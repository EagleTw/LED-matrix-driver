# LED-matrix-driver on NuMaker Uno 131

Demo Video: [[Link]](https://www.youtube.com/watch?v=Rvaf9_4eRo0)

# Overview

This project provides a driver for a 64x32 RGB LED matrix, utilizing the NuMaker Uno 131 microcontroller. It is adapted from the [LED-Matrix-Display-Driver-Library STM32](https://github.com/OptoLAB/LED-Matrix-Display-Driver-STM32) to function seamlessly with the NuMaker platform. With minor modifications, this library can be compatible with various other microcontrollers.

## Feature

- **Microcontroller:** NuMaker 131 Uno
  - Driver and GPIO are managed using the "NUC131Series_BSP_CMSIS_v3.00.004" and are set directly to the register level.
- **Display Specifications:**
  - **Resolution:** 64x32 pixels
  - **Color Depth:** RGB332
  - **Hue Levels:** 4 each for Red, Green, and Blue channels

*Note:* To adapt this driver for different RGB formats or display sizes, you'll need to recalculate the buffer size and modify the display functions accordingly.

*Note:* If you want SD Card support, you can look at [ChaN's FatFS](http://elm-chan.org/fsw/ff/00index_e.html).

## Pin Configuration

For users employing the NuMaker 131 Uno board, the following GPIO pin configuration is recommended:

| Line | GPIO Pin |
| ---- | -------- |
| R0   | PF4      |
| G0   | PF5      |
| B0   | PA10     |
| GND  | GND PIN  |
| R1   | PA11     |
| G1   | PA15     |
| B1   | PE5      |
| GND  | GND PIN  |
| A    | PA0      |
| B    | PA1      |
| C    | PA2      |
| D    | PA3      |
| CLK  | PB11     |
| LAT  | PA14     |
| OE   | PA13     |
| GND  | PA12     |

The pin setting funnction in DisplayInit() function is defined by "NUC131Series_BSP_CMSIS_v3.00.004",  which can be found in the NuVoton's website

## Before running the code

You need to install the corresponding board from "tools->boards manager"
In NuMaker 131 Uno, Install "NuMaker UNO"

## How to run example
1. create a directory with the same name as example/_____.ino
2. copy ____.ino in to the directory you just created
3. copy all documents in "src" inside the directory
4. open .ino and run code

## How to display image?

1. Convert your image file to .bmp
2. Use bmp2h.py to convert to byte array(.h) file
3. Inclue .h file to .iso
4. use displayLoadImage() function

## Adding New Font Style
same as logic displaying image


// Global variables
// Copyright (c) 2020 YPPAN, LEXTAR
