#include "TimeLib.h"
#include "driver.h"

#include "img_hue232.h"

void setup() {
  // Serial.begin(9600);

  displayInit();
  displaySetBrightness(40);

  displayGoTo(0, 0);
  displayLoadImage(hue);
  displayGoTo(31, 0);
  displayLoadImage(hue);

  // displayFill(COLOR(RED));

}
void loop() {
  //RGB332
  refreshDisplay();
  displayDelay(50);
}
