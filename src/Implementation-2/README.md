# Implementation 2: Pixels are read, converted, and written one by one

This implementation works with using just one class - for a single pixel - and works by reading one pixel, converting the colors, writing it to the new file, and then moving on to the next pixel. The meta data is read, verified, and written to the output file separately.

It uses C++ File Streams to incorporate reading and writing of data with the pixel object. This way, data is read directly into the object (`is.read()` is called in the constructor, where `is` is the input stream), and written to the output file directly.

It also ensures that file names entered by the user are verified (in the specific format "x.bmp") and the input and output file names are not the same, since overwriting is not supported.

#### Links consulted:
- [Bitmap File Header](https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader)
- [Bitmap Info Header](https://docs.microsoft.com/en-us/previous-versions//dd183376(v=vs.85)?redirectedfrom=MSDN)
- [RGB to HSV Conversion](https://www.rapidtables.com/convert/color/rgb-to-hsv.html)
- [C++ File Streams](http://www.cplusplus.com/doc/tutorial/files/)

#### Sample Result:

Original picture:
![tiger.bmp]
(https://github.com/mustafa-siddiqui/bitmap-image-transformation/blob/master/src/Implementation-2/tiger.jpg)

Transformed Picture: (Orange chosen to be kept)
![out.bmp]
(https://github.com/mustafa-siddiqui/bitmap-image-transformation/blob/master/src/Implementation-2/out.jpg)
