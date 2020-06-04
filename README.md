# Bitmap-Image-Transformation
This repository contains 2 implementations of the code.
1. The whole image is stored as an object
2. Colors are inverted pixel by pixel using a pixel object
    - C++ file streams are used in this implementation as well

The code is to change the color of a pure bitmap image file. It keeps one color specified by the user and converts the rest of the image to greyscale.

It does so by using HSV (Hue, Saturation, Value) color format which makes it easier to change colors than by using RGB (Red, Green, Blue) format.

Image is read in RGB, converted into HSV, colors changed, and then converted back to RGB and then written to the output file.
