/** @file   main.cc
 *  @brief  This program reads a bitmap image file and creates another bitmap file,
 *          with one color from the original image kept and the rest turned to
 *          greyscale.
 *  @author Mustafa Siddiqui
 *  @date   06/04/2020
 */

/* Include necessary libraries */
#include "file.h"
#include "bmp.h"
//--//
#include <iostream>
#include <string>
#include <limits>
#include <fstream>

/** @fn     main(int argc, char* argv[])
 *  @brief  Main function of the program which reads the bitmap image file and 
 *          changes its colors in a new file using the Pixel class defined in
 *          bmp.h
 *  @return An integer when successfully run.
 */
int main(int argc, char* argv[]) {
    
    // validate arguments
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << "<input file> <output file>\n";
        exit(EXIT_FAILURE);
    }

    // convert and store as std::string
    std::string inputFileName = (std::string)argv[1];
    std::string outputFileName = (std::string)argv[2];

    // verify file names
    if (fileExtensionCheck(argv[1]) == false) {
        std::cerr << "Input file name invalid.\n";
        exit(EXIT_FAILURE);
    }
    else if (fileExtensionCheck(argv[2]) == false) {
        std::cerr << "Output file name invalid.\n";
        exit(EXIT_FAILURE);
    }
    fileNameSame(inputFileName, outputFileName);

    // declare file stream objects
    std::ifstream inputFile;
    std::ofstream outputFile;

    // open file streams
    inputFile.open(inputFileName, std::ios_base::binary);
    outputFile.open(outputFileName, std::ios_base::binary);

    if ((inputFile.is_open() && outputFile.is_open()) == false) {
        std::cerr << "Error in opening files.\n";
        exit(EXIT_FAILURE);
    }

    // allocate memory for pointers
    BITMAPFILEHEADER* pFileHeader = new BITMAPFILEHEADER;
    BITMAPINFOHEADER* pInfoHeader = new BITMAPINFOHEADER;

    // read file headers
    inputFile.read((char*)pFileHeader, sizeof(BITMAPFILEHEADER));
    inputFile.read((char*)pInfoHeader, sizeof(BITMAPINFOHEADER));

    // check if file type correct or not
    if (fileTypeCheck(pFileHeader, pInfoHeader) == false) {
        std::cerr << "Incorrect file type.\n";
        exit(EXIT_FAILURE);
    }

    // ask the user for color to be unchanged & validate
    std::cout << "Enter color to keep (enter number next to color):\n"
              << "Red (1)\n"
              << "Yellow (2)\n"
              << "Orange (3)\n"
              << "Green (4)\n"
              << "Blue (5)\n";

    int colorChoice = 0;
    std::cin >> colorChoice;
    while (colorChoice < 1 || colorChoice > 5 || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Enter again: ";
        std::cin >> colorChoice;
    }

    // write headers to output file
    outputFile.write((char*)pFileHeader, sizeof(BITMAPFILEHEADER));
    outputFile.write((char*)pInfoHeader, sizeof(BITMAPINFOHEADER));

    // calculate amount of padding
    int padding = (4 - (pInfoHeader->biWidth * sizeof(RGB)) % 4) % 4;

    // read image, convert, and write to output file
    for (int i = 0; i < pInfoHeader->biHeight; i++) {
        for (int j = 0; j < pInfoHeader->biWidth; j++) {
            Pixel* bmpPixel = new Pixel(inputFile);
            bmpPixel->changeColors(colorChoice);
            bmpPixel->write(outputFile);
            delete bmpPixel;
        }

        // write padding data in output file
        if (padding > 0) {
            BYTE* pPaddingData = new BYTE;
            *pPaddingData = 0x0;
            for (int k = 0; k < padding; k++) {
                outputFile.write((char*)pPaddingData, sizeof(*pPaddingData));
            }
        }

        // seek ahead of padding in input stream
        inputFile.seekg(padding, std::ios_base::cur);
    }

    // close file streams
    inputFile.close();
    outputFile.close();

    // free allocated memory
    free(pFileHeader);
    free(pInfoHeader);

    std::cout << "Image successfully created!\n";
    
    return 0;
}
