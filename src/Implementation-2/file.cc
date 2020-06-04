/** @file   file.cc
 *  @brief  This file contains the definition of the functions
 *          defined in file.h
 *  @author Mustafa Siddiqui
 *  @date   06/03/2020
 */

#include "bmp.h"

/* Check if the file name entered is in "x.bmp" format */
bool fileExtensionCheck(char* fileName) {

    // return pointer of the index position where '.' is located
    char* point = strrchr(fileName, '.');

    // '.' not found
    if (point == NULL) {
        std::cerr << "File extension needed (.bmp)\n";
        return false;
    }
    // check the three letters after the dot to validate file extension as .bmp
    else if (*(point + 1) != 'b') {
        std::cerr << "File extension has to be .bmp\n";
        return false;
    }
    else if ((*(point + 2) != 'm')) {
        std::cerr << "File extension has to be .bmp\n";
        return false;
    }
    else if ((*(point + 3) != 'p')) {
        std::cerr << "File extension has to be .bmp\n";
        return false;
    }

    return true;
}

/* Prevent same name for input and output file */
void fileNameSame(std::string &argv1, std::string &argv2) {
    if (argv1 == argv2) {
        std::cout << "Input file and Output file names are the same. Overwrite is not possible.\n";
        for (;;) {
            std::cout << "Enter another name for output file: ";
            std::string fileName;
            std::cin >> fileName;
            if (fileExtensionCheck(&fileName[0]) == false) {
                continue;
            }
            fileNameSame(argv1, fileName);                      // recursive call
            argv2 = fileName;
            break;
        }
    }
}

/* Check if correct file type or not */
bool fileTypeCheck(BITMAPFILEHEADER* pFileHeader, BITMAPINFOHEADER* pInfoHeader) {

    // image type
    if (pFileHeader->bfType != 0x4D42) {
        std::cerr << "Image is not of BMP type.\n";
        return false;
    } 

    // offset bits
    if (pFileHeader->bfOffBits != 54) {
        std::cerr << "Image does not have an offset of 54 Bytes.\n";
        return false;
    }

    // size of info header
    if (pInfoHeader->biSize != 40) {
        std::cerr << "Size of image info header is not 40 Bytes.\n";
        return false;
    }

    // bit count per pixel
    if (pInfoHeader->biBitCount != 24) {
        std::cerr << "Bit count per pixel is not 24.\n";
        return false;
    }

    // compression
    if (pInfoHeader->biCompression != 0) {
        std::cerr << "Image is compressed.\n";
        return false;
    }

    return true;
}
