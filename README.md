# LED-Matrix-Display-Driver-Library NuMaker Uno 131
 
Demo Video: [[Link]](https://www.youtube.com/watch?v=Rvaf9_4eRo0)

## About Library 

This library is forked from LED-Matrix-Display-Driver-Library STM32. The source code to work with . With simple modification, this library can be compatable with more MCUs.

- MCU: NuMaker 131 Uno
    - The driver and gpio is controlled by "NUC131Series_BSP_CMSIS_v3.00.004" and set directly to register. 

- Display size: 64x32
- Color: RGB332
- Hue: 4 each R,G,B
    - If you want to change it to different RGB format or display size. You need to recalculate for buffer size and modify display fuctions.

- If you want SD Card support, you can look at [ChaN's FatFS](http://elm-chan.org/fsw/ff/00index_e.html). 

## Pin Configuration 

If you are using NuMaker 131 Uno board, you can directly use this pin config.

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