#include "TimeLib.h"
#include "driver.h"


void setup() {
  displayInit();
  displaySetBrightness(40);

  displayGoTo(0, 0);
  displaySetFont(DEFAULT_EXTRA_SMALL);
  displayPrint("TEST", COLOR(MAGENTA));
  displayGoTo(0, 8);
  displaySetFont(DEFAULT_SMALL);
  displayPrint("THIS IS A FONT DEMO ", COLOR(CYAN));
  displayGoTo(0, 16);
  displaySetFont(DEFAULT_BIG);
  displayPrint("TEST", COLOR(YELLOW));

  displayGoTo(38, 19);
  displaySetFont(TERMINAL_6X8);
  displayPrint("TEST", COLOR(GREEN));
}
void loop() {
  refreshDisplay();
  displayDelay(15);
  displayScrollLeft(8, 16);
}
