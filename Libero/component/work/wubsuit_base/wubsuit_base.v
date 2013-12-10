//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Tue Dec 10 02:32:13 2013
// Version: v11.0 11.0.0.23
//////////////////////////////////////////////////////////////////////

`timescale 1 ns/100 ps

// wubsuit_base
module wubsuit_base(
    // Inputs
    CButton0,
    CButton1,
    CButton2,
    CButton3,
    CapButton,
    LPiezo,
    MIDI_RX,
    MSS_RESET_N,
    RPiezo,
    UART_0_RXD,
    XBee_RX,
    // Outputs
    LCD_TX,
    MIDI_TX,
    RXRDY,
    UART_0_TXD,
    XBee_TX
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input  CButton0;
input  CButton1;
input  CButton2;
input  CButton3;
input  CapButton;
input  LPiezo;
input  MIDI_RX;
input  MSS_RESET_N;
input  RPiezo;
input  UART_0_RXD;
input  XBee_RX;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output LCD_TX;
output MIDI_TX;
output RXRDY;
output UART_0_TXD;
output XBee_TX;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire          CapButton;
wire          CButton0;
wire          CButton1;
wire          CButton2;
wire          CButton3;
wire          CoreAPB3_0_APBmslave0_PENABLE;
wire          CoreAPB3_0_APBmslave0_PREADY;
wire          CoreAPB3_0_APBmslave0_PSELx;
wire          CoreAPB3_0_APBmslave0_PSLVERR;
wire          CoreAPB3_0_APBmslave0_PWRITE;
wire          CoreAPB3_0_APBmslave1_PREADY;
wire          CoreAPB3_0_APBmslave1_PSELx;
wire          CoreAPB3_0_APBmslave1_PSLVERR;
wire          CoreAPB3_0_APBmslave2_PREADY;
wire          CoreAPB3_0_APBmslave2_PSELx;
wire          CoreAPB3_0_APBmslave2_PSLVERR;
wire          FABINT;
wire          fastTimer_0_fabint;
wire          FRAMING_ERR;
wire          LCD_TX_net_0;
wire          LPiezo;
wire          MIDI_RX;
wire          MIDI_TX_net_0;
wire          MSS_RESET_N;
wire          OVERFLOW;
wire          PARITY_ERR;
wire          RPiezo;
wire          RXRDY_net_0;
wire          RXRDY_0;
wire          UART_0_RXD;
wire          UART_0_TXD_net_0;
wire          wubsuit_base_MSS_0_FAB_CLK;
wire          wubsuit_base_MSS_0_M2F_RESET_N;
wire          wubsuit_base_MSS_0_MSS_MASTER_APB_PENABLE;
wire   [31:0] wubsuit_base_MSS_0_MSS_MASTER_APB_PRDATA;
wire          wubsuit_base_MSS_0_MSS_MASTER_APB_PREADY;
wire          wubsuit_base_MSS_0_MSS_MASTER_APB_PSELx;
wire          wubsuit_base_MSS_0_MSS_MASTER_APB_PSLVERR;
wire   [31:0] wubsuit_base_MSS_0_MSS_MASTER_APB_PWDATA;
wire          wubsuit_base_MSS_0_MSS_MASTER_APB_PWRITE;
wire          XBee_RX;
wire          XBee_TX_net_0;
wire          UART_0_TXD_net_1;
wire          XBee_TX_net_1;
wire          LCD_TX_net_1;
wire          MIDI_TX_net_1;
wire          RXRDY_0_net_0;
//--------------------------------------------------------------------
// TiedOff Nets
//--------------------------------------------------------------------
wire          VCC_net;
wire          GND_net;
wire   [31:0] IADDR_const_net_0;
wire   [31:0] PRDATAS3_const_net_0;
wire   [31:0] PRDATAS4_const_net_0;
wire   [31:0] PRDATAS5_const_net_0;
wire   [31:0] PRDATAS6_const_net_0;
wire   [31:0] PRDATAS7_const_net_0;
wire   [31:0] PRDATAS8_const_net_0;
wire   [31:0] PRDATAS9_const_net_0;
wire   [31:0] PRDATAS10_const_net_0;
wire   [31:0] PRDATAS11_const_net_0;
wire   [31:0] PRDATAS12_const_net_0;
wire   [31:0] PRDATAS13_const_net_0;
wire   [31:0] PRDATAS14_const_net_0;
wire   [31:0] PRDATAS15_const_net_0;
wire   [31:0] PRDATAS16_const_net_0;
//--------------------------------------------------------------------
// Bus Interface Nets Declarations - Unequal Pin Widths
//--------------------------------------------------------------------
wire   [4:0]  CoreAPB3_0_APBmslave0_PADDR_0_4to0;
wire   [4:0]  CoreAPB3_0_APBmslave0_PADDR_0;
wire   [4:0]  CoreAPB3_0_APBmslave0_PADDR_1_4to0;
wire   [4:0]  CoreAPB3_0_APBmslave0_PADDR_1;
wire   [4:0]  CoreAPB3_0_APBmslave0_PADDR_2_4to0;
wire   [4:0]  CoreAPB3_0_APBmslave0_PADDR_2;
wire   [31:0] CoreAPB3_0_APBmslave0_PADDR;
wire   [7:0]  CoreAPB3_0_APBmslave0_PRDATA;
wire   [31:8] CoreAPB3_0_APBmslave0_PRDATA_0_31to8;
wire   [7:0]  CoreAPB3_0_APBmslave0_PRDATA_0_7to0;
wire   [31:0] CoreAPB3_0_APBmslave0_PRDATA_0;
wire   [7:0]  CoreAPB3_0_APBmslave0_PWDATA_0_7to0;
wire   [7:0]  CoreAPB3_0_APBmslave0_PWDATA_0;
wire   [7:0]  CoreAPB3_0_APBmslave0_PWDATA_1_7to0;
wire   [7:0]  CoreAPB3_0_APBmslave0_PWDATA_1;
wire   [7:0]  CoreAPB3_0_APBmslave0_PWDATA_2_7to0;
wire   [7:0]  CoreAPB3_0_APBmslave0_PWDATA_2;
wire   [31:0] CoreAPB3_0_APBmslave0_PWDATA;
wire   [7:0]  CoreAPB3_0_APBmslave1_PRDATA;
wire   [31:8] CoreAPB3_0_APBmslave1_PRDATA_0_31to8;
wire   [7:0]  CoreAPB3_0_APBmslave1_PRDATA_0_7to0;
wire   [31:0] CoreAPB3_0_APBmslave1_PRDATA_0;
wire   [7:0]  CoreAPB3_0_APBmslave2_PRDATA;
wire   [31:8] CoreAPB3_0_APBmslave2_PRDATA_0_31to8;
wire   [7:0]  CoreAPB3_0_APBmslave2_PRDATA_0_7to0;
wire   [31:0] CoreAPB3_0_APBmslave2_PRDATA_0;
wire   [31:20]wubsuit_base_MSS_0_MSS_MASTER_APB_PADDR_0_31to20;
wire   [19:0] wubsuit_base_MSS_0_MSS_MASTER_APB_PADDR_0_19to0;
wire   [31:0] wubsuit_base_MSS_0_MSS_MASTER_APB_PADDR_0;
wire   [19:0] wubsuit_base_MSS_0_MSS_MASTER_APB_PADDR;
//--------------------------------------------------------------------
// Constant assignments
//--------------------------------------------------------------------
assign VCC_net               = 1'b1;
assign GND_net               = 1'b0;
assign IADDR_const_net_0     = 32'h00000000;
assign PRDATAS3_const_net_0  = 32'h00000000;
assign PRDATAS4_const_net_0  = 32'h00000000;
assign PRDATAS5_const_net_0  = 32'h00000000;
assign PRDATAS6_const_net_0  = 32'h00000000;
assign PRDATAS7_const_net_0  = 32'h00000000;
assign PRDATAS8_const_net_0  = 32'h00000000;
assign PRDATAS9_const_net_0  = 32'h00000000;
assign PRDATAS10_const_net_0 = 32'h00000000;
assign PRDATAS11_const_net_0 = 32'h00000000;
assign PRDATAS12_const_net_0 = 32'h00000000;
assign PRDATAS13_const_net_0 = 32'h00000000;
assign PRDATAS14_const_net_0 = 32'h00000000;
assign PRDATAS15_const_net_0 = 32'h00000000;
assign PRDATAS16_const_net_0 = 32'h00000000;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign UART_0_TXD_net_1 = UART_0_TXD_net_0;
assign UART_0_TXD       = UART_0_TXD_net_1;
assign XBee_TX_net_1    = XBee_TX_net_0;
assign XBee_TX          = XBee_TX_net_1;
assign LCD_TX_net_1     = LCD_TX_net_0;
assign LCD_TX           = LCD_TX_net_1;
assign MIDI_TX_net_1    = MIDI_TX_net_0;
assign MIDI_TX          = MIDI_TX_net_1;
assign RXRDY_0_net_0    = RXRDY_0;
assign RXRDY            = RXRDY_0_net_0;
//--------------------------------------------------------------------
// Bus Interface Nets Assignments - Unequal Pin Widths
//--------------------------------------------------------------------
assign CoreAPB3_0_APBmslave0_PADDR_0_4to0 = CoreAPB3_0_APBmslave0_PADDR[4:0];
assign CoreAPB3_0_APBmslave0_PADDR_0 = { CoreAPB3_0_APBmslave0_PADDR_0_4to0 };
assign CoreAPB3_0_APBmslave0_PADDR_1_4to0 = CoreAPB3_0_APBmslave0_PADDR[4:0];
assign CoreAPB3_0_APBmslave0_PADDR_1 = { CoreAPB3_0_APBmslave0_PADDR_1_4to0 };
assign CoreAPB3_0_APBmslave0_PADDR_2_4to0 = CoreAPB3_0_APBmslave0_PADDR[4:0];
assign CoreAPB3_0_APBmslave0_PADDR_2 = { CoreAPB3_0_APBmslave0_PADDR_2_4to0 };

assign CoreAPB3_0_APBmslave0_PRDATA_0_31to8 = 24'h0;
assign CoreAPB3_0_APBmslave0_PRDATA_0_7to0 = CoreAPB3_0_APBmslave0_PRDATA[7:0];
assign CoreAPB3_0_APBmslave0_PRDATA_0 = { CoreAPB3_0_APBmslave0_PRDATA_0_31to8, CoreAPB3_0_APBmslave0_PRDATA_0_7to0 };

assign CoreAPB3_0_APBmslave0_PWDATA_0_7to0 = CoreAPB3_0_APBmslave0_PWDATA[7:0];
assign CoreAPB3_0_APBmslave0_PWDATA_0 = { CoreAPB3_0_APBmslave0_PWDATA_0_7to0 };
assign CoreAPB3_0_APBmslave0_PWDATA_1_7to0 = CoreAPB3_0_APBmslave0_PWDATA[7:0];
assign CoreAPB3_0_APBmslave0_PWDATA_1 = { CoreAPB3_0_APBmslave0_PWDATA_1_7to0 };
assign CoreAPB3_0_APBmslave0_PWDATA_2_7to0 = CoreAPB3_0_APBmslave0_PWDATA[7:0];
assign CoreAPB3_0_APBmslave0_PWDATA_2 = { CoreAPB3_0_APBmslave0_PWDATA_2_7to0 };

assign CoreAPB3_0_APBmslave1_PRDATA_0_31to8 = 24'h0;
assign CoreAPB3_0_APBmslave1_PRDATA_0_7to0 = CoreAPB3_0_APBmslave1_PRDATA[7:0];
assign CoreAPB3_0_APBmslave1_PRDATA_0 = { CoreAPB3_0_APBmslave1_PRDATA_0_31to8, CoreAPB3_0_APBmslave1_PRDATA_0_7to0 };

assign CoreAPB3_0_APBmslave2_PRDATA_0_31to8 = 24'h0;
assign CoreAPB3_0_APBmslave2_PRDATA_0_7to0 = CoreAPB3_0_APBmslave2_PRDATA[7:0];
assign CoreAPB3_0_APBmslave2_PRDATA_0 = { CoreAPB3_0_APBmslave2_PRDATA_0_31to8, CoreAPB3_0_APBmslave2_PRDATA_0_7to0 };

assign wubsuit_base_MSS_0_MSS_MASTER_APB_PADDR_0_31to20 = 12'h0;
assign wubsuit_base_MSS_0_MSS_MASTER_APB_PADDR_0_19to0 = wubsuit_base_MSS_0_MSS_MASTER_APB_PADDR[19:0];
assign wubsuit_base_MSS_0_MSS_MASTER_APB_PADDR_0 = { wubsuit_base_MSS_0_MSS_MASTER_APB_PADDR_0_31to20, wubsuit_base_MSS_0_MSS_MASTER_APB_PADDR_0_19to0 };

//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------CoreAPB3   -   Actel:DirectCore:CoreAPB3:4.0.100
CoreAPB3 #( 
        .APB_DWIDTH      ( 32 ),
        .APBSLOT0ENABLE  ( 1 ),
        .APBSLOT1ENABLE  ( 1 ),
        .APBSLOT2ENABLE  ( 1 ),
        .APBSLOT3ENABLE  ( 0 ),
        .APBSLOT4ENABLE  ( 0 ),
        .APBSLOT5ENABLE  ( 0 ),
        .APBSLOT6ENABLE  ( 0 ),
        .APBSLOT7ENABLE  ( 0 ),
        .APBSLOT8ENABLE  ( 0 ),
        .APBSLOT9ENABLE  ( 0 ),
        .APBSLOT10ENABLE ( 0 ),
        .APBSLOT11ENABLE ( 0 ),
        .APBSLOT12ENABLE ( 0 ),
        .APBSLOT13ENABLE ( 0 ),
        .APBSLOT14ENABLE ( 0 ),
        .APBSLOT15ENABLE ( 0 ),
        .IADDR_OPTION    ( 0 ),
        .MADDR_BITS      ( 12 ),
        .SC_0            ( 0 ),
        .SC_1            ( 0 ),
        .SC_2            ( 0 ),
        .SC_3            ( 0 ),
        .SC_4            ( 0 ),
        .SC_5            ( 0 ),
        .SC_6            ( 0 ),
        .SC_7            ( 0 ),
        .SC_8            ( 0 ),
        .SC_9            ( 0 ),
        .SC_10           ( 0 ),
        .SC_11           ( 0 ),
        .SC_12           ( 0 ),
        .SC_13           ( 0 ),
        .SC_14           ( 0 ),
        .SC_15           ( 0 ),
        .UPR_NIBBLE_POSN ( 2 ) )
CoreAPB3_0(
        // Inputs
        .PRESETN    ( GND_net ), // tied to 1'b0 from definition
        .PCLK       ( GND_net ), // tied to 1'b0 from definition
        .PWRITE     ( wubsuit_base_MSS_0_MSS_MASTER_APB_PWRITE ),
        .PENABLE    ( wubsuit_base_MSS_0_MSS_MASTER_APB_PENABLE ),
        .PSEL       ( wubsuit_base_MSS_0_MSS_MASTER_APB_PSELx ),
        .PREADYS0   ( CoreAPB3_0_APBmslave0_PREADY ),
        .PSLVERRS0  ( CoreAPB3_0_APBmslave0_PSLVERR ),
        .PREADYS1   ( CoreAPB3_0_APBmslave1_PREADY ),
        .PSLVERRS1  ( CoreAPB3_0_APBmslave1_PSLVERR ),
        .PREADYS2   ( CoreAPB3_0_APBmslave2_PREADY ),
        .PSLVERRS2  ( CoreAPB3_0_APBmslave2_PSLVERR ),
        .PREADYS3   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS3  ( GND_net ), // tied to 1'b0 from definition
        .PREADYS4   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS4  ( GND_net ), // tied to 1'b0 from definition
        .PREADYS5   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS5  ( GND_net ), // tied to 1'b0 from definition
        .PREADYS6   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS6  ( GND_net ), // tied to 1'b0 from definition
        .PREADYS7   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS7  ( GND_net ), // tied to 1'b0 from definition
        .PREADYS8   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS8  ( GND_net ), // tied to 1'b0 from definition
        .PREADYS9   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS9  ( GND_net ), // tied to 1'b0 from definition
        .PREADYS10  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS10 ( GND_net ), // tied to 1'b0 from definition
        .PREADYS11  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS11 ( GND_net ), // tied to 1'b0 from definition
        .PREADYS12  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS12 ( GND_net ), // tied to 1'b0 from definition
        .PREADYS13  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS13 ( GND_net ), // tied to 1'b0 from definition
        .PREADYS14  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS14 ( GND_net ), // tied to 1'b0 from definition
        .PREADYS15  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS15 ( GND_net ), // tied to 1'b0 from definition
        .PREADYS16  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS16 ( GND_net ), // tied to 1'b0 from definition
        .PADDR      ( wubsuit_base_MSS_0_MSS_MASTER_APB_PADDR_0 ),
        .PWDATA     ( wubsuit_base_MSS_0_MSS_MASTER_APB_PWDATA ),
        .PRDATAS0   ( CoreAPB3_0_APBmslave0_PRDATA_0 ),
        .PRDATAS1   ( CoreAPB3_0_APBmslave1_PRDATA_0 ),
        .PRDATAS2   ( CoreAPB3_0_APBmslave2_PRDATA_0 ),
        .PRDATAS3   ( PRDATAS3_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS4   ( PRDATAS4_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS5   ( PRDATAS5_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS6   ( PRDATAS6_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS7   ( PRDATAS7_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS8   ( PRDATAS8_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS9   ( PRDATAS9_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS10  ( PRDATAS10_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS11  ( PRDATAS11_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS12  ( PRDATAS12_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS13  ( PRDATAS13_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS14  ( PRDATAS14_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS15  ( PRDATAS15_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS16  ( PRDATAS16_const_net_0 ), // tied to 32'h00000000 from definition
        .IADDR      ( IADDR_const_net_0 ), // tied to 32'h00000000 from definition
        // Outputs
        .PREADY     ( wubsuit_base_MSS_0_MSS_MASTER_APB_PREADY ),
        .PSLVERR    ( wubsuit_base_MSS_0_MSS_MASTER_APB_PSLVERR ),
        .PWRITES    ( CoreAPB3_0_APBmslave0_PWRITE ),
        .PENABLES   ( CoreAPB3_0_APBmslave0_PENABLE ),
        .PSELS0     ( CoreAPB3_0_APBmslave0_PSELx ),
        .PSELS1     ( CoreAPB3_0_APBmslave1_PSELx ),
        .PSELS2     ( CoreAPB3_0_APBmslave2_PSELx ),
        .PSELS3     (  ),
        .PSELS4     (  ),
        .PSELS5     (  ),
        .PSELS6     (  ),
        .PSELS7     (  ),
        .PSELS8     (  ),
        .PSELS9     (  ),
        .PSELS10    (  ),
        .PSELS11    (  ),
        .PSELS12    (  ),
        .PSELS13    (  ),
        .PSELS14    (  ),
        .PSELS15    (  ),
        .PSELS16    (  ),
        .PRDATA     ( wubsuit_base_MSS_0_MSS_MASTER_APB_PRDATA ),
        .PADDRS     ( CoreAPB3_0_APBmslave0_PADDR ),
        .PWDATAS    ( CoreAPB3_0_APBmslave0_PWDATA ) 
        );

//--------wubsuit_base_CoreUARTapb_0_CoreUARTapb   -   Actel:DirectCore:CoreUARTapb:5.2.2
wubsuit_base_CoreUARTapb_0_CoreUARTapb #( 
        .BAUD_VAL_FRCTN    ( 2 ),
        .BAUD_VAL_FRCTN_EN ( 1 ),
        .BAUD_VALUE        ( 53 ),
        .FAMILY            ( 18 ),
        .FIXEDMODE         ( 1 ),
        .PRG_BIT8          ( 1 ),
        .PRG_PARITY        ( 0 ),
        .RX_FIFO           ( 1 ),
        .RX_LEGACY_MODE    ( 0 ),
        .TX_FIFO           ( 1 ) )
CoreUARTapb_0(
        // Inputs
        .PCLK        ( wubsuit_base_MSS_0_FAB_CLK ),
        .PRESETN     ( wubsuit_base_MSS_0_M2F_RESET_N ),
        .PSEL        ( CoreAPB3_0_APBmslave0_PSELx ),
        .PENABLE     ( CoreAPB3_0_APBmslave0_PENABLE ),
        .PWRITE      ( CoreAPB3_0_APBmslave0_PWRITE ),
        .RX          ( XBee_RX ),
        .PADDR       ( CoreAPB3_0_APBmslave0_PADDR_0 ),
        .PWDATA      ( CoreAPB3_0_APBmslave0_PWDATA_0 ),
        // Outputs
        .TXRDY       (  ),
        .RXRDY       ( RXRDY_0 ),
        .PARITY_ERR  (  ),
        .OVERFLOW    (  ),
        .TX          ( XBee_TX_net_0 ),
        .PREADY      ( CoreAPB3_0_APBmslave0_PREADY ),
        .PSLVERR     ( CoreAPB3_0_APBmslave0_PSLVERR ),
        .FRAMING_ERR (  ),
        .PRDATA      ( CoreAPB3_0_APBmslave0_PRDATA ) 
        );

//--------wubsuit_base_CoreUARTapb_1_CoreUARTapb   -   Actel:DirectCore:CoreUARTapb:5.2.2
wubsuit_base_CoreUARTapb_1_CoreUARTapb #( 
        .BAUD_VAL_FRCTN    ( 0 ),
        .BAUD_VAL_FRCTN_EN ( 0 ),
        .BAUD_VALUE        ( 1 ),
        .FAMILY            ( 18 ),
        .FIXEDMODE         ( 0 ),
        .PRG_BIT8          ( 0 ),
        .PRG_PARITY        ( 0 ),
        .RX_FIFO           ( 1 ),
        .RX_LEGACY_MODE    ( 0 ),
        .TX_FIFO           ( 1 ) )
CoreUARTapb_1(
        // Inputs
        .PCLK        ( wubsuit_base_MSS_0_FAB_CLK ),
        .PRESETN     ( wubsuit_base_MSS_0_M2F_RESET_N ),
        .PSEL        ( CoreAPB3_0_APBmslave1_PSELx ),
        .PENABLE     ( CoreAPB3_0_APBmslave0_PENABLE ),
        .PWRITE      ( CoreAPB3_0_APBmslave0_PWRITE ),
        .RX          ( MIDI_RX ),
        .PADDR       ( CoreAPB3_0_APBmslave0_PADDR_1 ),
        .PWDATA      ( CoreAPB3_0_APBmslave0_PWDATA_1 ),
        // Outputs
        .TXRDY       (  ),
        .RXRDY       ( RXRDY_net_0 ),
        .PARITY_ERR  ( PARITY_ERR ),
        .OVERFLOW    ( OVERFLOW ),
        .TX          ( MIDI_TX_net_0 ),
        .PREADY      ( CoreAPB3_0_APBmslave1_PREADY ),
        .PSLVERR     ( CoreAPB3_0_APBmslave1_PSLVERR ),
        .FRAMING_ERR ( FRAMING_ERR ),
        .PRDATA      ( CoreAPB3_0_APBmslave1_PRDATA ) 
        );

//--------wubsuit_base_CoreUARTapb_2_CoreUARTapb   -   Actel:DirectCore:CoreUARTapb:5.2.2
wubsuit_base_CoreUARTapb_2_CoreUARTapb #( 
        .BAUD_VAL_FRCTN    ( 0 ),
        .BAUD_VAL_FRCTN_EN ( 0 ),
        .BAUD_VALUE        ( 1 ),
        .FAMILY            ( 18 ),
        .FIXEDMODE         ( 0 ),
        .PRG_BIT8          ( 0 ),
        .PRG_PARITY        ( 0 ),
        .RX_FIFO           ( 1 ),
        .RX_LEGACY_MODE    ( 0 ),
        .TX_FIFO           ( 1 ) )
CoreUARTapb_2(
        // Inputs
        .PCLK        ( wubsuit_base_MSS_0_FAB_CLK ),
        .PRESETN     ( wubsuit_base_MSS_0_M2F_RESET_N ),
        .PSEL        ( CoreAPB3_0_APBmslave2_PSELx ),
        .PENABLE     ( CoreAPB3_0_APBmslave0_PENABLE ),
        .PWRITE      ( CoreAPB3_0_APBmslave0_PWRITE ),
        .RX          ( VCC_net ),
        .PADDR       ( CoreAPB3_0_APBmslave0_PADDR_2 ),
        .PWDATA      ( CoreAPB3_0_APBmslave0_PWDATA_2 ),
        // Outputs
        .TXRDY       (  ),
        .RXRDY       (  ),
        .PARITY_ERR  (  ),
        .OVERFLOW    (  ),
        .TX          ( LCD_TX_net_0 ),
        .PREADY      ( CoreAPB3_0_APBmslave2_PREADY ),
        .PSLVERR     ( CoreAPB3_0_APBmslave2_PSLVERR ),
        .FRAMING_ERR (  ),
        .PRDATA      ( CoreAPB3_0_APBmslave2_PRDATA ) 
        );

//--------fastTimer
fastTimer fastTimer_0(
        // Inputs
        .pclk   ( wubsuit_base_MSS_0_FAB_CLK ),
        .nreset ( wubsuit_base_MSS_0_M2F_RESET_N ),
        // Outputs
        .fabint ( fastTimer_0_fabint ) 
        );

//--------timer
timer timer_0(
        // Inputs
        .pclk   ( wubsuit_base_MSS_0_FAB_CLK ),
        .nreset ( wubsuit_base_MSS_0_M2F_RESET_N ),
        // Outputs
        .fabint ( FABINT ) 
        );

//--------wubsuit_base_MSS
wubsuit_base_MSS wubsuit_base_MSS_0(
        // Inputs
        .UART_0_RXD  ( UART_0_RXD ),
        .MSS_RESET_N ( MSS_RESET_N ),
        .MSSPREADY   ( wubsuit_base_MSS_0_MSS_MASTER_APB_PREADY ),
        .MSSPSLVERR  ( wubsuit_base_MSS_0_MSS_MASTER_APB_PSLVERR ),
        .F2M_GPI_0   ( RXRDY_0 ),
        .F2M_GPI_8   ( CButton3 ),
        .F2M_GPI_7   ( CButton2 ),
        .F2M_GPI_6   ( CButton1 ),
        .F2M_GPI_5   ( CButton0 ),
        .F2M_GPI_4   ( RPiezo ),
        .F2M_GPI_3   ( LPiezo ),
        .F2M_GPI_2   ( CapButton ),
        .F2M_GPI_1   ( RXRDY_net_0 ),
        .F2M_GPI_9   ( FABINT ),
        .MSSPRDATA   ( wubsuit_base_MSS_0_MSS_MASTER_APB_PRDATA ),
        .F2M_GPI_10  ( fastTimer_0_fabint ),
        // Outputs
        .UART_0_TXD  ( UART_0_TXD_net_0 ),
        .FAB_CLK     ( wubsuit_base_MSS_0_FAB_CLK ),
        .MSSPSEL     ( wubsuit_base_MSS_0_MSS_MASTER_APB_PSELx ),
        .MSSPENABLE  ( wubsuit_base_MSS_0_MSS_MASTER_APB_PENABLE ),
        .MSSPWRITE   ( wubsuit_base_MSS_0_MSS_MASTER_APB_PWRITE ),
        .M2F_RESET_N ( wubsuit_base_MSS_0_M2F_RESET_N ),
        .MSSPADDR    ( wubsuit_base_MSS_0_MSS_MASTER_APB_PADDR ),
        .MSSPWDATA   ( wubsuit_base_MSS_0_MSS_MASTER_APB_PWDATA ) 
        );


endmodule
