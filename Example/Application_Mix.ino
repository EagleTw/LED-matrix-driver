#include "TimeLib.h"
#include "driver.h"

#include "img_hue232.h"
#include "img_babyincar.h"
#include "img_parking.h"
#include "img_pedestrian.h"

void displayPedestrian(){
  displayClear();
  
  displayGoTo(0, 0);
  displayLoadImage(pedestrian, 0);

  displayGoTo(25, 7);
  displaySetFont(DEFAULT_SMALL);
  displayPrint("PEOPLE", COLOR(SALMON));

  displayGoTo(29, 19);
  displaySetFont(DEFAULT_SMALL);
  displayPrint("AHEAD", COLOR(SALMON)); 
}
void displayParking(){
  displayClear();
  
  displayGoTo(0, 0);
  displayLoadImage(parking, 0);

  displayGoTo(36, 7);
  displaySetFont(DEFAULT_SMALL);
  displayPrint("FIND", COLOR(YELLOW));

  displayGoTo(33, 19);
  displaySetFont(DEFAULT_SMALL);
  displayPrint("SPACE", COLOR(MAGENTA));  
}
void displayBabyincar(){
  displayClear();
  
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

  

}
void loop() {
  //RGB332
  displayPedestrian();
  refreshDisplay();
  displayDelay(500);
  
  displayParking();
  refreshDisplay();
  displayDelay(500);

  displayBabyincar();
  refreshDisplay();
  displayDelay(500);
}
