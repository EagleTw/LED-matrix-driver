//------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "displayBoardConfig.h"
#include "displayTypeDefs.h"
#include "utils_fonts.h"
#include "utils_gamma.h"
#include "utils_colors.h"
#include "Timer.h"

// font
#include "Courier9x13.h"
#include "Arial16x19.h"
#include "Victorian_LET16x26.h"
#include "Terminal6x8.h"


//------------------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------------------
color_t FRAME_BUFF[64 + 64][32] = {0}; // X: 0~63 display area; x:64~127 buffer area
uint8_t BITS_PER_CHANNEL = BPC;
uint16_t BRIGHTNESS = 10;
font_t SELECTED_FONT = {0};

uint8_t positionX = 0;
uint8_t positionY = 0;
uint8_t strEndX = 0;

#define DELAY(X) refreshDelay(X)

//------------------------------------------------------------------------------------------
// DISPLAY CONTROL FUNCTIONS
// clock, latch, selectRow, setTopColor, setBottomColor
//------------------------------------------------------------------------------------------
void clock_low_high() { // Data shift atClock Rising edge
  CLK = 0;
  CLK = 1;
}
void clock_high_low() {
  CLK = 1;
  CLK = 0;
}
static void latch(void) {
  LAT = 1;
  LAT = 0;
}
void selectRow(uint8_t x) {
  A_PIN = (x & 0x01);
  B_PIN = ((x & 0x02) >> 1);
  C_PIN = ((x & 0x04) >> 2);
  D_PIN = ((x & 0x08) >> 3);
}
static void setColor(uint8_t x, uint8_t y, uint8_t cCycle) {
  int r0, g0, b0, r1, g1, b1;
  (cCycle >= rCh(FRAME_BUFF[x][y])) ? R0 = 0 : R0 = 1;
  (cCycle >= gCh(FRAME_BUFF[x][y])) ? G0 = 0 : G0 = 1;
  (cCycle >= bCh(FRAME_BUFF[x][y])) ? B0 = 0 : B0 = 1;

  (cCycle >= rCh(FRAME_BUFF[x][y + 16])) ? R1 = 0 : R1 = 1;
  (cCycle >= gCh(FRAME_BUFF[x][y + 16])) ? G1 = 0 : G1 = 1;
  (cCycle >= bCh(FRAME_BUFF[x][y + 16])) ? B1 = 0 : B1 = 1;
}

//------------------------------------------------------------------------------------------
// DISPLAY REFRESH FUNCTIONS
// refreshDisplay, displaySetBrightness
//------------------------------------------------------------------------------------------
void refreshDisplay(void)
{
  static const uint8_t scanSeq[16] = {0, 1, 8, 9, 4, 5, 12, 13, 2, 3, 10, 11, 6, 7, 14, 15};    // Scanning sequence

  for (uint8_t y = 0; y < 16 ; y++) {
    int z = scanSeq[y];
    selectRow(z);
    for ( uint8_t cCycle = 1; cCycle < 4; cCycle++) {
      for (uint8_t x = 0; x < 64; x++) {
        clock_high_low();
        setColor(x , z , cCycle);
        clock_low_high();
      }
      CLK = 0;
      latch();

      OE = 0;
      delayMicroseconds(BRIGHTNESS);
      // delay(3000);
      OE = 1;
      delayMicroseconds(1);
    }
  }
}
void displaySetBrightness(uint8_t level) {
  BRIGHTNESS = level;
}


