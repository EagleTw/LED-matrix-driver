//------------------------------------------------------------------------------------------
// color pin & register define
//------------------------------------------------------------------------------------------
#define R0 PF4
#define G0 PF5
#define B0 PA10

#define R1 PA11
#define G1 PA15
#define B1 PE5
//---
#define A_PIN PA0  //A0
#define B_PIN PA1  //A1
#define C_PIN PA2  //A2
#define D_PIN PA3  //A3
//---
#define CLK PB11
#define LAT PA14
#define OE PA13
//-------------------------------------------------------------------
//DISPLAY SIZE
//-------------------------------------------------------------------
#define DISPLAY_WIDTH           (64)
#define DISPLAY_HEIGHT          (32)
//-------------------------------------------------------------------
//CONFIGURE PANELS
//-------------------------------------------------------------------
#define PANEL_WIDTH             (64)
#define PANEL_HEIGHT            (32)
#define NUM_OF_SELECTION_BITS   (4)
#define NUM_OF_SUBPANELS        (1) // max 4 //(R1,G1,B1)&(R2,G2,B2)&(R3,G3,B3)&(R4,G4,B4)
