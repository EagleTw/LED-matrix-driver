#include "TimeLib.h"
#include "driver.h"


void setup() {
  displayInit();
  displaySetBrightness(40);

  displayGoTo(0+2, 1);
  displaySetFont(ARIAL_16X19);
  displayPrint("L", COLOR(RED));

  displayGoTo(9+2, 1);
  displaySetFont(ARIAL_16X19);
  displayPrint("E", COLOR(ORANGE));

  displayGoTo(19+2, 1);
  displaySetFont(ARIAL_16X19);
  displayPrint("X", COLOR(YELLOW));

  displayGoTo(31+2, 1);
  displaySetFont(ARIAL_16X19);
  displayPrint("T", COLOR(GREEN));

  displayGoTo(38+2, 1);
  displaySetFont(ARIAL_16X19);
  displayPrint("A", COLOR(BLUE));

  displayGoTo(50+2, 1);
  displaySetFont(ARIAL_16X19);
  displayPrint("R", COLOR(PURPLE));


  displayGoTo(3, 18);
  displaySetFont(DEFAULT_BIG);
  displayPrint("P5", COLOR(WHITE));

  displayGoTo(30, 23);
  displaySetFont(DEFAULT_SMALL);
  displayPrint("64x32", COLOR(0xFA8072));

}
void loop() {
  refreshDisplay();
  displayDelay(15);
}
