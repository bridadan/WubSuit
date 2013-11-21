#include <inttypes.h>
#include <stdio.h>
#include "drivers/CoreUARTapb/core_uart_apb.h"
#include "drivers/mss_gpio/mss_gpio.h"
#include "suit.h"

// XBee RX Interrupt
__attribute__ ((interrupt)) void GPIO0_IRQHandler( void )
{
	uint8_t final_data[MAX_RX_DATA_SIZE];
	uint8_t rx_data[MAX_RX_DATA_SIZE];
	uint8_t rx_size = 0;
	uint8_t rx_index = 0;
	uint8_t err_status;

	printf("XBee RX Interrupt Fired\n\r");

	while((MSS_GPIO_get_inputs() & 0x01) == 1) {
		//printf("Receiving data from MIDI\n\r");
		rx_size = UART_get_rx(&XBee_uart, rx_data, MAX_RX_DATA_SIZE);
		err_status = UART_get_rx_status(&XBee_uart);
		if (err_status != 0) {
			//printf("MIDI UART error with code %u\n\r", err_status);
			return;
		}
		if (rx_size >= 1) {
			volatile int i;
			//printf("Receiving %u bytes of data\n\r", rx_size);
			for (i = 0; i < rx_size; i++) {
				//printf("Data byte %u was %#x\n\r", rx_index++, rx_data[i]);
				final_data[rx_index] = rx_data[i];
			}
		}
	}

    MSS_GPIO_clear_irq(MSS_GPIO_0);
    NVIC_ClearPendingIRQ(GPIO0_IRQn);
}

// MIDI RX Interrupt
__attribute__ ((interrupt)) void GPIO1_IRQHandler( void )
{
	uint8_t final_data[MAX_RX_DATA_SIZE];
	uint8_t rx_data[MAX_RX_DATA_SIZE];
	uint8_t rx_size = 0;
	uint8_t rx_index = 0;
	//uint8_t err_status;

	printf("MIDI RX Interrupt Fired\n\r");
	volatile int i, j;
	while(((MSS_GPIO_get_inputs() >> 1) & 0x01) == 1) {
		//printf("Receiving data from MIDI\n\r");
		rx_size = UART_get_rx(&MIDI_uart, rx_data, MAX_RX_DATA_SIZE);
		//err_status = UART_get_rx_status(&MIDI_uart);
		/*if (err_status != 0) {
			//printf("MIDI UART error with code %u\n\r", err_status);
			return;
		}*/
		if (rx_size >= 1) {
			//printf("Receiving %u bytes of data\n\r", rx_size);
			for (i = 0; i < rx_size; i++) {
				//printf("Data byte %u was %#x\n\r", rx_index, rx_data[i]);
				final_data[rx_index++] = rx_data[i];
			}
		}
	}
	i = 0;
	while (i < rx_index) {
		//Handle data
		if (((final_data[i] >> 7) & 0x1) == 1){
			j = i + 1;
			while (((final_data[j] >> 7) & 0x1) == 0 && j < rx_index) {
				j++;
			}
			//printf("Message handling with length %u\n\r", j - i);
			Suit_handleMIDIMessage(&(final_data[i]), j - i);
			i += j;
		} else {
			i++;
		}
	}

	//printf("Received %u bytes of data\n\r", rx_index);

	// Call function with final_data as argument

    //printf("Finishing MIDI RX interrupt\n\r");
    MSS_GPIO_clear_irq(MSS_GPIO_1);
    NVIC_ClearPendingIRQ(GPIO1_IRQn);
}

// CapButton Interrupt
__attribute__ ((interrupt)) void GPIO2_IRQHandler( void )
{
	uint8_t buttonState = ((MSS_GPIO_get_inputs() >> 2) & 0x01);

	printf("New CapButton state of %u\n\r", buttonState);

    // call handle capButtonChanged

    printf("Finishing CapButton interrupt\n\r");
    MSS_GPIO_clear_irq(MSS_GPIO_2);
    NVIC_ClearPendingIRQ(GPIO2_IRQn);
}

// LPiezo Interrupt
__attribute__ ((interrupt)) void GPIO3_IRQHandler( void )
{
	uint8_t buttonState = ((MSS_GPIO_get_inputs() >> 3) & 0x01);

	printf("LPiezo went high %u\n\r", buttonState);

    // call handle capButtonChanged

    printf("Finishing LPiezo interrupt\n\r");
    MSS_GPIO_clear_irq(MSS_GPIO_3);
    NVIC_ClearPendingIRQ(GPIO3_IRQn);
}

void Suit_init() {
	printf("\n\r\nr\r/\\/\\/\\/ WubSuit \\/\\/\\/\\\n\r");
	printf("Brian Daniels\n\r");
	printf("Patrick Hayes\n\r");
	printf("Brian Margosian\n\r");
	printf("Nick Tountasakis\n\r\n\r");

	/* Disable Watchdog Timer*/
	uint32_t * P_WDG_ENABLE = (uint32_t *)(0x40006010);
	*P_WDG_ENABLE = 0x4C6E55FA;

	suitState.lightControlMIDIChannel = 0;
	volatile int i;
	for (i = 0; i < LIGHT_CHANNELS_COUNT; i++) {
		suitState.lightChannelMappings[i] = i;
	}

	printf("Initiating interrupts...\n\r");

	// Initialize GPIO
	MSS_GPIO_init();

	// Initialize XBee UART
	UART_init(&XBee_uart, COREUARTAPB0_BASE_ADDR, BAUD_VALUE_115200, (DATA_8_BITS | NO_PARITY));

	// Initialize MIDI UART
	UART_init(&MIDI_uart, COREUARTAPB1_BASE_ADDR, BAUD_VALUE_31250, (DATA_8_BITS | NO_PARITY));

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
}

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
	for (i = 0; i < LIGHT_CHANNELS_COUNT; i++) {
		if (suitState.lightChannelMappings[i] == note) {
			return i;
		}
	}
	//printf("Invalid MIDI Light Channel note mapping %#x\n\r", note);
	return 0;
}
