#include <inttypes.h>
#include <stdio.h>
#include "drivers/CoreUARTapb/core_uart_apb.h"
#include "drivers/mss_gpio/mss_gpio.h"
#include "suit.h"
#include "menu.h"
#include "midi.h"
#include "lcd.h"

UART_instance_t XBee_uart, MIDI_uart;

XBeeState xbeeState;
MIDIState midiState;
SuitState suitState;
Settings settings;

// XBee RX Interrupt
__attribute__ ((interrupt)) void GPIO0_IRQHandler( void )
{
	uint8_t rx_data[MAX_RX_DATA_SIZE];
	uint8_t rx_size = 0;
	uint8_t err_status;
	volatile int i;

	//printf("XBee RX Interrupt Fired\n\r");

	while((MSS_GPIO_get_inputs() & 0x01) == 1) {
		//printf("Receiving data from MIDI\n\r");
		rx_size = UART_get_rx(&XBee_uart, rx_data, MAX_RX_DATA_SIZE);
		/*err_status = UART_get_rx_status(&XBee_uart);
		if (err_status != 0) {
			//printf("MIDI UART error with code %u\n\r", err_status);
			return;
		}*/
		if (rx_size >= 1) {
			for (i = 0; i < rx_size; i++) {
				if (xbeeState.valid == 1) {
					// New packet is found
					if (rx_data[i] == 0xFF) {
						if (xbeeState.packetPointer != XBEE_PACKET_LENGTH) {
							// The XBee state has been invalidated, reset packet
							xbeeState.valid = 0;
						} else {
							// New packet coming in, reset packet pointer
							xbeeState.packetPointer = 0;
						}
					}
				} else {
					// Check for next packet
					if (rx_data[i] == 0xFF) {
						xbeeState.packetPointer = 0;
						xbeeState.valid = 1;
					}
				}

				xbeeState.data[xbeeState.packetPointer++] = rx_data[i];

				// XBee state is valid and we have a full packet
				if (xbeeState.valid == 1 && xbeeState.packetPointer == XBEE_PACKET_LENGTH) {
					suitState.accelX = xbeeState.data[1];
					suitState.accelY = xbeeState.data[2];
					suitState.accelZ = xbeeState.data[3];
					suitState.flexValue = xbeeState.data[4];
					suitState.handHeight = xbeeState.data[5];
					Suit_newSensorValues();
				}
			}
		}
	}

	/*printf("Receiving %u bytes of data\n\r", rx_index);
	for (i = 0; i < rx_index; i++) {
		printf("Data byte %u was %#x\n\r", i, final_data[i]);
	}*/

    MSS_GPIO_clear_irq(MSS_GPIO_0);
    NVIC_ClearPendingIRQ(GPIO0_IRQn);
}

// MIDI RX Interrupt
__attribute__ ((interrupt)) void GPIO1_IRQHandler( void )
{
	uint8_t rx_data[MAX_RX_DATA_SIZE];
	uint8_t rx_size = 0;
	uint8_t err_status;
	volatile int i;

	//printf("MIDI RX Interrupt Fired\n\r");


	while(((MSS_GPIO_get_inputs() >> 1) & 0x01) == 1) {
		//printf("Receiving data from MIDI\n\r");
		rx_size = UART_get_rx(&MIDI_uart, rx_data, MAX_RX_DATA_SIZE);
		/*err_status = UART_get_rx_status(&MIDI_uart);
		if (err_status != 0) {
			//printf("MIDI UART error with code %u\n\r", err_status);
			return;
		}*/
		if (rx_size >= 1) {
			for (i = 0; i < rx_size; i++) {
				if (midiState.valid == 1) {
					// New packet is found
					if (((rx_data[i] >> 7) & 0x1) == 1 && (rx_data[i] & 0xF) == settings.suitLightsMIDIChannel) {
						if (midiState.packetPointer != MIDI_PACKET_LENGTH) {
							// The MIDI state has been invalidated, reset packet
							midiState.valid = 0;
						} else {
							// New packet coming in, reset packet pointer
							midiState.packetPointer = 0;
						}
					}
				} else {
					// Check for next packet
					if (((rx_data[i] >> 7) & 0x1) == 1 && (rx_data[i] & 0xF) == settings.suitLightsMIDIChannel) {
						midiState.packetPointer = 0;
						midiState.valid = 1;
					}
				}

				midiState.data[midiState.packetPointer++] = rx_data[i];

				// MIDI state is valid and we have a full packet
				if (midiState.valid == 1 && midiState.packetPointer == MIDI_PACKET_LENGTH) {
					Suit_handleMIDIMessage(midiState.data, MIDI_PACKET_LENGTH);
				}
			}
		}
	}

    //printf("Finishing MIDI RX interrupt\n\r");
    MSS_GPIO_clear_irq(MSS_GPIO_1);
    NVIC_ClearPendingIRQ(GPIO1_IRQn);
}

