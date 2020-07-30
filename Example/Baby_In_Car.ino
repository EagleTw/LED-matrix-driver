#include "TimeLib.h"
#include "driver.h"

#include "img_hue232.h"
#include "img_babyincar.h"
#include "img_parking.h"
#include "img_pedestrian.h"

void displayBabyincar(){
  displayGoTo(0, 0);
  displayLoadImage(babyincar, 0);

  displayGoTo(3, 22);
  displayDrawRectangle(25, 5, COLOR(BLACK), COLOR(BLACK));

  displayGoTo(35, 4);
  displaySetFont(TERMINAL_6X8);
  displayPrint("BABY", COLOR(YELLOW));

  displayGoTo(34, 13);
  displaySetFont(TERMINAL_6X8);
  displayPrint("IN", COLOR(YELLOW));

  displayGoTo(35, 22);
  displaySetFont(TERMINAL_6X8);
  displayPrint("CAR", COLOR(YELLOW));

  
}

void setup() {
  // Serial.begin(9600);

  displayInit();
  displaySetBrightness(40);

  displayBabyincar();

}
void loop() {
  //RGB332
  refreshDisplay();
  displayDelay(50);
}
