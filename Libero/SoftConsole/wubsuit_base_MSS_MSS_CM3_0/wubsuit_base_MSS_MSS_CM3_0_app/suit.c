#include <inttypes.h>
#include <stdio.h>
#include "drivers/CoreUARTapb/core_uart_apb.h"
#include "drivers/mss_gpio/mss_gpio.h"
#include "suit.h"

// XBee RX Interrupt
__attribute__ ((interrupt)) void GPIO0_IRQHandler( void )
{
	uint8_t rx_data[MAX_RX_DATA_SIZE];
	uint8_t rx_size = 0;
	int i;
	rx_size = UART_get_rx(&XBee_uart, rx_data, sizeof(rx_data));

    printf("Receiving data from XBee\n\r");
    printf("Received %u bytes of data\n\r", rx_size);

    for (i = 0; i < rx_size; i++) {
    	printf("Data byte %u was %u\n\r", i, rx_data[i]);
    }

    printf("Finishing XBee RX interrupt\n\r");
    MSS_GPIO_clear_irq(MSS_GPIO_0);
    NVIC_ClearPendingIRQ(GPIO0_IRQn);
}

// MIDI RX Interrupt
__attribute__ ((interrupt)) void GPIO1_IRQHandler( void )
{
	uint8_t rx_data[3];
	uint8_t rx_size = 0;
	int i;
	rx_size = UART_get_rx(&MIDI_uart, rx_data, sizeof(rx_data));

    printf("Receiving data from MIDI\n\r");
    printf("Received %u bytes of data\n\r", rx_size);

    for (i = 0; i < rx_size; i++) {
    	printf("Data byte %u was %u\n\r", i, rx_data[i]);
    }

    printf("Finishing MIDI RX interrupt\n\r");
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
	printf("/\\/\\/\\/ WubSuit \\/\\/\\/\\\n\r");
	printf("Brian Daniels\n\r");
	printf("Patrick Hayes\n\r");
	printf("Brian Margosian\n\r");
	printf("Nick Tountasakis\n\r\n\r");

	/* Disable Watchdog Timer*/
	uint32_t * P_WDG_ENABLE = (uint32_t *)(0x40006010);
	*P_WDG_ENABLE = 0x4C6E55FA;

	printf("Initiating interrupts...\n\r");

	// Initialize GPIO
	MSS_GPIO_init();

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

	// Initialize XBee UART
	UART_init(&XBee_uart, COREUARTAPB0_BASE_ADDR, BAUD_VALUE_115200, (DATA_8_BITS | NO_PARITY));

	// Initialize MIDI UART
	UART_init(&MIDI_uart, COREUARTAPB1_BASE_ADDR, BAUD_VALUE_31250, (DATA_8_BITS | NO_PARITY));
}