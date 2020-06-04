/** @file   pixel.cc
 *  @brief  Contains definitions of methods of the pixel 
 *          class defined in bmp.h
 *  @author Mustafa Siddiqui
 *  @date   06/01/2020
 */

#include "bmp.h"

// default constructor
Pixel::Pixel() {}

// constructor
Pixel::Pixel(std::istream &is) {
    Pixel::read(is);
}

// deconstructor
Pixel::~Pixel(void) {}

// convert pixel to hsv format
void Pixel::convertToHSV(void) {
    HSV_Colors = rgb_to_hsv(RGB_Colors);
}

// convert pixel to rgb format
void Pixel::convertToRGB(void) {
    RGB_Colors = hsv_to_rgb(HSV_Colors);
}

// change colors of pixel
void Pixel::changeColors(int colorChoice) {

    // convert to HSV
    convertToHSV();
    
    // red
    if (colorChoice == 1) {
        if (HSV_Colors.hue > 20 && HSV_Colors.hue < 340) {
            HSV_Colors.saturation = 0;
        }
    }
    // yellow
    else if (colorChoice == 2) {
        if (HSV_Colors.hue < 50 || HSV_Colors.hue > 70) {
            HSV_Colors.saturation = 0;
        }
    }
    // orange
    else  if (colorChoice == 3) {
        if (HSV_Colors.hue < 20 || HSV_Colors.hue > 50) {
            HSV_Colors.saturation = 0;
        }
    }
    // green
    else if (colorChoice == 4) {
        if (HSV_Colors.hue < 60 || HSV_Colors.hue > 160) {
            HSV_Colors.saturation = 0;
        }
    }
    // blue
    else if (colorChoice == 5) {
        if (HSV_Colors.hue < 160 || HSV_Colors.hue > 230) {
            HSV_Colors.saturation = 0;
        }
    }
    // this case is never going to happen since colorChoice is validated in main()
    else {
        std::cout << "Invalid Color Choice\n";
    }

    // convert to RGB again
    convertToRGB();
}

// to write Pixel object into file in binary format
void Pixel::write(std::ostream &os) {
    os.write((char*)&RGB_Colors.blue, sizeof(BYTE));
    os.write((char*)&RGB_Colors.green, sizeof(BYTE));
    os.write((char*)&RGB_Colors.red, sizeof(BYTE));
}

// to read Pixel object from file in binary format
void Pixel::read(std::istream &is) {
    is.read((char*)&RGB_Colors.blue, sizeof(BYTE));
    is.read((char*)&RGB_Colors.green, sizeof(BYTE));
    is.read((char*)&RGB_Colors.red, sizeof(BYTE));
}