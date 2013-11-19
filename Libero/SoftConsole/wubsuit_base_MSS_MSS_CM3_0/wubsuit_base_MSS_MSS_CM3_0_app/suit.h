#ifndef SUIT_H_
#define SUIT_H_

#include "drivers/CoreUARTapb/core_uart_apb.h"

// NOTE: Baud values based on 100MHz clock
#define BAUD_VALUE_115200    		53 //Possibly a problem because not exactly 53 (53.2535)
#define BAUD_VALUE_31250    		199

#define COREUARTAPB0_BASE_ADDR      0x40050000
#define COREUARTAPB1_BASE_ADDR      0x40050100
#define COREUARTAPB2_BASE_ADDR      0x40050200
#define MAX_RX_DATA_SIZE    		256

UART_instance_t XBee_uart, MIDI_uart;

struct state {
	uint8_t accelX, accelY, accelZ;
	uint8_t flexValue;
	uint8_t handHeight;
	uint8_t activeLights;
};

void Suit_init();

#endif /* SUIT_H_ */
