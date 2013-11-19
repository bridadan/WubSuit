//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Mon Nov 18 21:31:02 2013
// Testbench Template
// This is a basic testbench that instantiates your design with basic 
// clock and reset pins connected.  If your design has special
// clock/reset or testbench driver requirements then you should 
// copy this file and modify it. 
//////////////////////////////////////////////////////////////////////

`timescale 1ns/100ps

module testbench;

parameter SYSCLK_PERIOD = 100; // 10MHz

reg SYSCLK;
reg NSYSRESET;

initial
begin
    SYSCLK = 1'b0;
    NSYSRESET = 1'b0;
end

//////////////////////////////////////////////////////////////////////
// Reset Pulse
//////////////////////////////////////////////////////////////////////
initial
begin
    #(SYSCLK_PERIOD * 10 )
        NSYSRESET = 1'b1;
end


//////////////////////////////////////////////////////////////////////
// 10MHz Clock Driver
//////////////////////////////////////////////////////////////////////
always @(SYSCLK)
    #(SYSCLK_PERIOD / 2.0) SYSCLK <= !SYSCLK;


//////////////////////////////////////////////////////////////////////
// Instantiate Unit Under Test:  wubsuit_base
//////////////////////////////////////////////////////////////////////
wubsuit_base wubsuit_base_0 (
    // Inputs
    .UART_0_RXD({1{1'b0}}),
    .MSS_RESET_N(NSYSRESET),
    .XBee_RX({1{1'b0}}),
    .MIDI_RX({1{1'b0}}),
    .CapButton({1{1'b0}}),
    .LPiezo({1{1'b0}}),

    // Outputs
    .UART_0_TXD( ),
    .XBee_TX( ),
    .MIDI_TX( ),
    .LCD_TX( )

    // Inouts

);

endmodule