//------------------------------------------------------------------------------------------
// DISPLAY FILL FUNCTIONS
// displayFillArea, displayFill, displayFillNoise, displayClear
//------------------------------------------------------------------------------------------
void displayFillArea(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, color_t color)
{
  uint16_t x, y;

  for (y = y1; y < y2; y++) {
    for (x = x1; x < x2; x++)
      setFRAMEpx(x, y, color);
  }
}
void displayFill(color_t color)
{
  uint16_t x, y;
  for (y = 0; y < PANEL_HEIGHT; y++) {
    for (x = 0; x < 128; x++)
      setFRAMEpx(x, y, color);
  }
}
void displayFillNoise(void)
{
  uint16_t x, y;
  for (y = 0; y < PANEL_HEIGHT; y++) {
    for (x = 0; x < PANEL_WIDTH; x++)
      setFRAMEpx(x, y, COLOR(rand() * (0xFFFFFF)));
  }
}
void displayClear(void)
{
  displayFill(COLOR(0));
}
//------------------------------------------------------------------------------------------
// DISPLAY DELAY FUNCTIONS
// displayDelay
//------------------------------------------------------------------------------------------
void refreshDelay(uint16_t x_times)
{
  uint16_t i;
  for (i = 0; i < x_times; i++)
  {
    refreshDisplay();
  }
}
void displayDelay(uint16_t time)
{
    DELAY(time);
}
//------------------------------------------------------------------------------------------
// DISPLAY DRAW FUNCTIONS
// displaySetPixel, displayDrawRectangle, displayDrawCircle
//------------------------------------------------------------------------------------------
void displaySetPixel(uint16_t x, uint16_t y, color_t color) {
  setFRAMEpx(x, y, color);
}

void displayDrawRectangle(uint16_t width, uint16_t height, color_t line_color, color_t fill_color) {
  uint16_t x = 0, y = 0, x1, y1;

  x1 = positionX;
  y1 = positionY;

  for (x = 0; x < (width + 1); x++) {
    displaySetPixel((x1 + x), y1, line_color);
    displaySetPixel((x1 + x), y1 + height, line_color);
  }

  for (y = 0; y < (height + 1); y++) {
    displaySetPixel(x1, y1 + y, line_color);
    displaySetPixel(x1 + width, y1 + y, line_color);
  }

  for (x = 1; x < (width); x++) {
    for (y = 1; y < (height); y++) {
      displaySetPixel(x1 + x, y1 + y, fill_color);
    }
  }
}

void displayDrawCircle(uint16_t radius, color_t line_color, color_t fill_color)
{
  int sw = 0, intY = 0, intX = 0, i;
  uint16_t d, x, y;

  x = positionX;
  y = positionY;
  d = y - x;
  intY = radius;
  sw = 3 - 2 * radius;

  while (intX <= intY) {
    for (i = (y - (uint8_t)intY) + 1; i < (y + (uint8_t)intY); i++) {
      displaySetPixel(((uint8_t)(x - intX)), i, fill_color);
      displaySetPixel(((uint8_t)(x + intX)), i, fill_color);
    }

    displaySetPixel(((uint8_t)(x + intX)), y + (uint8_t)intY, line_color);
    displaySetPixel(((uint8_t)(x + intX)), y - (uint8_t)intY, line_color);
    displaySetPixel(((uint8_t)(x - intX)), y + (uint8_t)intY, line_color);
    displaySetPixel(((uint8_t)(x - intX)), y - (uint8_t)intY, line_color);


    for (i = (y - (uint8_t)intX); i < (y + (uint8_t)intX) + 1; i++) {
      displaySetPixel(((uint8_t)(y + intY - d)) - 1, i, fill_color);
      displaySetPixel(((uint8_t)(y - intY - d)) + 1, i, fill_color);
    }
    displaySetPixel(((uint8_t)(y + intY - d)), y + (uint8_t)intX, line_color);
    displaySetPixel(((uint8_t)(y + intY - d)), y - (uint8_t)intX, line_color);
    displaySetPixel(((uint8_t)(y - intY - d)), y + (uint8_t)intX, line_color);
    displaySetPixel(((uint8_t)(y - intY - d)), y - (uint8_t)intX, line_color);

    if (sw < 0) sw += (4 * intX + 6);
    else {
      sw += (4 * (intX - intY) + 10);
      intY--;
    }
    intX++;
  }
}
// for debugging use
void printBuff(void) {
  Serial.print(" Buff Print\n");
  for (int y = 0; y < 32; y++) {
    for (int x = 0; x < 64; x++) {
      Serial.print(FRAME_BUFF[x][y].color);
    }
    Serial.println();
  }
}
//------------------------------------------------------------------------------------------
// DISPLAY PRINT FUNCTIONS
// displayGoTo, displaySetFont, displayNewLine, displayPutChar, displayPrint
//------------------------------------------------------------------------------------------