// CapButton Interrupt
__attribute__ ((interrupt)) void GPIO2_IRQHandler( void )
{
	uint8_t buttonState = ((MSS_GPIO_get_inputs() >> 2) & 0x01);

	//printf("New CapButton state of %u\n\r", buttonState);

    if (buttonState == 1) {
    	Suit_capButtonPressed();
    } else {
    	Suit_capButtonReleased();
    }

    //printf("Finishing CapButton interrupt\n\r");
    MSS_GPIO_clear_irq(MSS_GPIO_2);
    NVIC_ClearPendingIRQ(GPIO2_IRQn);
}

// LPiezo Interrupt
__attribute__ ((interrupt)) void GPIO3_IRQHandler( void )
{
	//printf("LPiezo went high\n\r");

	Suit_LPiezoPressed();

    //printf("Finishing LPiezo interrupt\n\r");
    MSS_GPIO_clear_irq(MSS_GPIO_3);
    NVIC_ClearPendingIRQ(GPIO3_IRQn);
}

void Suit_init() {
	printf("\n\r\nr\r/\\/\\/\\/ WubSuit \\/\\/\\/\\\n\r");
	printf("Brian Daniels\n\r");
	printf("Patrick Hayes\n\r");
	printf("Brian Margosian\n\r");
	printf("Nick Tountasakis\n\r\n\r");

	suitState.waitingForMIDI = 0;
	suitState.noteActive = 0;

	xbeeState.valid = 0;
	xbeeState.packetPointer = 0;
	volatile int i;
	for (i = 0; i < XBEE_PACKET_LENGTH; i++) {
		xbeeState.data[i] = 0;
	}

	midiState.valid = 0;
	midiState.packetPointer = 0;
	for (i = 0; i < MIDI_PACKET_LENGTH; i++) {
		midiState.data[i] = 0;
	}

	settings.suitLightMappings[0] = C0;
	settings.suitLightMappings[1] = CS0;
	settings.suitLightMappings[2] = D0;
	settings.suitLightMappings[3] = DS0;
	settings.suitLightMappings[4] = E0;
	settings.suitLightMappings[5] = F0;

	suitState.handHeight = 0;
	settings.handHeightMapping = 0;
	settings.handHeightMin = 10;
	settings.handHeightMax = 90;

	settings.LPiezoMapping = C2;
	settings.RPiezoMapping = CS2;

	settings.minNote = C4;
	settings.maxNote = C5;
	settings.keySignature = CHROMATIC;
	settings.suitLightsMIDIChannel = 0;
	settings.outputMIDIChannel = 0;

	settings.accelMin = 0;
	settings.accelMax = 255;
	settings.pitchBendMin = 0;
	settings.pitchBendMax = 127;

	/* Disable Watchdog Timer*/
	uint32_t * P_WDG_ENABLE = (uint32_t *)(0x40006010);
	*P_WDG_ENABLE = 0x4C6E55FA;

	printf("Initiating interrupts...\n\r");

	// Initialize GPIO
	MSS_GPIO_init();

	// Initialize XBee UART
	UART_init(&XBee_uart, COREUARTAPB0_BASE_ADDR, BAUD_VALUE_115200, (DATA_8_BITS | NO_PARITY));

	// Initialize MIDI UART
	UART_init(&MIDI_uart, COREUARTAPB1_BASE_ADDR, BAUD_VALUE_31250, (DATA_8_BITS | NO_PARITY));
	MIDI_init(&MIDI_uart);

	// Setup XBee RX interrupt
	MSS_GPIO_config(MSS_GPIO_0, MSS_GPIO_INPUT_MODE | MSS_GPIO_IRQ_EDGE_POSITIVE);
	MSS_GPIO_enable_irq(MSS_GPIO_0);
	NVIC_EnableIRQ(GPIO0_IRQn);

	// Setup MIDI RX interrupt
	MSS_GPIO_config(MSS_GPIO_1, MSS_GPIO_INPUT_MODE | MSS_GPIO_IRQ_EDGE_POSITIVE);
	MSS_GPIO_enable_irq(MSS_GPIO_1);
	NVIC_EnableIRQ(GPIO1_IRQn);

	// Setup CapButton interrupt
	MSS_GPIO_config(MSS_GPIO_2, MSS_GPIO_INPUT_MODE | MSS_GPIO_IRQ_EDGE_BOTH);
	MSS_GPIO_enable_irq(MSS_GPIO_2);
	NVIC_EnableIRQ(GPIO2_IRQn);

	// Setup LPiezo interrupt
	MSS_GPIO_config(MSS_GPIO_3, MSS_GPIO_INPUT_MODE | MSS_GPIO_IRQ_EDGE_POSITIVE);
	MSS_GPIO_enable_irq(MSS_GPIO_3);
	NVIC_EnableIRQ(GPIO3_IRQn);
	printf("Before menu init\n\r");
	Menu_init(&settings, &suitState);
	printf("After menu init\n\r");

	Suit_setMode(PERFORMANCE);
}

