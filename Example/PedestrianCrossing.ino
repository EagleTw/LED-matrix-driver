#include "TimeLib.h"
#include "driver.h"

#include "img_hue232.h"
#include "img_babyincar.h"
#include "img_parking.h"
#include "img_pedestrian.h"

void displayParking(){
  displayGoTo(0, 0);
  displayLoadImage(pedestrian, 0);

  displayGoTo(25, 7);
  displaySetFont(DEFAULT_SMALL);
  displayPrint("PEOPLE", COLOR(SALMON));

  displayGoTo(29, 19);
  displaySetFont(DEFAULT_SMALL);
  displayPrint("AHEAD", COLOR(SALMON)); 
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
