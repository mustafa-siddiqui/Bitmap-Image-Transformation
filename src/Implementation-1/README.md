# Implementation 1: Image stored as an object

This implementation works by having two classes - for an individual pixel and the whole image. The image object contains an array of the pixel objects as per the number of pixels in the image. All of the data of the bitmap image file - metadata and pixel data - is stored in the image object. The pixel object stores only the color information of a single pixel in RGB and HSV formats.

It uses C File I/O to perform read and write operations on the bitmap file. Since `fwrite()` and `fread()` cannot work with user-defined data types, the data has to be first read into an `unsigned char` array and then transferred into the object. The class's methods are written accordingly.

### Links consulted:
- [Bitmap File Header](https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader)
- [Bitmap Info Header](https://docs.microsoft.com/en-us/previous-versions//dd183376(v=vs.85)?redirectedfrom=MSDN)
- [RGB to HSV Conversion](https://www.rapidtables.com/convert/color/rgb-to-hsv.html)
