//
// Created by david on 21/1/2026.
//

#ifndef CPPPICASSO_CANVAS_H
#define CPPPICASSO_CANVAS_H

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <variant>

#include "Palette.h"

// Define specific instructions
struct SetPen { std::uint8_t ch; };
struct SetColor { std::string color; };
struct SetBgColor { std::string color; };
struct DrawPixel { int x; int y; };
struct CreateCanvas { int x; int y; };
struct ClearCanvas {};

// A 'Step' is any one of these instructions
using Step = std::variant<
    SetPen,
    SetColor,
    SetBgColor,
    DrawPixel,
    CreateCanvas,
    ClearCanvas>;

// A 'Command' is a collection of steps (e.g., "Draw Rectangle" = many DrawPixels)
struct Command {
    std::string text; // e.g., "RECT 1 1 5 5"
    std::vector<Step> steps;
};

/**
 * @brief Represents a 2D canvas for drawing operations.
 *
 * This class provides functionality to create, manipulate, and draw on a 2D canvas.
 * Access the canvas via 1-based indexing, i.e., x: [1...width], y: [1...width].
 */
class Canvas {
public:
    static constexpr int MIN_WIDTH = 1;
    static constexpr int MAX_WIDTH = 40;
    static constexpr int MIN_HEIGHT = 1;
    static constexpr int MAX_HEIGHT = 40;

    static constexpr std::uint8_t DEFAULT_PEN = '@';

    void reset() {
        width = 0;
        height = 0;
        commands.clear();
    }

    /**
     * @brief Adds a command to the canvas history.
     *
     * @param text The command to add.
     */
    void addCommand(const std::string& text) {
        if (text.empty()) {
            throw std::invalid_argument("Command text cannot be empty.");
        }

        this->commands.emplace_back(text, std::vector<Step>());
    }

    /**
     * @brief Undoes the last command executed on the canvas.
     */
    void undo(){
        if (!commands.empty()) commands.pop_back();
    }

    /**
     * @brief Creates a new Canvas with the specified dimensions.
     *
     * @param canvasWidth The width in pixels (must be between min and max width).
     * @param canvasHeight The height in pixels (must be between min and max height).
     * @return An optional containing the Canvas, or std::nullopt if dimensions are invalid.
     */
    void create(const int canvasWidth, const int canvasHeight){
        if (canvasWidth < MIN_WIDTH || canvasWidth > MAX_WIDTH) {
            throw std::invalid_argument("Width must be between " + std::to_string(MIN_WIDTH) + " and " + std::to_string(MAX_WIDTH));
        }

        if (canvasHeight < MIN_HEIGHT || canvasHeight > MAX_HEIGHT) {
            throw std::invalid_argument("Height must be between " + std::to_string(MIN_HEIGHT) + " and " + std::to_string(MAX_HEIGHT));
        }

        this->width = canvasWidth;
        this->height = canvasHeight;

        addStep(CreateCanvas{width, height});
    }
    /**
     * @brief Clears the canvas.
     */
    void clear() {
        addStep(ClearCanvas{});
    }

    /**
     * @brief Sets the drawing pen color.
     * @param ch The character to use for subsequent drawing operations.
     */
    void setPen(const std::uint8_t ch) {
        addStep(SetPen{ch});
    }

    /**
     * @brief Sets the foreground color.
     * @param color The desired color from the palette.
     */
    void setColor(const std::string& color) {
        Palette::validate(color);
        addStep(SetColor{color});
    }

    /**
     * @brief Sets the background color.
     * @param color The desired background color from the palette.
     */
    void setBgColor(const std::string& color) {
        Palette::validate(color);
        addStep(SetBgColor(color));
    }

    /**
     * @brief Sets a pixel on the canvas, using the drawing pen color.
     * @param x The x-coordinate of the pixel (1-based index).
     * @param y The y-coordinate of the pixel (1-based index).
     */
    void setPixel(const int x, const int y) {
        verifyPixel(x, y);
        addStep(DrawPixel{x-1, y-1});
    }

    /**
     * @brief Returns an iterator to the beginning of the command history.
     */
    [[nodiscard]] auto begin() { return commands.begin(); }
    [[nodiscard]] auto begin() const { return commands.begin(); }
    [[nodiscard]] auto cbegin() const { return commands.cbegin(); }

    /**
     * @brief Returns an iterator to the end of the command history.
     */
    [[nodiscard]] auto end() { return commands.end(); }
    [[nodiscard]] auto end() const { return commands.end(); }
    [[nodiscard]] auto cend() const { return commands.cend(); }

private:
    void addStep(const Step& step) {
        if (commands.empty()) {
            throw std::invalid_argument("Cannot add step to empty canvas.");
        }

        commands.back().steps.push_back(step);
    }

    void verifyPixel(const int x, const int y) const {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            throw std::out_of_range("Pixel coordinates out of range.");
        }
    }

    void verifyCanvas() const {
        if (width == 0 || height == 0) {
            throw std::invalid_argument("There is no canvas.");
        }
    }

    int width = 0;
    int height = 0;

    std::vector<Command> commands;
};

#endif //CPPPICASSO_CANVAS_H