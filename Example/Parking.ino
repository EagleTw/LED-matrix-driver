#include "TimeLib.h"
#include "driver.h"

#include "img_hue232.h"
#include "img_babyincar.h"
#include "img_parking.h"
#include "img_pedestrian.h"

void displayParking(){
  displayGoTo(0, 0);
  displayLoadImage(parking, 0);

  displayGoTo(36, 7);
  displaySetFont(DEFAULT_SMALL);
  displayPrint("FIND", COLOR(YELLOW));

  displayGoTo(33, 19);
  displaySetFont(DEFAULT_SMALL);
  displayPrint("SPACE", COLOR(MAGENTA));

  
}

void setup() {
  // Serial.begin(9600);

  displayInit();
  displaySetBrightness(40);

  displayParking();

}
void loop() {
  //RGB332
  refreshDisplay();
  displayDelay(50);
}
