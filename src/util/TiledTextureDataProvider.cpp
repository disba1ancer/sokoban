#include <algorithm>
#include <limits>
#include <vector>
#include <cstring>
#include "util.h"
#include "TiledTextureDataProvider.h"

namespace {
unsigned ctz(unsigned val)
{
    if (val == 0) {
        return std::numeric_limits<int>::digits;
    }
    int result = 0;
    while ((val & 1) == 0) {
        val >>= 1;
        ++result;
    }
    return result;
}
}

namespace util {

TiledTextureDataProvider::TiledTextureDataProvider(
    ITextureDataProvider* provider, int tileWidth, int tileHeight
) :
    provider(provider), width(tileWidth), height(tileHeight), count(0),
    lodCount(std::min(std::min(ctz(unsigned(width)), ctz(unsigned(height))), provider->getLodCount()))
{
    tilesPerLine = provider->getWidth() / tileWidth;
    count = provider->getHeight() / tileHeight * tilesPerLine;
}

int TiledTextureDataProvider::getWidth()
{
    return width;
}

int TiledTextureDataProvider::getHeight()
{
    return height;
}

int TiledTextureDataProvider::getDepth()
{
    return count;
}

ITextureDataProvider::PixelFormat TiledTextureDataProvider::getFormat()
{
    return provider->getFormat();
}

unsigned TiledTextureDataProvider::getLodCount()
{
    return lodCount;
}

void TiledTextureDataProvider::uploadData(void* recvBuffer, unsigned lod)
{
    auto pixelSize = pixelFormatParameters[provider->getFormat()].pixelSize;
    auto atlasWidth = std::size_t(provider->getWidth()) >> lod;
    auto atlasHeight = std::size_t(provider->getHeight()) >> lod;
    auto atlasLineSize = atlasWidth * pixelSize;
    auto atlasLineSizeA = alignSize(atlasLineSize, 4);
    auto bufSize = atlasLineSizeA * atlasHeight;
    std::vector<unsigned char> buffer(bufSize);
    auto tileLineSize = std::size_t(width) * pixelSize;
    auto tileRowStride = atlasLineSizeA * std::size_t(height);
    auto tileLineStride = alignSize(tileLineSize, 4);
    auto recv = static_cast<unsigned char*>(recvBuffer);
    std::size_t tileY = 0;
    std::size_t tileX = 0;
    provider->uploadData(buffer.data(), lod);
    for (int i = 0; i < count; ++i) {
        std::size_t tileYOffset = tileY + tileX;
        for (int j = 0; j < height; ++j, tileYOffset += atlasLineSizeA, recv += tileLineStride) {
            std::memcpy(recv, buffer.data() + tileYOffset, tileLineSize);
        }
        tileX += tileLineSize;
        if (tileX < tileLineSize || tileX >= atlasLineSize) {
            tileX = 0;
            tileY += tileRowStride;
        }
    }
}

} // namespace util
