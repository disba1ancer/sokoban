/*
 * ITextureDataProvider.h
 *
 *  Created on: Nov 12, 2018
 *      Author: disba1ancer
 */

#ifndef ITEXTUREDATAPROVIDER_H_
#define ITEXTUREDATAPROVIDER_H_

namespace util {

struct ITextureDataProvider {
	enum PixelFormat {
		PF_RGBA8,
		PF_RGB8,
		PF_BGRA8,
		PF_BGR8
	};

	struct PixelFormatParameters {
		unsigned char pixelSize;
	};
	static const PixelFormatParameters pixelFormatParameters[];

	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual int getDepth() = 0;
	virtual PixelFormat getFormat() = 0;
	virtual unsigned getLodCount() = 0;
	virtual void uploadData(void* recvBuffer, unsigned lod) = 0;
	virtual ~ITextureDataProvider() = 0;
};

inline ITextureDataProvider::~ITextureDataProvider() {}

} /* namespace sokoban */

#endif /* ITEXTUREDATAPROVIDER_H_ */
