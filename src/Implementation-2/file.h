/** @file   file.h
 *  @brief  Header file containing definitions for functions that check if the input
 *          and output file names are same and if the filename entered by the user is
 *          in the appropriate format, and to verify that the image specifications are
 *          in line with what's required (pure bitmap image).
 *  @author Mustafa Siddiqui
 *  @date   06/03/2020
 */

#ifndef FILE_H
#define FILE_H

/* bmp.h has the necessary libraries already included in it */
#include "bmp.h"

/** @fn     fileNameSame(string&, string&)
 *  @brief  This recursive function checks if the input and output filenames are the same 
 *          and prevents them from being the same by prompting the user for another name
 *          until a different name is provided by the user.
 *          ** Does not verify if filename entered by user is valid or not **
 */
void fileNameSame(std::string &argv1, std::string &argv2);

/** @fn     fileExtensionCheck(char*)
 *  @brief  This functions checks if the file name entered by the user is of "x.bmp" format
 *          or not - meaning it should have a ".bmp" at the end.
 *  @return A boolean value that indicates if the file name entered is of the correct 
 *          format or not.
 */
int fileExtensionCheck(char* filename);

/** @fn     fileTypeCheck(BITMAPFILEHEADER*, BITMAPINFOHEADER*)
 *  @brief  This function checks the following info of the input image file:
 *              - file type:                    .bmp
 *              - offset to image data:         54 Bytes
 *              - size of bitmap info header:   40 Bytes
 *              - bit count per pixel:          24 bits per pixel
 *              - compression:                  0
 *  @return A boolean value that indicates if the input is of the correct type (.bmp) and
 *          is according to the specifications mentioned above.
 */
bool fileTypeCheck(BITMAPFILEHEADER* pFileHeader, BITMAPINFOHEADER* pInfoHeader);

#endif