void displayGoTo(uint16_t x, uint16_t y)
{
  x = x % DISPLAY_WIDTH;
  y = y % DISPLAY_HEIGHT;
  positionX = x;
  positionY = y;
}
void displaySetFont(font_t font) {
  SELECTED_FONT = font;
}
/*
   Function: displayNewLine
   --------------------
   clear screen if screen is too small for text
*/
void displayNewLine(void) {
  positionX = 0;
  if ((positionY + SELECTED_FONT.height + 1) >= DISPLAY_HEIGHT) {
    positionY = 0;
    displayClear(); // original way
  }
  else positionY += SELECTED_FONT.height + 1;
}
void displayPutChar(char c, color_t color)
{
  uint16_t x, y, char_offset;
  uint8_t i, j;
  unsigned long long data;

  if (c <= SELECTED_FONT.last_char)
  {
    j = SELECTED_FONT.height / 8; // bytes per char
    if (SELECTED_FONT.height % 8 != 0)j++;
    char_offset = (c - SELECTED_FONT.first_char) * (j * SELECTED_FONT.width + 1);

    // if ((positionX+ SELECTED_FONT.chars[char_offset] - 1) >= DISPLAY_WIDTH)displayNewLine(); // Original handling wa

    for (x = 1; x <= SELECTED_FONT.chars[char_offset]; x++)
    {
      data = 0;
      for (i = 0; i < j; i++)data |= (SELECTED_FONT.chars[char_offset + j * (x - 1) + i + 1] & 0xFF) << (i * 8);

      if (x != 1 || data != 0) // skip if starts with blank line
      {
        for (y = 0; y < (SELECTED_FONT.height + 1); y++)
        {
          if ((data >> y) & 0x01) displaySetPixel(positionX, positionY, color);
          positionY++;
        }
        positionX++;
        positionY = positionY - (SELECTED_FONT.height + 1);
      }
    }
    positionX++; // blank line at the end of char
  }
}

bool displayPutCharInBuffer(char c, color_t color)
{
  uint16_t x, y, char_offset;
  uint8_t i, j;
  unsigned long long data;

  if (c <= SELECTED_FONT.last_char)
  {
    j = SELECTED_FONT.height / 8; // bytes per char
    if (SELECTED_FONT.height % 8 != 0)j++;
    char_offset = (c - SELECTED_FONT.first_char) * (j * SELECTED_FONT.width + 1);

    if ((strEndX + SELECTED_FONT.chars[char_offset] - 1) >= 128) {
      strEndX = positionX;
      return 0;
    }
    for (x = 1; x <= SELECTED_FONT.chars[char_offset]; x++)
    {
      data = 0;
      for (i = 0; i < j; i++)data |= (SELECTED_FONT.chars[char_offset + j * (x - 1) + i + 1] & 0xFF) << (i * 8);

      if (x != 1 || data != 0) // skip if starts with blank line
      {
        for (y = 0; y < (SELECTED_FONT.height + 1); y++)
        {
          if ((data >> y) & 0x01) displaySetPixel(positionX, positionY, color);
          positionY++;
        }
        positionX++;
        positionY = positionY - (SELECTED_FONT.height + 1);
      }
    }
    positionX++; // blank line at the end of char
    return 1;
  }
}

void displayPrint(char *text, color_t color)
{
  while (*text != 0)
  {
    displayPutChar(*text, color);
    text++;
  }
}

