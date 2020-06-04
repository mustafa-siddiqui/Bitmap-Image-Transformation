/** @file   bmp.h
 *  @brief  Header file containing definitions for the pixel class
 *          and its methods along with the bitmap structures.
 *  @author Mustafa Siddiqui
 *  @date   06/01/2020
 */

#ifndef BMP_H
#define BMP_H

/* Include necessary libraries */
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
//--//
#include <iostream>
#include <string>

// aliases for C/C++ primitive data types
// https://msdn.microsoft.com/en-us/library/cc230309.aspx
typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

// information about the type, size, and layout of a file
// https://msdn.microsoft.com/en-us/library/dd183374(v=vs.85).aspx
typedef struct {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} __attribute__((__packed__))
BITMAPFILEHEADER;

// information about the dimensions and color format
// https://msdn.microsoft.com/en-us/library/dd183376(v=vs.85).aspx
typedef struct {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} __attribute__((__packed__))
BITMAPINFOHEADER;

// relative intensities of red, green, and blue
// https://msdn.microsoft.com/en-us/library/dd162939(v=vs.85).aspx
typedef struct {
    BYTE blue;
    BYTE green;
    BYTE red;
} __attribute__((__packed__))
RGB;

// Alternative representation of RGB model in terms of hue, saturation and value
// http://learn.leighcotnoir.com/artspeak/elements-color/hue-value-saturation/
typedef struct {
    double hue;
    double saturation;
    double value;
} __attribute__((__packed__))
HSV;

// to covert one pixel's data from RGB to HSV domain
// https://www.rapidtables.com/convert/color/rgb-to-hsv.html
HSV rgb_to_hsv(RGB In_RGB);

// to covert one pixel's data from HSV to RGB domain
// https://www.rapidtables.com/convert/color/hsv-to-rgb.html
RGB hsv_to_rgb(HSV In_HSV);

// pixel class to store a pixel
class Pixel {
    private: 
        RGB RGB_Colors;
        HSV HSV_Colors;

        // color struct conversions
        void convertToHSV(void);
        void convertToRGB(void);

        // helper function to read Pixel object
        void read(std::istream &is);

    public:
        // constructor & deconstructor
        Pixel();
        Pixel(std::istream &is);
        ~Pixel(void);

        // change color of pixel
        void changeColors(int colorChoice);

        // helper functions to write Pixel object
        void write(std::ostream &os);
};

#endif