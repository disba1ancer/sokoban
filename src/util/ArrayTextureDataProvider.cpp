/*
 * ArrayTextureDataProvider.cpp
 *
 *  Created on: Dec 1, 2018
 *      Author: disba1ancer
 */

#include <util/ArrayTextureDataProvider.h>
#include <stdexcept>

namespace util {

ArrayTextureDataProvider::ArrayTextureDataProvider(int width, int height, PixelFormat format, unsigned lodCount)
:
		width(width),
		height(height),
		format(format),
		lodCount(lodCount)
{}

ArrayTextureDataProvider::~ArrayTextureDataProvider() {
	// TODO Auto-generated destructor stub
}

int ArrayTextureDataProvider::getWidth() {
	return width;
}

int ArrayTextureDataProvider::getHeight() {
	return height;
}

int ArrayTextureDataProvider::getDepth() {
	return textures.size();
}

ArrayTextureDataProvider::PixelFormat ArrayTextureDataProvider::getFormat() {
	return format;
}

unsigned ArrayTextureDataProvider::getLodCount() {
	return lodCount;
}

void ArrayTextureDataProvider::addTexture(ITextureDataProvider* texture) {
	if (texture->getWidth() != width ||
			texture->getHeight() != width ||
			texture->getDepth() != 1 ||
			texture->getFormat() != format ||
			texture->getLodCount() != lodCount)
	{
		throw std::runtime_error("Incompatible texture");
	}
	textures.push_back(texture);
}

void ArrayTextureDataProvider::uploadData(void* recvBuffer, unsigned lod) {
	auto buffer = static_cast<unsigned char *>(recvBuffer);
	int lodWidth, lodHeight;
	lodWidth = width >> lod;
	lodHeight = height >> lod;
	auto planeSize = ITextureDataProvider::pixelFormatParameters[format].pixelSize * lodWidth;
	planeSize += ((planeSize % 4) != 0 ? (4 - (planeSize % 4)) : 0);
	planeSize *= lodHeight;
	for (auto texture : textures) {
		texture->uploadData(buffer, lod);
		buffer += planeSize;
	}
}

} /* namespace util */
