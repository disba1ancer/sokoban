/*
 * BitmapTextureDataProvider.h
 *
 *  Created on: Nov 12, 2018
 *      Author: disba1ancer
 */

#ifndef BITMAPTEXTUREDATAPROVIDER_H_
#define BITMAPTEXTUREDATAPROVIDER_H_

#include <util/ITextureDataProvider.h>
#include <fstream>

namespace util {

class BitmapTextureDataProvider: public ITextureDataProvider {
public:
	BitmapTextureDataProvider(const char* file = nullptr);
	~BitmapTextureDataProvider() override;
	int getWidth() override;
	int getHeight() override;
	int getDepth() override;
	PixelFormat getFormat() override;
	unsigned getLodCount() override;
	void uploadData(void* recvBuffer, unsigned lod) override;
private:
	std::ifstream bitmapFile;
	int width, height;
	PixelFormat format;
	std::ifstream::pos_type pixelsPos;
	unsigned char redShift, greenShift, blueShift, alphaShift, redLength, greenLength, blueLength, alphaLength;
};

} /* namespace util */

#endif /* BITMAPTEXTUREDATAPROVIDER_H_ */
