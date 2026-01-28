#ifndef CPPPICASSO_CANVAS_H
#define CPPPICASSO_CANVAS_H

#include <vector>
#include <string>
#include <variant>

#include "Palette.h"
#include "PixelBuffer.h"

// Define specific instructions
struct SetPixel { int x; int y; const std::string text; const char pen; };
struct SetCanvas { int width; int height; };

// A 'Step' is any one of these instructions
using Step = std::variant<
    SetPixel,
    SetCanvas>;

enum class OpKind { Nop, Mutation, Normal };

// A 'Command' is a collection of steps (e.g., "Draw Rectangle" = many DrawPixels)
struct Operation {
    OpKind kind {OpKind::Normal};

    std::string text;
    std::vector<Step> steps;

    bool operator==(const Operation& other) const {
        return String::isSame(text, other.text);
    }

    [[nodiscard]] bool hasSteps() const noexcept { return !steps.empty(); }
};

static Operation NOP { OpKind::Nop, "nop" };
static Operation MUTATION { OpKind::Mutation, "undo" };

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
    Operation& line(const std::string& command, int x1, int y1, int x2, int y2, char pen);
    Operation& rectangle(const std::string& command, int x, int y, int width, int height,  char pen);
    Operation& triangle(const std::string &command, int x1, int y1, int x2, int y2, int x3, int y3, char pen);
    Operation& write(const std::string& command, int x, int y, const std::string& text);
    Operation& fill(const std::string& command, int x, int y, char pen);

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

    void removeOperations();

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
    static constexpr char DEFAULT_BG_PEN = ' ';

private:
    void addOperation(const std::string& text);

    // operations
    void setCanvas(int canvasWidth, int canvasHeight);
    void setPixel(int x, int y, char pen = 0);
    void setColor(const std::string& color);
    void setBgColor(const std::string& color);

    // internal command management
    void addOperationStep(const Step& step);

    // validation methods
    void verifyPixel(int x, int y) const;
    void verifyCanvas() const;

    void drawHorizontalLine(int x1, int x2, int y, char pen);
    void drawVerticalLine(int x, int y1, int y2, char pen);
    void drawDiagonalLine(int x1, int y1, int x2, int y2, char pen);

    void plotFill(PixelBuffer& buffer, int x, int y, char pen, char targetPen);

    int m_width;
    int m_height;
    int m_color;
    int m_bgColor;
    char m_pen;

    std::vector<Operation> m_operations;
};

#endif //CPPPICASSO_CANVAS_H