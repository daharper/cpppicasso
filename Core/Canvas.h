#ifndef CPPPICASSO_CANVAS_H
#define CPPPICASSO_CANVAS_H

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <variant>

#include "Palette.h"

// Define specific instructions
struct SetPixel { int x; int y; const std::string text; };
struct SetCanvas { int width; int height; };

// A 'Step' is any one of these instructions
using Step = std::variant<
    SetPixel,
    SetCanvas>;

// A 'Command' is a collection of steps (e.g., "Draw Rectangle" = many DrawPixels)
struct Operation {
    std::string text;
    std::vector<Step> steps;

    bool operator==(const Operation& other) const {
        return String::isSame(text, other.text);
    }

    [[nodiscard]] bool hasSteps() const noexcept { return !steps.empty(); }
};

static Operation NOP { "nop" };
static Operation UNDO { "undo" };

/**
 * @brief Represents a 2D canvas for drawing operations.
 *
 * This class provides functionality to create, manipulate, and draw on a 2D canvas.
 * Access the canvas via 1-based indexing, i.e., x: [1...width], y: [1...width].
 */
class Canvas {
public:
    Canvas();

    /**
     * @brief Undoes the last command executed on the canvas.
     */
    Operation& undo();

    Operation& setPen(char pen);
    Operation& setColors(const std::string& color, const std::string& bgColor);
    Operation& create(const std::string& command, int width, int height, const std::string& color = "white", const std::string& bgColor = "black");
    Operation& plot(const std::string& command, int x, int y, char pen);
    //Operation& line(const std::string& command, int x1, int y1, int x2, int y2, char pen);

    /**
     * @brief Returns an iterator to the beginning of the command history.
     */
    [[nodiscard]] auto begin() { return m_operations.begin(); }
    [[nodiscard]] auto begin() const { return m_operations.begin(); }
    [[nodiscard]] auto cbegin() const { return m_operations.cbegin(); }

    /**
     * @brief Returns an iterator to the end of the command history.
     */
    [[nodiscard]] auto end() { return m_operations.end(); }
    [[nodiscard]] auto end() const { return m_operations.end(); }
    [[nodiscard]] auto cend() const { return m_operations.cend(); }

    [[nodiscard]] char getPen() const { return m_pen; }
    [[nodiscard]] int getWidth() const { return m_width; }
    [[nodiscard]] int getHeight() const { return m_height; }

    static void verifyForegroundColor(const std::string &color) ;
    static void verifyBackgroundColor(const std::string &color);

    static void verifyCommand(const std::string &command);

    static std::string DEFAULT_COLOR;
    static std::string DEFAULT_BG_COLOR;

    static constexpr int MIN_WIDTH = 4;
    static constexpr int MAX_WIDTH = 40;
    static constexpr int MIN_HEIGHT = 4;
    static constexpr int MAX_HEIGHT = 20;
    static constexpr char DEFAULT_PEN = '*';

private:
    void addOperation(const std::string& text);

    // operations
    void setCanvas(int canvasWidth, int canvasHeight);
    void setPixel(int x, int y, char pen = 0);
    void setColor(const std::string& color);
    void setBgColor(const std::string& color);

    // internal command management
    void addOperationStep(const Step& step);
    void removeOperations();

    // validation methods
    void verifyPixel(int x, int y) const;
    void verifyCanvas() const;

    int m_width;
    int m_height;
    int m_color;
    int m_bgColor;
    char m_pen;

    std::vector<Operation> m_operations;
};

#endif //CPPPICASSO_CANVAS_H