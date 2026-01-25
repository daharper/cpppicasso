#include "Canvas.h"

std::string Canvas::DEFAULT_COLOR = "white";
std::string Canvas::DEFAULT_BG_COLOR = "black";

Canvas::Canvas() {
    m_width = 0;
    m_height = 0;
    m_color = Palette::getForeground("white");
    m_bgColor = Palette::getBackground("black");
    m_pen = DEFAULT_PEN;
}

#pragma region Graphics

Operation& Canvas::create(const std::string& command, const int width, const int height, const std::string& color, const std::string& bgColor) {
    addOperation(command);

    setCanvas(width, height);
    setColor(color);
    setBgColor(bgColor);

    return m_operations.back();
}

Operation& Canvas::plot(const std::string& command, const int x, const int y, const char pen) {
    addOperation(command);

    setPixel(x, y, pen);

    return m_operations.back();
}

#pragma endregion

#pragma region Operations

void Canvas::setCanvas(const int canvasWidth, const int canvasHeight){
    if (canvasWidth < MIN_WIDTH || canvasWidth > MAX_WIDTH) {
        throw std::invalid_argument("Width must be between " + std::to_string(MIN_WIDTH) + " and " + std::to_string(MAX_WIDTH));
    }

    if (canvasHeight < MIN_HEIGHT || canvasHeight > MAX_HEIGHT) {
        throw std::invalid_argument("Height must be between " + std::to_string(MIN_HEIGHT) + " and " + std::to_string(MAX_HEIGHT));
    }

    removeOperations();

    m_width = canvasWidth;
    m_height = canvasHeight;

    addOperationStep(SetCanvas{canvasWidth, canvasHeight});
}

void Canvas::setPixel(const int x, const int y, const char pen) {
    verifyPixel(x, y);
    const std::string p = { pen == 0 ? m_pen : pen };
    const auto text = Palette::format(m_color, m_bgColor, p);
    addOperationStep(SetPixel{x, y, text});
}

void Canvas::setColor(const std::string& color) {
    m_color = Palette::getForeground(color);
    //addOperationStep(SetColor{m_color});
}

void Canvas::setBgColor(const std::string& color) {
    m_bgColor = Palette::getBackground(color);
    //addOperationStep(SetBgColor({m_bgColor}));
}

void Canvas::setPen(const char pen) {
    m_pen = pen;
    //addOperationStep(SetPen{m_pen});
}


#pragma endregion

#pragma region Command Management

void Canvas::addOperation(const std::string& text) {
    if (text.empty()) {
        throw std::invalid_argument("Command text cannot be empty.");
    }

    this->m_operations.emplace_back(text, std::vector<Step>());
}

void Canvas::addOperationStep(const Step& step) {
    if (m_operations.empty()) {
        throw std::invalid_argument("Cannot add step to empty canvas.");
    }

    m_operations.back().steps.push_back(step);
}

void Canvas::undoOperation(){
    if (!m_operations.empty()) m_operations.pop_back();
}

void Canvas::removeOperations() {
    if (!m_operations.empty()) {
        m_operations.erase(m_operations.begin(), prev(m_operations.end()));
    }
}

#pragma endregion

#pragma region Validation Methods

void Canvas::verifyPixel(const int x, const int y) const {
    verifyCanvas();

    if (x < 1 || x > m_width || y < 1 || y > m_height) {
        throw std::out_of_range("Pixel coordinates out of range.");
    }
}

void Canvas::verifyCanvas() const {
    if (m_width == 0 || m_height == 0) {
        throw std::invalid_argument("There is no canvas.");
    }
}

#pragma endregion