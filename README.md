# RGB-Matrix-Driver-NuMaker

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

## Getting Started

### Prerequisites

Before running the code, ensure you have installed the required board package:

1. Open **Arduino IDE**.
2. Navigate to **Tools → Board Manager**.
3. Search for **NuMaker UNO** and install it.

### Running an Example

Follow these steps to run an example sketch:

1. Create a new directory with the **same name** as the example file (`example/_____.ino`).
2. Copy the `_____.ino` file into the newly created directory.
3. Copy all files from the `src/` directory into the same directory.
4. Open the `.ino` file in the **Arduino IDE** and upload the code to the board.

### Displaying an Image

To display an image on the LED matrix:

1. Convert your image file to **.bmp** format.
2. Use `bmp2h.py` to convert the BMP file into a **byte array (.h) file**.
3. Include the generated `.h` file in your `.ino` sketch.
4. Call the `displayLoadImage()` function to load and display the image.

### Adding a New Font Style

The process of adding a new font style follows the **same logic** as displaying an image:

1. Convert the font data into a compatible byte array.
2. Include the generated `.h` file in your project.
3. Modify the display function to support the new font style.
