//////////////////////////////////////////////////////////////////////
// Created by Actel SmartDesign Mon Nov 18 20:59:57 2013
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
// Instantiate Unit Under Test:  wubsuit_base_MSS
//////////////////////////////////////////////////////////////////////
wubsuit_base_MSS wubsuit_base_MSS_0 (
    // Inputs
    .MSSPREADY({1{1'b0}}),
    .MSSPSLVERR({1{1'b0}}),
    .F2M_GPI_0({1{1'b0}}),
    .F2M_GPI_8({1{1'b0}}),
    .F2M_GPI_7({1{1'b0}}),
    .F2M_GPI_6({1{1'b0}}),
    .F2M_GPI_5({1{1'b0}}),
    .F2M_GPI_4({1{1'b0}}),
    .F2M_GPI_3({1{1'b0}}),
    .F2M_GPI_2({1{1'b0}}),
    .F2M_GPI_1({1{1'b0}}),
    .MSSPRDATA({32{1'b0}}),
    .UART_0_RXD({1{1'b0}}),
    .MSS_RESET_N(NSYSRESET),

    // Outputs
    .FAB_CLK( ),
    .MSSPSEL( ),
    .MSSPENABLE( ),
    .MSSPWRITE( ),
    .M2F_RESET_N( ),
    .MSSPADDR( ),
    .MSSPWDATA( ),
    .UART_0_TXD( )

    // Inouts

);

endmodule

