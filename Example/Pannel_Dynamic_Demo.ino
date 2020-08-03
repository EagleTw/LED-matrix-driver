#include "TimeLib.h"
#include "driver.h"

#include "img_hue232.h"

void LineShiftRight(uint8_t y) {
  for (int x = 63; x >= 0; x--) {
    if (x == 0)  displaySetPixel(x, y, COLOR(BLACK));
    else displaySetPixel(x, y, getFRAMEpx(x - 1, y));
  }
}
void LineShiftLeft(uint8_t y) {
  for (int x = 0; x <= 63; x++) {
    if (x == 63) displaySetPixel(x, y, COLOR(BLACK));
    else displaySetPixel(x, y, getFRAMEpx(x + 1, y));
  }
}

void worm() {
  uint8_t worm_delay = 1;
  color_t tmp_color;

  for (uint8_t cnt = 0; cnt < 8; cnt++) {
    tmp_color = COLOR(rand() * (0xFFFFFF));

    for (uint8_t x = 0; x <= 16; x++) {
      displaySetPixel(x, 4 * cnt + 0, tmp_color);
      displaySetPixel(x, 4 * cnt + 1, tmp_color);
      displayDelay(worm_delay);
    }
    for (uint8_t i = 0; i < 64; i++) {
      LineShiftRight(4 * cnt + 0);
      LineShiftRight(4 * cnt + 1);
      displayDelay(worm_delay);
    }

    tmp_color = COLOR(rand() * (0xFFFFFF));

    for (uint8_t x = 0; x <= 16; x++) {
      displaySetPixel(63 - x, 4 * cnt + 2, tmp_color);
      displaySetPixel(63 - x, 4 * cnt + 3, tmp_color);
      displayDelay(worm_delay);
    }
    for (uint8_t i = 0; i < 64; i++) {
      LineShiftLeft(4 * cnt + 2);
      LineShiftLeft(4 * cnt + 3);
      displayDelay(worm_delay);
    }
  }
}

void crossColor() {
  uint8_t cross_delay = 5;

  color_t tmp_color1 = COLOR(0);
  color_t tmp_color2 = COLOR(0);


  tmp_color1 = COLOR(rand() * (0xFFFFFF));
  tmp_color2 = COLOR(rand() * (0xFFFFFF));

  for (uint8_t x = 0; x <= 20; x++) {
    for (uint8_t y = 0; y < 32; y++) {
      if (y % 2 == 0)  displaySetPixel(x, y, tmp_color1);
      else displaySetPixel(63 - x, y, tmp_color2);
    }
    displayDelay(cross_delay);
  }
  for (uint8_t i = 0; i < 64; i++) {
    for (uint8_t y = 0; y < 32; y++) {
      if (y % 2 == 0)  LineShiftRight(y);
      else LineShiftLeft(y);
    }
    displayDelay(cross_delay);
  }
}
void noSignal() {
  for (uint8_t i = 0; i < 200; i++) {
    displayFillNoise();
    displayGoTo(4, 11);
    displayDrawRectangle(56, 8, COLOR(BLACK), COLOR(BLACK));

    displayGoTo(5, 12);
    displaySetFont(TERMINAL_6X8);
    displayPrint("NO SIGNAL!", COLOR(YELLOW));

    displayDelay(1);
  }
  displayClear();
}
void couplingEffect() {
  for (uint8_t j = 0; j < 4; j++) {
    for (uint8_t i = 0; i < 8; i++) {
      displayGoTo(0 + 16 * i, 0 + 16 * j);
      displayDrawRectangle(7, 7, COLOR(WHITE), COLOR(WHITE));
      displayGoTo(8 + 16 * i, 8 + 16 * j);
      displayDrawRectangle(7, 7, COLOR(WHITE), COLOR(WHITE));
    }
  }
  displayDelay(300);

  for (uint8_t i = 0; i < 64; i++) {
    displayScrollLeft(8, 24);
    displayDelay(5);
  }

  displayGoTo(1, 9);
  displaySetFont(TERMINAL_6X8);
  displayPrint("NO COUPLING", COLOR(SALMON));

  displayGoTo(15, 17);
  displaySetFont(TERMINAL_6X8);
  displayPrint("EFFECT", COLOR(SALMON));

  displayDelay(450);
  displayClear();
}

void setup() {
  displayInit();
  displaySetBrightness(45);
}
void loop() {
  displayClear();
  refreshDisplay();

  worm();
  crossColor();
  crossColor();
  crossColor();
  crossColor();

  displayDelay(60);

  displayFill(COLOR(RED));
  displayDelay(300);
  displayClear();

  displayFill(COLOR(GREEN));
  displayDelay(300);
  displayClear();

  displayFill(COLOR(BLUE));
  displayDelay(300);
  displayClear();

  displayGoTo(0, 0);
  displayLoadImage(hue, 0);
  displayGoTo(31, 0);
  displayLoadImage(hue, 0);
  displayDelay(600);
  displayClear();

  couplingEffect();

  noSignal();

  displayClear();
}
