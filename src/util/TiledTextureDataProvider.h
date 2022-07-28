#ifndef UTIL_TILEDTEXTUREDATAPROVIDER_H
#define UTIL_TILEDTEXTUREDATAPROVIDER_H

#include "ITextureDataProvider.h"

namespace util {

class TiledTextureDataProvider : public ITextureDataProvider
{
public:
    TiledTextureDataProvider(ITextureDataProvider* provider, int tileWidth, int tileHeight);

    // ITextureDataProvider interface
public:
    virtual int getWidth() override;
    virtual int getHeight() override;
    virtual int getDepth() override;
    virtual PixelFormat getFormat() override;
    virtual unsigned getLodCount() override;
    virtual void uploadData(void* recvBuffer, unsigned lod) override;
private:
    ITextureDataProvider* provider;
    int width, height, tilesPerLine, count;
    unsigned lodCount;
};

} // namespace util

#endif // UTIL_TILEDTEXTUREDATAPROVIDER_H
