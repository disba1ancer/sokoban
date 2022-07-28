/*
 * BitmapTextureDataProvider.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: disba1ancer
 */

#include <string>
#include <cinttypes>
#include <exception>
#include <cmath>
#include "util.h"
#include "BitmapTextureDataProvider.h"

namespace {
	struct BitmapHeader {
		uint_least32_t fileSize;
		uint_least32_t pad;
		uint_least32_t bitmapDataStart;
	};

	struct BitmapInfo {
		uint_least32_t structSize;
		int_least32_t width;
		int_least32_t height;
		int_least16_t planesCount;
		int_least16_t bpp;
		uint_least32_t compression;
		uint_least32_t bitmapDataSize;
		int_least32_t pxPerMeterX;
		int_least32_t pxPerMeterY;
		uint_least32_t palColorCount;
		uint_least32_t palColorReqCount;
	};

	enum BitmapCompression {
		BMCOMPR_RGB = 0,
		BMCOMPR_BITFIELDS = 3,
	};

	struct BitmapMeta {
		BitmapHeader header;
		BitmapInfo info;
	};

	struct ColorMasks {
		uint_least32_t redMask;
		uint_least32_t greenMask;
		uint_least32_t blueMask;
		uint_least32_t alphaMask;
	};

	void maskToShift(uint_least32_t mask, unsigned char& shift, unsigned char& length) {
		if (mask != 0) {
			shift = 0;
			while ((mask & 1) == 0) {
				++shift;
				mask >>= 1;
			}
			length = 0;
			while ((mask & 1) == 1) {
				++length;
				mask >>= 1;
			}
			if (length > 8) {
				throw std::runtime_error("Mask length is very long");
			}
		} else {
			throw std::runtime_error("Color mask can not be null");
		}
	}

	uint_least32_t applyShiftLength(uint_least32_t color, unsigned char shift, unsigned char length, unsigned char addShift) {
		color >>= shift + length - 8;
		color &= 0xFF;
		color |= color >> length;
		return color << addShift;
	}
}

namespace util {

BitmapTextureDataProvider::BitmapTextureDataProvider(const char* file) :
width(0),
height(0),
format(PF_RGBA8),
redShift(16), greenShift(8), blueShift(0), alphaShift(24), redLength(8), greenLength(8), blueLength(8), alphaLength(8)
{
	if (file && file[0] != '\0') {
		bitmapFile = std::ifstream(file, std::ios::in | std::ios::binary);
		if (bitmapFile.fail()) {
			throw std::runtime_error("Can not open file");
		}
		std::uint_least16_t sign = 0;
		bitmapFile.read(reinterpret_cast<char*>(&sign), sizeof(sign));
		if ((sign & 0xFFFF) != 0x4D42) {
			throw std::runtime_error("Bitmap signature error");
		}
		BitmapMeta bitmapMeta = {};
		bitmapFile.read(reinterpret_cast<char*>(&bitmapMeta), sizeof(bitmapMeta));
		if (bitmapMeta.info.height < 0) {
			throw std::runtime_error("Negative height not supported");
		}
		if (bitmapMeta.info.compression != BMCOMPR_RGB && bitmapMeta.info.compression != BMCOMPR_BITFIELDS) {
			throw std::runtime_error("Compression in not supported");
		}
		if (bitmapMeta.info.bpp == 24) {
			format = PF_BGR8;
		} else if (bitmapMeta.info.bpp == 32) {
			format = PF_RGBA8;
			if (bitmapMeta.info.compression == BMCOMPR_BITFIELDS) {
				ColorMasks clMasks = {};
				bitmapFile.read(reinterpret_cast<char*>(&clMasks), sizeof(clMasks));
				maskToShift(clMasks.redMask, redShift, redLength);
				maskToShift(clMasks.greenMask, greenShift, greenLength);
				maskToShift(clMasks.blueMask, blueShift, blueLength);
				maskToShift(clMasks.alphaMask, alphaShift, alphaLength);
			}
		} else {
			throw std::runtime_error("Only 24 and 32 BPP supported");
		}
		width = bitmapMeta.info.width;
		height = bitmapMeta.info.height;
		pixelsPos = bitmapMeta.header.bitmapDataStart;
	}
}

BitmapTextureDataProvider::~BitmapTextureDataProvider() {
	// TODO Auto-generated destructor stub
}

int BitmapTextureDataProvider::getWidth() {
	return width;
}

int BitmapTextureDataProvider::getHeight() {
	return height;
}

int BitmapTextureDataProvider::getDepth() {
	return 1;
}

ITextureDataProvider::PixelFormat BitmapTextureDataProvider::getFormat() {
	return format;
}

void BitmapTextureDataProvider::uploadData(void* recvBuffer, unsigned) {
	bitmapFile.seekg(pixelsPos);
	switch (format) {
	case PF_BGR8: {
		size_t dataSize = util::alignSize(3 * std::size_t(width), 4);
		dataSize *= std::size_t(height);
		bitmapFile.read(static_cast<char*>(recvBuffer), dataSize);
	} break;
	case PF_RGBA8: {
		auto buffer = static_cast<unsigned char*>(recvBuffer);
		uint_least32_t pixel;
		for (auto i = 0U; i < std::size_t(width) * std::size_t(height); ++i, buffer += 4) {
			bitmapFile.read(reinterpret_cast<char*>(&pixel), sizeof(pixel));
			buffer[3] = (unsigned char)applyShiftLength(pixel, alphaShift, alphaLength, 0);
			buffer[2] = (unsigned char)applyShiftLength(pixel, blueShift, blueLength, 0);
			buffer[1] = (unsigned char)applyShiftLength(pixel, greenShift, greenLength, 0);
			buffer[0] = (unsigned char)applyShiftLength(pixel, redShift, redLength, 0);
		}
	} break;
	default:
		throw std::runtime_error("Internal error: invalid format");
	}
}

unsigned BitmapTextureDataProvider::getLodCount() {
	return 1;
}

} /* namespace util */
