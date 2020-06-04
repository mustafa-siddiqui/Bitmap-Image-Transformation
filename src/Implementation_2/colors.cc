/** @file   colors.cc
 *  @brief  Contains definitions of functions related to
 *          RGB and HSV conversions defined in bmp.h
 *  @author Mustafa Siddiqui
 *  @date   06/01/2020
 */

#include "bmp.h"

// RGB to HSV conversion
// https://www.rapidtables.com/convert/color/rgb-to-hsv.html
HSV rgb_to_hsv(RGB In_RGB) {
    HSV Out_HSV;

    double redTemp = In_RGB.red / 255.0;
    double greenTemp = In_RGB.green / 255.0;
    double blueTemp = In_RGB.blue / 255.0;

    double maxVal = std::max(redTemp, std::max(greenTemp, blueTemp));
    double minVal = std::min(redTemp, std::min(greenTemp, blueTemp));

    double deltaVal = maxVal - minVal;

    // hue
    if (deltaVal == 0) {
        Out_HSV.hue = 0;
    }
    else if (maxVal == redTemp) {
        Out_HSV.hue = 60 * (fmod(((greenTemp - blueTemp)/deltaVal),6));
    }
    else if (maxVal == greenTemp) {
        Out_HSV.hue = 60 * (((blueTemp - redTemp)/deltaVal) + 2.0);
    }
    else if (maxVal == blueTemp) {
        Out_HSV.hue = 60 * (((redTemp - greenTemp)/deltaVal) + 4.0);
    }
    if (Out_HSV.hue < 0) {
        Out_HSV.hue += 360;
    }

    // saturation
    if (maxVal == 0.00) {
        Out_HSV.saturation = 0;
    }
    else {
        Out_HSV.saturation = 100 * (deltaVal / maxVal);
    }

    // value
    Out_HSV.value = 100 * maxVal;

    return Out_HSV;
}

// HSV to RGB conversion
// https://www.rapidtables.com/convert/color/hsv-to-rgb.html
RGB hsv_to_rgb(HSV In_HSV) {
    RGB Out_RGB;
    
    double C = 0, X = 0, m = 0;
    double redTemp = 0, blueTemp = 0, greenTemp = 0;

    double saturation = In_HSV.saturation / 100;
    double value = In_HSV.value / 100;

    if ((In_HSV.hue >= 0 && In_HSV.hue < 360) && (saturation >= 0 && saturation <= 1) && (value >= 0 && value <= 1)) {
        C = value * saturation;
        X = C * (1-fabs(fmod((In_HSV.hue / 60), 2)-1));
        m = value - C;
    }

    if (In_HSV.hue >= 0 && In_HSV.hue < 60) {
        redTemp = C;
        greenTemp = X;
        blueTemp = 0;
    }
    else if (In_HSV.hue >= 60 && In_HSV.hue < 120) {
        redTemp = X;
        greenTemp = C;
        blueTemp = 0;
    }
    else if (In_HSV.hue >= 120 && In_HSV.hue < 180) {
        redTemp = 0;
        greenTemp = C;
        blueTemp = X;
    }
    else if (In_HSV.hue >= 180 && In_HSV.hue < 240) {
        redTemp = 0;
        greenTemp = X;
        blueTemp = C;
    }
    else if (In_HSV.hue >= 240 && In_HSV.hue < 300) {
        redTemp = X;
        greenTemp = 0;
        blueTemp = C;
    }
    else if (In_HSV.hue >= 300 && In_HSV.hue < 360) {
        redTemp = C;
        greenTemp = 0;
        blueTemp = X;
    }

    double red = (redTemp + m) * 255;
    double green = (greenTemp + m) * 255;
    double blue = (blueTemp + m) * 255;

    Out_RGB.red = BYTE(red);
    Out_RGB.green = BYTE(green);
    Out_RGB.blue = BYTE(blue);

    return Out_RGB;
}