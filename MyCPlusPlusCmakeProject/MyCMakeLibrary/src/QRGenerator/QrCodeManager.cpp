/* 
 * QR Code generator demo (C++)
 * 
 * Run this command-line program with no arguments. The program computes a bunch of demonstration
 * QR Codes and prints them to the console. Also, the SVG code for one QR Code is printed as a sample.
 * 
 * Copyright (c) Project Nayuki. (MIT License)
 * https://www.nayuki.io/page/qr-code-generator-library
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * - The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 * - The Software is provided "as is", without warranty of any kind, express or
 *   implied, including but not limited to the warranties of merchantability,
 *   fitness for a particular purpose and noninfringement. In no event shall the
 *   authors or copyright holders be liable for any claim, damages or other
 *   liability, whether in an action of contract, tort or otherwise, arising from,
 *   out of or in connection with the Software or the use or other dealings in the
 *   Software.
 */

#include <climits>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "QRGenerator/qrcodegen.hpp"
#include "QRGenerator/QrCodeManager.h"
#include "QRGenerator/lodepng.h"

using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

QrCodeManager::QrCodeManager() :
	SingletonClass<QrCodeManager>()
{
}

QrCodeManager::~QrCodeManager()
{
}

void QrCodeManager::generateQRImage(std::string content, int scale)
{
	// Encode the content into a QR Code symbol
	qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(content.c_str(), qrcodegen::QrCode::Ecc::MEDIUM);

	// Output the QR Code as a PBM (Portable Bitmap) file
	std::ofstream outFile(FILE_PATH + std::string("QrCode.bmp"), std::ios::binary);

	// BMP file header
	outFile.put('B');
	outFile.put('M');
	std::uint32_t fileSize = 54 + 3 * (qr.getSize() * scale) * (qr.getSize() * scale); // File size
	outFile.write(reinterpret_cast<const char*>(&fileSize), sizeof(fileSize));
	std::uint32_t reserved = 0; // Reserved
	outFile.write(reinterpret_cast<const char*>(&reserved), sizeof(reserved));
	std::uint32_t pixelDataOffset = 54; // Pixel data offset
	outFile.write(reinterpret_cast<const char*>(&pixelDataOffset), sizeof(pixelDataOffset));

	// DIB header
	std::uint32_t dibHeaderSize = 40; // DIB header size
	outFile.write(reinterpret_cast<const char*>(&dibHeaderSize), sizeof(dibHeaderSize));
	std::uint32_t width = qr.getSize() * scale; // Width
	outFile.write(reinterpret_cast<const char*>(&width), sizeof(width));
	std::uint32_t height = qr.getSize() * scale; // Height
	outFile.write(reinterpret_cast<const char*>(&height), sizeof(height));
	std::uint16_t colorPlanes = 1; // Color planes
	outFile.write(reinterpret_cast<const char*>(&colorPlanes), sizeof(colorPlanes));
	std::uint16_t bitsPerPixel = 24; // Bits per pixel
	outFile.write(reinterpret_cast<const char*>(&bitsPerPixel), sizeof(bitsPerPixel));
	std::uint32_t compressionMethod = 0; // Compression method
	outFile.write(reinterpret_cast<const char*>(&compressionMethod), sizeof(compressionMethod));
	std::uint32_t imageSize = 3 * (qr.getSize() * scale) * (qr.getSize() * scale); // Image size
	outFile.write(reinterpret_cast<const char*>(&imageSize), sizeof(imageSize));
	std::uint32_t horizontalResolution = 2835; // Horizontal resolution (pixels per meter, approximately 72 DPI)
	outFile.write(reinterpret_cast<const char*>(&horizontalResolution), sizeof(horizontalResolution));
	std::uint32_t verticalResolution = 2835; // Vertical resolution (pixels per meter, approximately 72 DPI)
	outFile.write(reinterpret_cast<const char*>(&verticalResolution), sizeof(verticalResolution));
	std::uint32_t numberOfColorsInPalette = 0; // Number of colors in palette
	outFile.write(reinterpret_cast<const char*>(&numberOfColorsInPalette), sizeof(numberOfColorsInPalette));
	std::uint32_t numberOfImportantColors = 0; // Number of important colors
	outFile.write(reinterpret_cast<const char*>(&numberOfImportantColors), sizeof(numberOfImportantColors));

	// Pixel data
	for (int y = 0; y < qr.getSize(); ++y)
	{
		for (int sy = 0; sy < scale; ++sy)
		{ // Scale vertically
			for (int x = 0; x < qr.getSize(); ++x)
			{
				std::uint8_t pixel = qr.getModule(x, y) ? 0 : 255; // Black or white pixel
				for (int sx = 0; sx < scale; ++sx)
				{ // Scale horizontally
					outFile.put(pixel); // Blue
					outFile.put(pixel); // Green
					outFile.put(pixel); // Red
				}
			}
			// Add padding to make each row a multiple of 4 bytes
			for (int i = 0; i < (4 - ((qr.getSize() * scale * 3) % 4)) % 4; ++i)
			{
				outFile.put(0);
			}
		}
	}

#if 0
	// Pixel data in mirror image
	for (int y = 0; y < qr.getSize(); ++y)
	{
		for (int sy = 0; sy < scale; ++sy)
		{ // Scale vertically
			for (int x = qr.getSize() - 1; x >= 0; --x)
			{ // Reverse order horizontally
				std::uint8_t pixel = qr.getModule(x, y) ? 0 : 255; // Black or white pixel
				for (int sx = 0; sx < scale; ++sx)
				{ // Scale horizontally
					outFile.put(pixel); // Blue
					outFile.put(pixel); // Green
					outFile.put(pixel); // Red
				}
			}
			// Add padding to make each row a multiple of 4 bytes
			for (int i = 0; i < (4 - ((qr.getSize() * scale * 3) % 4)) % 4; ++i)
			{
				outFile.put(0);
			}
		}
	}
#endif // if want to generate a mirror image QR code

	// Close the file
	outFile.close();
}

void QrCodeManager::generateHighResQRCode(const std::string& text, int scale, int border)
{
	// Generate the QR code
	qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(text.c_str(), qrcodegen::QrCode::Ecc::LOW);

	// Calculate the size of the QR code image
	int qrSize = qr.getSize();
	int imageSize = (qrSize + 2 * border) * scale;

	// Create a vector to store the image data
	std::vector<unsigned char> image(imageSize * imageSize * 4, 255); // Initialize with white background

	// Fill the image with the QR code data
	for (int y = 0; y < qrSize; ++y) 
	{
		for (int x = 0; x < qrSize; ++x) 
		{
			bool module = qr.getModule(x, y);
			int xPos = (x + border) * scale;
			int yPos = (y + border) * scale;
			for (int dy = 0; dy < scale; ++dy) 
			{
				for (int dx = 0; dx < scale; ++dx) 
				{
					int index = 4 * ((yPos + dy) * imageSize + (xPos + dx));
					image[index + 0] = module ? 0 : 255; // Red
					image[index + 1] = module ? 0 : 255; // Green
					image[index + 2] = module ? 0 : 255; // Blue
					image[index + 3] = 255;              // Alpha
				}
			}
		}
	}

	// Save the image as a PNG file using lodepng
	lodepng::encode(FILE_PATH + std::string("QrCode.png"), image, imageSize, imageSize);
}


