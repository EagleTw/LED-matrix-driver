#include <time.h>
#include "TimeLib.h"
#include "driver.h"

int rtc[7];   // Holds real time clock output

void refreshClock() {
  rtc[0] =  second(); // The second now (0-59)
  rtc[1] =  minute(); // The minute now (0-59)
  rtc[2] =  hour();   // The hour now (0-23)
  rtc[3] =  day();    // The day now (1-31)
  rtc[4] =  weekday(); // Day of the week (1-7), Sunday is day 1
  rtc[5] =  month();  // The month now (1-12)
  rtc[6] =  year();   // The full four digit year: (2009,2010 etc)
}

const void int2strTime(char *str) {
  sprintf(str, "%02d:%02d:%02d", rtc[2], rtc[1], rtc[0]);
}
const void int2strDate(char *str) {
  sprintf(str, "%02d/%02d/%02d", rtc[6], rtc[5], rtc[3]);
}
const void displayClock() {
  char strTime[20] = "HH:MM:SS";
  char strDate[30] = "YYYY/MM/DD";

  displayClear();

  refreshClock();

  int2strTime(strTime);
  displayGoTo(3, 6);
  displaySetFont(DEFAULT_BIG);
  displayPrint(strTime, COLOR(CRIMSON));

  int2strDate(strDate);
  displayGoTo(3, 22);
  displaySetFont(TERMINAL_6X8);
  displayPrint(strDate, COLOR(SALMON));
}


void setup() {
  Serial.begin(9600);
  displayInit();

  setTime(13, 27, 00, 30, 7, 20);

  displaySetBrightness(40);
  displayGoTo(0, 0);
}
void loop() {
  //refreshClock();
  displayClock();
  refreshDisplay();
  DELAY(80);
}
