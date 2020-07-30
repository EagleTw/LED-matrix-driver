#include "TimeLib.h"
#include "driver.h"


void setup() {
  displayInit();
  displaySetBrightness(40);

  displayGoTo(0+3, 1);
  displaySetFont(ARIAL_16X19);
  displayPrint("L", COLOR(RED));

  displayGoTo(10+3, 1);
  displaySetFont(ARIAL_16X19);
  displayPrint("U", COLOR(ORANGE));

  displayGoTo(22+3, 1);
  displaySetFont(ARIAL_16X19);
  displayPrint("M", COLOR(YELLOW));

  displayGoTo(36+3, 1);
  displaySetFont(ARIAL_16X19);
  displayPrint("E", COLOR(GREEN));

  displayGoTo(47+3, 1);
  displaySetFont(ARIAL_16X19);
  displayPrint("X", COLOR(BLUE));

  displayGoTo(3, 18);
  displaySetFont(DEFAULT_BIG);
  displayPrint("P5", COLOR(WHITE));

  displayGoTo(30, 23);
  displaySetFont(DEFAULT_SMALL);
  displayPrint("64x32", COLOR(MAGENTA));


  //  displayGoTo(38, 19);
  //  displaySetFont(TERMINAL_6X8);
  //  displayPrint("TEST", COLOR(GREEN));
}
void loop() {
  refreshDisplay();
  displayDelay(15);
}
