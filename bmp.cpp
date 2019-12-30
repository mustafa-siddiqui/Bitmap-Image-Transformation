#include <iostream>
#include "bmp.h"

// store FILEHEADER data into Object
void bmpImage::setFILEHEADER(BITMAPFILEHEADER* readData) {

    if (readData == NULL) {
        std::cout << "Error setting object File Header\n";
    }

    fileHeaderData.bfType = readData->bfType;
    fileHeaderData.bfSize = readData->bfSize;
    fileHeaderData.bfReserved1 = readData->bfReserved1;
    fileHeaderData.bfReserved2 = readData->bfReserved2;
    fileHeaderData.bfOffBits = readData->bfOffBits;
}

// store INFOHEADER data into Object
void bmpImage::setINFOHEADER(BITMAPINFOHEADER* readData) {

    if (readData == NULL) {
        std::cout << "Error setting object Info Header\n";
    }

    infoHeaderData.biSize = readData->biSize;
    infoHeaderData.biWidth = readData->biWidth;
    infoHeaderData.biHeight = readData->biHeight;
    infoHeaderData.biPlanes = readData->biPlanes;
    infoHeaderData.biBitCount = readData->biBitCount;
    infoHeaderData.biCompression = readData->biCompression;
    infoHeaderData.biSizeImage = readData->biSizeImage;
    infoHeaderData.biXPelsPerMeter = readData->biXPelsPerMeter;
    infoHeaderData.biYPelsPerMeter = readData->biYPelsPerMeter;
    infoHeaderData.biClrUsed = readData->biClrUsed;
    infoHeaderData.biClrImportant = readData->biClrImportant;
}

// get methods for image class
BITMAPFILEHEADER bmpImage::getFileHeader(void) { return (this->fileHeaderData); }

BITMAPINFOHEADER bmpImage::getInfoHeader(void) { return (this->infoHeaderData); }

bmpPixel* bmpImage::getImagePixelData(void) { return (this->imageData); }

// initalize required number of pixel objects in image object
bool bmpImage::initializeNumberOfPixels(int numberOfPixels) {

    bool memoryAllot = true;
    this->imageData = new bmpPixel[numberOfPixels];
    if (this->imageData == NULL) {
        // Memory Allocation failed
        memoryAllot = false;
    }
    return (memoryAllot);
}

// store read data into image object's pixel object array
void bmpImage::setImagePixels(unsigned char* readData, int numberOfBytes) {

    int c {0};
    for (int i {0}; i < numberOfBytes; i += 3) {
        (imageData + c)->setRGB_Colors(readData + i);
        c++;
    }
    if (imageData == NULL) {
        std::cout << "Failed to set Image Object Data @ Line 50 bmp.cpp\n";
    }
}

// verify file type of image
bool bmpImage::checkBitmapID() { return (bmpImage::fileHeaderData.bfType == 0x4D42); }

// verify offset to image data is 54 bytes
bool bmpImage::checkOffset() { return (bmpImage::fileHeaderData.bfOffBits == 54); }

// verify size of bitmap info header is 40 bytes
bool bmpImage::checkHeaderSize() { return (bmpImage::infoHeaderData.biSize == 40); }

// verify bit count per pixel is 24 bits per pixel
bool bmpImage::checkBitCount() { return (bmpImage::infoHeaderData.biBitCount == 24); }

// verify compression is off
bool bmpImage::checkCompression() { return (bmpImage::infoHeaderData.biCompression == 0); }

// convert read data into BYTE and store into pixel object array
void bmpPixel::setRGB_Colors(unsigned char* readData) {
    // in a bitmap where each color takes 8 bits or 1-byte of the color value, the 1st byte is for blue, 2nd for green and 3rd for red 
    RGB_Colors.blue = (BYTE)*readData;
    RGB_Colors.green = (BYTE)*(readData + 1);
    RGB_Colors.red = (BYTE)*(readData + 2);
}

// RGB to HSV conversion
HSV rgb2hsv(RGB in) {
    HSV out;
    double redTemp = in.red / 255.0;
    double greenTemp = in.green / 255.0;
    double blueTemp = in.blue / 255.0;

    double maxVal = std::max(redTemp, std::max(greenTemp, blueTemp));
    double minVal = std::min(redTemp, std::min(greenTemp, blueTemp));

    double deltaVal = maxVal - minVal;

    // hue
    if (deltaVal == 0) {
        out.hue = 0;
    }
    else if (maxVal == redTemp) {
        out.hue = 60 * (fmod(((greenTemp - blueTemp)/deltaVal),6));
    }
    else if (maxVal == greenTemp) {
        out.hue = 60 * (((blueTemp - redTemp)/deltaVal) + 2.0);
    }
    else if (maxVal == blueTemp) {
        out.hue = 60 * (((redTemp - greenTemp)/deltaVal) + 4.0);
    }
    if (out.hue < 0) {
        out.hue += 360;
    }
    // saturation
    if (maxVal == 0.00) {
        out.saturation = 0;
    }
    else {
        out.saturation = 100 * (deltaVal / maxVal);
    }
    // value
    out.value = 100 * maxVal;

    return (out);
}

