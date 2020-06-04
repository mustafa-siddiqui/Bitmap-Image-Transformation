// BMP-related data types based on Microsoft's own wingdi.h // Used from HarvardX CS50 with modifications by Varun Khatri
// Modified by Mustafa Siddiqui to fit Object-Oriented Design; 11/9/19

#ifndef BMP_H
#define BMP_H

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>

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
HSV rgb2hsv(RGB in);

// to covert one pixel's data from HSV to RGB domain
// https://www.rapidtables.com/convert/color/hsv-to-rgb.html
RGB hsv2rgb(HSV in);

class bmpPixel {
    private: 
        RGB RGB_Colors;
        HSV HSV_Colors;     

    public:
        void setRGB_Colors(unsigned char*);

        void convertToHSV(void);
        void convertToRGB(void);

        void changeColors(int);

        RGB getPixelRGBData(void);
        HSV getPixelHSVData(void);
};

class bmpImage {
    private:
        BITMAPFILEHEADER fileHeaderData;
        BITMAPINFOHEADER infoHeaderData;
        bmpPixel* imageData;
              
    public:
        // access image data
        BITMAPFILEHEADER getFileHeader(void);
        BITMAPINFOHEADER getInfoHeader(void);
        bmpPixel* getImagePixelData(void);

        // data from file header
        bool checkBitmapID(void);
        bool checkOffset(void);

        // data from info header
        bool checkHeaderSize(void);
        bool checkBitCount(void);
        bool checkCompression(void);
    
        // setting up image as object
        void setFILEHEADER(BITMAPFILEHEADER*);
        void setINFOHEADER(BITMAPINFOHEADER*);
        bool initializeNumberOfPixels(int);
        void setImagePixels(unsigned char*, int);

        // color conversion
        void changeImageColor(int, int);
};

#endif