#ifndef __MIDI_H_
#define __MIDI_H_

#include "drivers/COREUARTapb/core_uart_apb.h"
#include "drivers/COREUARTapb/coreuartapb_regs.h"

#define MIDI_DEFAULT_VELOCITY 0x47

void MIDI_init(UART_instance_t *inst);
void MIDI_sendMessage(uint8_t dataBytes[], uint32_t numDataBytes);
void MIDI_noteOn(uint8_t note, uint8_t velocity, uint8_t channel);
void MIDI_noteOff(uint8_t note, uint8_t velocity, uint8_t channel);
void MIDI_pitchWheelChange(uint16_t value, uint8_t channel);
void MIDI_controlChange(uint8_t control, uint8_t value, uint8_t channel);
void MIDI_programChange(uint8_t program, uint8_t channel);

// Commands not implemented: Aftertouch and Channel Pressure

#endif /* __MIDI_H_ */