/*void Menu_LPiezoOptionCmd() {
	suitState.waitingForMIDI = 1;
	settings.valueToMapTo = &(settings.LPiezoMapping);
	menuState.menus[4].name = WAITING_MESSAGE;
}*/

void Suit_handleMIDIMessage(uint8_t *message, uint16_t length) {
	uint8_t channel;
	if (message[0] == 0x90) {
		channel = Suit_MIDIToLightChannel(message[1]);
		Suit_turnOnLightChannel(channel);
	} else if (message[0] == 0x80) {
		channel = Suit_MIDIToLightChannel(message[1]);
		Suit_turnOffLightChannel(channel);
	}
}

void Suit_turnOnLightChannel(uint8_t channel) {
	suitState.activeLights |= (0x1 << channel);
	//printf("Active lights (on): %#x\n\r", suitState.activeLights);
}

void Suit_turnOffLightChannel(uint8_t channel) {
	suitState.activeLights &= ~(0x1 << channel);
	//printf("Active lights (off): %#x\n\r", suitState.activeLights);
}

uint8_t Suit_MIDIToLightChannel(uint8_t note) {
	volatile int i;
	for (i = 0; i < LIGHT_CHANNELS; i++) {
		if (settings.suitLightMappings[i] == note) {
			return i;
		}
	}
	//printf("Invalid MIDI Light Channel note mapping %#x\n\r", note);
	return 0;
}

void Suit_newSensorValues() {
	printf("Accel: (%u, %u, %u)\n\r", suitState.accelX, suitState.accelY, suitState.accelZ);
	printf("Flex: %u\n\r", suitState.flexValue);
	printf("Hand Height: %u\n\r", suitState.handHeight);

	if (suitState.state == PERFORMANCE) {
		uint8_t pitchBendOut = Suit_mapValue(suitState.accelX, settings.accelMin, settings.accelMax, settings.pitchBendMin, settings.pitchBendMax);
		MIDI_pitchWheelChange(pitchBendOut, settings.outputMIDIChannel);
	}
}

void Suit_capButtonPressed() {
	if (suitState.state == PERFORMANCE) {
		if (suitState.noteActive == 1) {
			MIDI_noteOff(suitState.activeNote, MIDI_DEFAULT_VELOCITY, settings.outputMIDIChannel);
		}
		Note noteOut = Suit_mapValue(suitState.handHeight, settings.handHeightMin, settings.handHeightMax, settings.minNote, settings.maxNote);
		suitState.activeNote = noteOut;
		suitState.noteActive = 1;
		MIDI_noteOn(noteOut, MIDI_DEFAULT_VELOCITY, settings.outputMIDIChannel);
	} else {
		Menu_select();
	}
}

void Suit_capButtonReleased() {
	if (suitState.state == PERFORMANCE) {
		if (suitState.noteActive == 1) {
			suitState.noteActive = 0;
			MIDI_noteOff(suitState.activeNote, MIDI_DEFAULT_VELOCITY, settings.outputMIDIChannel);
		}
	}
}

void Suit_LPiezoPressed() {
	if (suitState.state == PERFORMANCE) {
		MIDI_noteOff(settings.LPiezoMapping, MIDI_DEFAULT_VELOCITY, settings.outputMIDIChannel);
		MIDI_noteOn(settings.LPiezoMapping, MIDI_DEFAULT_VELOCITY, settings.outputMIDIChannel);
	} else {
		Menu_moveDown();
	}
}

void Suit_RPiezoPressed() {
	MIDI_noteOff(settings.RPiezoMapping, MIDI_DEFAULT_VELOCITY, settings.outputMIDIChannel);
	MIDI_noteOn(settings.RPiezoMapping, MIDI_DEFAULT_VELOCITY, settings.outputMIDIChannel);
}

// Taken from Arduino
uint8_t Suit_mapValue(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Suit_setMode(State state) {
	suitState.state = state;
	if (state == PERFORMANCE) {
		//LCD_showSensorValues();
	} else {
		Menu_displayCurrentMenu();
	}
}
