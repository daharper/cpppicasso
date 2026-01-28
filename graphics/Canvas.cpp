#include "Canvas.h"

#include "PixelBuffer.h"

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

Operation& Canvas::setPen(const char pen) {
    m_pen = pen;
    return NOP;
}

Operation& Canvas::setColors(const std::string& color, const std::string& bgColor) {
    m_color = Palette::getForeground(color);
    m_bgColor = Palette::getBackground(bgColor);
    return NOP;
}

Operation& Canvas::create(const std::string& command, const int width, const int height, const std::string& color, const std::string& bgColor) {
    addOperation(command);

    setCanvas(width, height);
    setColor(color);
    setBgColor(bgColor);

    return m_operations.back();
}

Operation& Canvas::plot(const std::string& command, const int x, const int y, const char pen) {
    verifyPixel(x, y);

    addOperation(command);

    setPixel(x, y, pen);

    return m_operations.back();
}

Operation& Canvas::rectangle(const std::string& command, const int x, const int y, const int width, const int height,  const char pen) {
    const int x2 = x + width - 1;
    const int y2 = y + height - 1;

    verifyPixel(x, y);
    verifyPixel(x2, y2);

    addOperation(command);

    for (int i = x; i <= x2; ++i) {
        setPixel(i, y, pen);
        setPixel(i, y2, pen);
    }

    for (int i = y; i <= y2; ++i) {
        setPixel(x, i, pen);
        setPixel(x2, i, pen);
    }

    return m_operations.back();
}

Operation& Canvas::triangle(const std::string& command, const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, const char pen) {
    verifyPixel(x1, y1);
    verifyPixel(x2, y2);
    verifyPixel(x3, y3);

    addOperation(command);

    drawDiagonalLine(x1, y1, x2, y2, pen);
    drawDiagonalLine(x2, y2, x3, y3, pen);
    drawDiagonalLine(x3, y3, x1, y1, pen);

    return m_operations.back();
}

Operation & Canvas::write(const std::string &command, const int x, const int y, const std::string &text) {
    verifyPixel(x, y);

    addOperation(command);

    for (int i = 0; i < text.length(); i++) {
        if (x + i > m_width) break;
        setPixel(x + i, y, text[i]);
    }

    return m_operations.back();
}

void Canvas::plotFill(PixelBuffer& buffer, const int x, const int y, const char pen, const char targetPen) {
    if (buffer.isSamePen(x, y, targetPen)) {
        setPixel(x, y, pen);
        buffer.setPixel(x, y, pen);

        if (buffer.isSamePen(x + 1, y, targetPen)) {
            plotFill(buffer, x + 1, y, pen, targetPen);
        }

        if (buffer.isSamePen(x - 1, y, targetPen)) {
            plotFill(buffer, x - 1, y, pen, targetPen);
        }

        if (buffer.isSamePen(x, y + 1, targetPen)) {
            plotFill(buffer, x, y + 1, pen, targetPen);
        }

        if (buffer.isSamePen(x, y - 1, targetPen)) {
            plotFill(buffer, x, y - 1, pen, targetPen);
        }
    }
}

Operation& Canvas::fill(const std::string& command, const int x, const int y, const char pen) {
    verifyPixel(x, y);

    addOperation(command);

    const auto buffer = PixelBuffer::snapshot();
    const auto targetPen = buffer->getPixel(x, y);

    plotFill(*buffer, x, y, pen, targetPen);

    return m_operations.back();
}

Operation& Canvas::line(const std::string& command, const int x1, const int y1, const int x2, const int y2, const char pen) {
    verifyPixel(x1, y1);
    verifyPixel(x2, y2);

    addOperation(command);

    if (x1 == x2) {
        drawVerticalLine(x1, y1, y2, pen);
    } else if (y1 == y2) {
        drawHorizontalLine(x1, x2, y1, pen);
    } else {
        drawDiagonalLine(x1, y1, x2, y2, pen);
    }

    return m_operations.back();
}

void Canvas::drawHorizontalLine(const int x1, const int x2, const int y, const char pen) {
    int startX{x1};
    int endX {x2};

    if (x1 > x2) {
        startX = x2;
        endX = x1;
    }

    for (int x = startX; x <= endX; ++x) {
        setPixel(x, y, pen);
    }
}

void Canvas::drawVerticalLine(const int x, const int y1, const int y2, const char pen) {
    int startY{y1};
    int endY {y2};

    if (y1 > y2) {
        startY = y2;
        endY = y1;
    }

    for (int y = startY; y <= endY; ++y) {
        setPixel(x, y, pen);
    }
}

void Canvas::drawDiagonalLine(int x1, int y1, int x2, int y2, char pen) {
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        setPixel(x1, y1, pen);

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;

        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}

Operation& Canvas::undo(){
    // nothing recorded, nothing to undo
    if (m_operations.empty()) {
        return NOP;
    }

    // index of the last operation
    const auto i = m_operations.size() - 1;

    // no steps mean this operation is a NOP: discard it
    if (!m_operations[i].hasSteps()) {
        m_operations.pop_back();
        return NOP;
    }

    // can't undo the initial canvas setup
    if (std::holds_alternative<SetCanvas>(m_operations[i].steps.front())) {
        return NOP;
    }

    // undo the last real operation
    m_operations.pop_back();
    return MUTATION;
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
    const std::string p = { pen == 0 ? m_pen : pen };
    const auto text = Palette::format(m_color, m_bgColor, p);
    addOperationStep(SetPixel{x, y, text, pen});
}

void Canvas::setColor(const std::string& color) {
    m_color = Palette::getForeground(color);
}

void Canvas::setBgColor(const std::string& color) {
    m_bgColor = Palette::getBackground(color);
}

#pragma endregion

#pragma region Command Management

void Canvas::addOperation(const std::string& text) {
    if (text.empty()) {
        throw std::invalid_argument("Command text cannot be empty.");
    }

    this->m_operations.emplace_back(OpKind::Normal, text, std::vector<Step>());
}

void Canvas::addOperationStep(const Step& step) {
    if (m_operations.empty()) {
        throw std::invalid_argument("Cannot add step to empty canvas.");
    }

    m_operations.back().steps.push_back(step);
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

void Canvas::verifyForegroundColor(const std::string& color) {
    Palette::validateForeground(color);
}

void Canvas::verifyBackgroundColor(const std::string& color) {
    Palette::validateBackground(color);
}

void Canvas::verifyCommand(const std::string& command) {
    if (String::isBlank(command)) {
        throw std::invalid_argument("Missing command: " + command);
    }
}

#pragma endregion