//------------------------------------------------------------------------------------------
// DISPLAY SCROLL&MIRROR FUNCTIONS
// displayScrollLeft
//------------------------------------------------------------------------------------------
/*
   Function: displayScrollLeft
   --------------------
   from line y1 to y2, scroll left
*/
static void displayScrollLeft(uint8_t y1, uint8_t y2)
{
  uint16_t x, y = y1, last_column;
  uint32_t line = 0;
  color_t temp = {{0, 0, 0}};

  for (y = y1; y < y2; y++) {
    strEndX --;
    for (x = 0; x < 128; x++) {
      if (x == 0)
        temp = getFRAMEpx(x, y);
      setFRAMEpx(x, y, getFRAMEpx(x + 1, y));
    }
    if (x == 128)
      setFRAMEpx(x, y, temp);
  }
}
//------------------------------------------------------------------------------------------
// DISPLAY COLOR FUNCTIONS
// RGB, HSV
//------------------------------------------------------------------------------------------
uint32_t RGB(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r << 16) | (g << 8) | b);
}
uint32_t convertRGB(const unsigned char src, const unsigned char dst, uint32_t color)
{
  // color RGB332
  uint8_t r, g, b;

  r = (color >> 5) & 0x07;
  g = (color >> 2) & 0x07;
  b = (color & 0x03);
  if (dst == 0)      return (((r >> 2) << 2) | ((g >> 2) << 1) | (b >> 1));
  else if (dst == 2) return ((r << 13) | (g << 8) | (b << 3));
  else if (dst == 3) return ((r << 21) | (g << 13) | (b << 6));
  else            return color;
}
color_t gammaCorrected(color_t color)
{
  uint8_t r,g,b;
 
  r=gamma_curve[rCh(color)&chMask];
  g=gamma_curve[gCh(color)&chMask];
  b=gamma_curve[bCh(color)&chMask];
    
  return color2px(mixCh(r,g,b));
}
//------------------------------------------------------------------------------------------
// DISPLAY IMAGE FUNCTIONS
// displayLoadImage, displayLoadImageSD
//------------------------------------------------------------------------------------------
void displayLoadImage(const image_t img, uint8_t gamma_corrected)
{
    uint16_t x, y, endX, endY;
    uint32_t line, color, y_offset=0, x_offset;
    uint8_t i, bytes, pixels;
    color_t px;

    
    endX=img.width+positionX;
    endY=img.height+positionY;
    if((endX)>DISPLAY_WIDTH)endX=DISPLAY_WIDTH;
    if((endY)>DISPLAY_HEIGHT)endY=DISPLAY_HEIGHT;

    line=positionY*DISPLAY_WIDTH;  
    
    bytes=img.bytes_per_px;
    pixels=img.px_per_bytes-1;
    if(!bytes)bytes=1;

    for(y=positionY;y<endY;y++)
    {
        for(x=positionX;x<endX;x++)
        {
            color=0;
            //get pixel
            x_offset=(x-positionX)*bytes;
            for(i=0;i<bytes;i++)
                color|=img.pixels[(x_offset>>pixels)+y_offset+i]<<(i<<3); 
            if(pixels)color=(color>>((~x_offset&pixels)<<2))&0x0F; //get only nibble 
            //convert to default color format if needed
            if(img.bytes_per_px!=DEFAULT_FORMAT) color=convertRGB(img.bytes_per_px,DEFAULT_FORMAT,color);
            px=color2px(color);
            //gamma correct or not
            if(gamma_corrected)px=gammaCorrected(px);
            //update frame buffer
            setFRAMEpx(x,y,px);
        }
        line+=DISPLAY_WIDTH;
        y_offset+=(img.width)*bytes>>pixels;
    }
}



void displayInit(void) {
  // Set pin mode
  GPIO_SetMode(PF, BIT4, GPIO_PMD_OUTPUT);   // R0
  GPIO_SetMode(PF, BIT5, GPIO_PMD_OUTPUT);   // G0
  GPIO_SetMode(PA, BIT10, GPIO_PMD_OUTPUT);   // B0
  GPIO_SetMode(PA, BIT11, GPIO_PMD_OUTPUT);   // R1
  GPIO_SetMode(PA, BIT15, GPIO_PMD_OUTPUT);   // G1
  GPIO_SetMode(PE, BIT5, GPIO_PMD_OUTPUT);   // B1

  GPIO_SetMode(PA, BIT0, GPIO_PMD_OUTPUT);   // A
  GPIO_SetMode(PA, BIT1, GPIO_PMD_OUTPUT);   // B
  GPIO_SetMode(PA, BIT2, GPIO_PMD_OUTPUT);   // C
  GPIO_SetMode(PA, BIT3, GPIO_PMD_OUTPUT);   // D

  GPIO_SetMode(PB, BIT11, GPIO_PMD_OUTPUT);   // CLK
  GPIO_SetMode(PA, BIT14, GPIO_PMD_OUTPUT);   // LAT
  GPIO_SetMode(PA, BIT13, GPIO_PMD_OUTPUT);   // OE
  GPIO_SetMode(PA, BIT12, GPIO_PMD_OUTPUT);   // GND

  //set default value
  PA12 = 0; // fake ground

  A_PIN = 0;
  B_PIN = 0;
  C_PIN = 0;
  D_PIN = 0;

  CLK = 0;
  LAT = 0;
  OE = 0;
}
