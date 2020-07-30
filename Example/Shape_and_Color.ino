#include "TimeLib.h"
#include "driver.h"


void setup() {
  displayInit();
  displaySetBrightness(40);

  displayGoTo(5, 4);
  displayDrawRectangle(20,20,COLOR(AQUAMARINE),COLOR(PURPLE));

  displayGoTo(47, 17);
  displayDrawCircle(11,COLOR(YELLOW),COLOR(RED));
}
void loop() {
  refreshDisplay();
  displayDelay(15);
}
