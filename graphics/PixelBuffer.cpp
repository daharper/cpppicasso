#include "PixelBuffer.h"

#include <stdexcept>

char PixelBuffer::getPixel(const int x, const int y) const {
    verifySize();
    verifyPixel(x, y);

    // pixel is 1-based as per user's view, m_pixels is 0-based.
    return m_pixels[(y - 1) * m_width + (x - 1)];
}

void PixelBuffer::setPixel(const int x, const int y, const char pen) {
    verifySize();
    verifyPixel(x, y);

    // pixel is 1-based as per user's view, m_pixels is 0-based.
    m_pixels[(y - 1) * m_width + (x - 1)] = pen;
}

void PixelBuffer::setSize(const int width, const int height) {
    m_width = width;
    m_height = height;

    m_pixels.clear();

    // pixel is 1-based as per user's view, m_pixels is 0-based.
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            m_pixels.emplace_back(' ');
        }
    }
}

bool PixelBuffer::isSamePen(const int x, const int y, const char pen) const {
    return isValidPixel(x, y) && getPixel(x, y) == pen;
}

bool PixelBuffer::isInitialized() const {
    return m_width != 0 && m_height != 0;
}

void PixelBuffer::verifySize() const {
    if (m_height == 0 || m_width == 0) {
        throw std::invalid_argument("Pixel buffer has not been initialized.");
    }
}

bool PixelBuffer::isValidPixel(const int x, const int y) const {
    return x > 0 && x <= m_width && y > 0 && y <= m_height;
}

void PixelBuffer::verifyPixel(const int x, const int y) const {
    if (x < 1 || x > m_width || y < 1 || y > m_height) {
        throw std::out_of_range("Pixel coordinates out of range.");
    }
}