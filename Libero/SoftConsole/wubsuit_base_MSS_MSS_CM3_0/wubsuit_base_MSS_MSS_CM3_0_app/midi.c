#include "drivers/COREUARTapb/core_uart_apb.h"
#include "drivers/COREUARTapb/coreuartapb_regs.h"

UART_instance_t *uartInstance;

void MIDI_init(UART_instance_t *inst) {
	uartInstance = inst;
}

void MIDI_sendMessage(uint8_t dataBytes[], uint32_t numDataBytes) {
	UART_send(uartInstance, dataBytes, numDataBytes);
    //MSS_UART_polled_tx( &g_mss_uart1, dataBytes, numDataBytes );
}

void MIDI_noteOn(uint8_t note, uint8_t velocity, uint8_t channel) {
    uint8_t data[3] = { 0x90 | (channel & 0xF), note, velocity};
    MIDI_sendMessage(data, 3);
}

void MIDI_noteOff(uint8_t note, uint8_t velocity, uint8_t channel) {
    uint8_t data[3] = { 0x80 | (channel & 0xF), note, velocity};
    MIDI_sendMessage(data, 3);
}

void MIDI_pitchWheelChange(uint16_t value, uint8_t channel) {
	uint8_t data[3] = {0xE0 | (channel & 0xF), value & 0x7F, value & 0x3F80>> 8};
	MIDI_sendMessage(data, 3);
}

void MIDI_controlChange(uint8_t control, uint8_t value, uint8_t channel) {
    uint8_t data[3] = { 0xB0 | (channel & 0xF), control, value};
    MIDI_sendMessage(data, 3);
}

void MIDI_programChange(uint8_t program, uint8_t channel) {
    uint8_t data[2] = { 0xC0 | (channel & 0xF), program};
    MIDI_sendMessage(data, 2);
}

// Commands not implemented: Aftertouch and Channel Pressure
