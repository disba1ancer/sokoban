/*
 * ArrayTextureDataProvider.h
 *
 *  Created on: Dec 1, 2018
 *      Author: disba1ancer
 */

#ifndef ARRAYTEXTUREDATAPROVIDER_H_
#define ARRAYTEXTUREDATAPROVIDER_H_

#include <util/ITextureDataProvider.h>
#include <vector>
#include <memory>

namespace util {

class ArrayTextureDataProvider: public ITextureDataProvider {
public:
	ArrayTextureDataProvider(int width, int height, PixelFormat format, unsigned lodCount);
	virtual ~ArrayTextureDataProvider();

	void addTexture(ITextureDataProvider* texture);

	int getWidth() override;
	int getHeight() override;
	int getDepth() override;
	PixelFormat getFormat() override;
	unsigned getLodCount() override;
	void uploadData(void* recvBuffer, unsigned lod) override;
private:
	int width, height;
	PixelFormat format;
	unsigned lodCount;
	std::vector<ITextureDataProvider*> textures;
};

} /* namespace util */

#endif /* ARRAYTEXTUREDATAPROVIDER_H_ */