// HSV to RGB conversion
RGB hsv2rgb(HSV in) {
    RGB out;
    double C = 0, X = 0, m = 0;

    double saturation = in.saturation / 100;
    double value = in.value / 100;

    if ((in.hue >= 0 && in.hue < 360) && (saturation >= 0 && saturation <= 1) && (value >= 0 && value <= 1)) {
        C = value * saturation;
        X = C * (1-fabs(fmod((in.hue / 60), 2)-1));
        m = value - C;
    }

    double redTemp = 0, blueTemp = 0, greenTemp = 0;

    if (in.hue >= 0 && in.hue < 60) {
        redTemp = C;
        greenTemp = X;
        blueTemp = 0;
    }
    else if (in.hue >= 60 && in.hue < 120) {
        redTemp = X;
        greenTemp = C;
        blueTemp = 0;
    }
    else if (in.hue >= 120 && in.hue < 180) {
        redTemp = 0;
        greenTemp = C;
        blueTemp = X;
    }
    else if (in.hue >= 180 && in.hue < 240) {
        redTemp = 0;
        greenTemp = X;
        blueTemp = C;
    }
    else if (in.hue >= 240 && in.hue < 300) {
        redTemp = X;
        greenTemp = 0;
        blueTemp = C;
    }
    else if (in.hue >= 300 && in.hue < 360) {
        redTemp = C;
        greenTemp = 0;
        blueTemp = X;
    }

    double red = (redTemp + m) * 255;
    double green = (greenTemp + m) * 255;
    double blue = (blueTemp + m) * 255;

    out.red = BYTE(red);
    out.green = BYTE(green);
    out.blue = BYTE(blue);

    return (out);
}

HSV colorChange(HSV pixelData_hsv, int colorChoice) {
    if (colorChoice == 1) {                                     // red
        if (pixelData_hsv.hue > 20 && pixelData_hsv.hue < 340) {
            pixelData_hsv.saturation = 0;
        }
        return pixelData_hsv;
    }
    else if (colorChoice == 2) {                                // yellow
        if (pixelData_hsv.hue < 50 || pixelData_hsv.hue > 70) {
            pixelData_hsv.saturation = 0;
        }
        return pixelData_hsv;
    }
    else  if (colorChoice == 3) {                               // orange
        if (pixelData_hsv.hue < 20 || pixelData_hsv.hue > 50) {
            pixelData_hsv.saturation = 0;
        }
        return pixelData_hsv;
    }
    else if (colorChoice == 4) {                                // green
        if (pixelData_hsv.hue < 60 || pixelData_hsv.hue > 160) {
            pixelData_hsv.saturation = 0;
        }
        return pixelData_hsv;
    }
    else if (colorChoice == 5) {                                // blue
        if (pixelData_hsv.hue < 160 || pixelData_hsv.hue > 230) {
            pixelData_hsv.saturation = 0;
        }
        return pixelData_hsv;
    }
    else {  // this case is never going to happen since colorChoice is validated in main()
        std::cout << "Invalid Color Choice\n";
        return {0,0,0};
    }
}

// get RGB values from pixel
RGB bmpPixel::getPixelRGBData(void) { return (this->RGB_Colors); }
HSV bmpPixel::getPixelHSVData(void) { return (this->HSV_Colors); }

// convert pixel from rgb to hsv
void bmpPixel::convertToHSV(void) { this->HSV_Colors = rgb2hsv(this->RGB_Colors); }

// convert pixel from hsv to rgb
void bmpPixel::convertToRGB(void) { this->RGB_Colors = hsv2rgb(this->HSV_Colors); }

// changes color values in hsv and updates rgb values accordingly
void bmpPixel::changeColors(int colorChoice) { 

    this->convertToHSV();
    this->HSV_Colors = colorChange(this->HSV_Colors, colorChoice);
    this->convertToRGB();
}

// changes image colors in hsv and updates rgb values accordingly
void bmpImage::changeImageColor(int numberOfPixels, int colorChoice) {

    for (int i {0}; i < numberOfPixels; i++) {
        (this->imageData + i)->changeColors(colorChoice);
    }
}