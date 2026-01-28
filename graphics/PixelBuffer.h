#ifndef CPPPICASSO_PIXELS_H
#define CPPPICASSO_PIXELS_H

#include <memory>
#include <vector>

class PixelBuffer {
public:
    static PixelBuffer& getInstance() {
        static PixelBuffer instance;
        return instance;
    }

    static std::unique_ptr<PixelBuffer> snapshot() {
        return std::unique_ptr<PixelBuffer>(
            new PixelBuffer(getInstance())
        );
    }

    PixelBuffer& operator=(const PixelBuffer&) = delete;

    [[nodiscard]] char getPixel(int x, int y) const;
    [[nodiscard]] bool isSamePen(int x, int y, char pen) const;

    void setPixel(int x, int y, char pen);
    void setSize(int width, int height);

    [[nodiscard]] int getWidth() const {
        return m_width;
    }

    [[nodiscard]] int getHeight() const {
        return m_height;
    }

private:
    PixelBuffer() = default;
    PixelBuffer(const PixelBuffer&) = default;

    void verifySize() const;
    void verifyPixel(int x, int y) const;

    [[nodiscard]] bool isValidPixel(int x, int y) const;
    [[nodiscard]] bool isInitialized() const;

    int m_width{0};
    int m_height{0};

    std::vector<char> m_pixels;
};


#endif //CPPPICASSO_PIXELS_H