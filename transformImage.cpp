/** @file transformImage.cpp
 *  @brief Sample Code for ECE 114: Image Transformation Project - Fall 2019.
 *         The whole image is stored as an object, based on the bmpImage class, and methods are called on it to convert colors.
 *         The image object has an array of objects representing pixels in the image, based on the bmpPixel class.
 *         -> 2 Other Files: bmp.cpp & bmp.h <-
 *  @author Mustafa Siddiqui
 *  @date 11/16/2019
 */

#include <iostream>
#include <fstream>
#include <string>
#include "bmp.h"

int main(int argc, char* argv[]) {

    // check correct arguments have been passed
    if (argc != 3) {
        std::cout << "Usage: <executable filename> <input filename> <output filename>" << std::endl;
        return 0;
    }

    // declare object
    bmpImage image;

    // declare structure pointers to store data
    BITMAPFILEHEADER* imgFileHeader = new BITMAPFILEHEADER;
    if (imgFileHeader == NULL) {
        std::cout << "imgFileHeader initialization failed @ Line 18\n";
        return 0;
    }
    BITMAPINFOHEADER* imgInfoHeader = new BITMAPINFOHEADER;
    if (imgInfoHeader == NULL) {
        std::cout << "imgInfoHeader initialization failed @ Line 23\n";
        return 0;
    }

    // declare file pointer and verify memory is allotted
    FILE* fptr1;
    fptr1 = fopen(argv[1], "rb");
    if (fptr1 == NULL) {
        std::cout << "Error opening file @ Line 31\n";
        return 0;
    }

    // read bitmap file header and assign data to image object
    fread(imgFileHeader, sizeof(BITMAPFILEHEADER), 1, fptr1);
    if (imgFileHeader == NULL) {
        std::cout << "Failed to read imgFileHeader @ Line 38\n";
        return 0;
    }
    image.setFILEHEADER(imgFileHeader);

    // check bitmap ID to verify file type
    if (!image.checkBitmapID()) {
        fclose(fptr1);
        std::cout << "Bitmap ID: " << std::hex << image.getFileHeader().bfType << std::dec << '\n';
        std::cout << "ERROR: File is not a Bitmap Image\n";
        return 0;
    }
    else {
        std::cout << "Bitmap ID: " << std::hex << image.getFileHeader().bfType << std::dec << '\n';
    }

    // check offset
    if (!image.checkOffset()) {
        fclose(fptr1);
        std::cout << "ERROR: Offset not of 54 Bytes\n";
        return 0;
    }

    // read bitmap info header and assign data to image object
    fread(imgInfoHeader, sizeof(BITMAPINFOHEADER), 1, fptr1);
    if (imgInfoHeader == NULL) {
        std::cout << "Failed to read imgInfoHeader @ Line 64\n";
        return 0;
    }
    image.setINFOHEADER(imgInfoHeader);

    // check info header size of image
    if (!image.checkHeaderSize()) {
        fclose(fptr1);
        std::cout << "ERROR: Bitmap info header is not of 40 Bytes\n";
        return 0;
    }

    // check bit count per pixel of image
    if (!image.checkBitCount()) {
        fclose(fptr1);
        std::cout << "ERROR: Bit Count per Pixel is not 24\n";
        return 0;
    }

    // check compression of image
    if (!image.checkCompression()) {
        fclose(fptr1);
        std::cout << "ERROR: This program only works for uncompressed files\n";
        return 0;
    }

    // move file pointer to where the image data starts
    fseek(fptr1, imgFileHeader->bfOffBits, SEEK_SET);
    if (fptr1 == NULL) {
        std::cout << "Failed to seek file pointer @ LINE 93\n";
        return 0;
    }

    // calculate number of pixels and padding in image
    int paddingAmount = (4 - (image.getInfoHeader().biWidth * sizeof(RGB)) % 4) % 4; /* taken from Varun's solution code */
    // OR int paddingAmount = image.getInfoHeader().biWidth % 4; /* gives the same value */
    int numberOfColoredPixels = (int)(imgInfoHeader->biHeight * (imgInfoHeader->biWidth + paddingAmount)); // biWidth excludes padding

    // allot memory for number of pixels in the read image in image object & exit if failed
    if (image.initializeNumberOfPixels(numberOfColoredPixels) == false) {
        std::cout << "ERROR: Memory Allocation Failed\n";
        return 0;
    }
    else {
        std::cout << numberOfColoredPixels << " Pixel Objects instantiated\n";
    }

    // var to store image data
    unsigned char* imageData = new unsigned char[(int)image.getInfoHeader().biSizeImage];
    if (imageData == NULL) {
        fclose(fptr1);
        std::cout << "ERROR: Memory Allocation Failed\n";
        return 0;
    }

    // read pixel data
    fread(imageData, image.getInfoHeader().biSizeImage, 1, fptr1);
    if (imageData == NULL) {
        fclose(fptr1);
        std::cout << "Error Reading File\n";
        return 0;
    }

    std::cout << "Number of colored pixels: " << numberOfColoredPixels << std::endl;
    std::cout << "BiSizeImage: " << (int)image.getInfoHeader().biSizeImage << std::endl;
    std::cout << "Padding Amount: " << paddingAmount << std::endl;
    // store RGB pixel data into image object
    image.setImagePixels(imageData, (int)image.getInfoHeader().biSizeImage);
    //std::cout << "Check: " << (image.getImagePixelData()->getPixelRGBData().red == *imageData) << '\n';

    std::cout << "Image object instantiated!\n";

    /* Now the whole image has been store as an object */

    // don't need temporary variables anymore
    fclose(fptr1);
    delete imgFileHeader;
    delete imgInfoHeader;
    delete[] imageData;

    /* CONVERSION OF COLORS */

    // color choice selection
    int colorChoice;
    std::cout << "1. Red\n2. Yellow\n3. Orange\n4. Green\n5. Blue\nChoose the color you want to keep in the image: ";
    std::cin >> colorChoice;
    while (colorChoice < 1 || colorChoice > 5 || std::cin.fail()) {
        std::cin.clear(); std::cin.ignore(__INT_MAX__, '\n');
        std::cout << "Invalid choice. Enter again: ";
        std::cin >> colorChoice;
    }

    // convert image colors
    image.changeImageColor(numberOfColoredPixels, colorChoice);
    
    /* WRITING THE OUTPUT FILE */
    /* Have to take care of padding when writing the output file */
    
    FILE* fptr2;
    fptr2 = fopen(argv[2], "ab");
    if (fptr2 == NULL) {
        fclose(fptr2);
        std::cout << "Error creating new file\n";
        return 0;
    }
    // output file header
    BITMAPFILEHEADER* ofileheader = new BITMAPFILEHEADER;
    *ofileheader = image.getFileHeader();
    fwrite(ofileheader, sizeof(BITMAPFILEHEADER), 1, fptr2);

    BITMAPINFOHEADER* oinfoheader = new BITMAPINFOHEADER;
    *oinfoheader = image.getInfoHeader();
    fwrite(oinfoheader, sizeof(BITMAPINFOHEADER), 1, fptr2);
    
    // output pixel data
    unsigned char* outImageData = new unsigned char[image.getInfoHeader().biSizeImage];

    int pixelIndex {0};
    for (int i {0}; i < (int)image.getInfoHeader().biSizeImage; i += 3) {
            *(outImageData + i) = (image.getImagePixelData() + pixelIndex)->getPixelRGBData().blue;
            *(outImageData + i+1) = (image.getImagePixelData() + pixelIndex)->getPixelRGBData().green;
            *(outImageData + i+2) = (image.getImagePixelData() + pixelIndex)->getPixelRGBData().red;
            pixelIndex++;
    }
   
    /* FILE OUTPUT WORKS */
    int index {0};
    for (int j {0}; j < image.getInfoHeader().biHeight; j++) {
        for (int k {0}; k < image.getInfoHeader().biWidth; k++) {
            fwrite((outImageData + index), sizeof(BYTE), 3, fptr2);
            index += 3;
        }
        if (paddingAmount > 0) {
            BYTE* paddingData = new BYTE;   // gets deleted automatically once loop is exited
            *paddingData = 0x00;
            for (int c {0}; c < paddingAmount; c++) {
                fwrite(paddingData, sizeof(BYTE), 1, fptr2);
            }
        }
        index += paddingAmount;
    }

    delete ofileheader;
    delete oinfoheader;
    delete[] outImageData;
    std::cout << std::endl << (std::string)argv[2] << " successfully created!\n";
    fclose(fptr2);

    return 0;
}