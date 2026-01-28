cmake_minimum_required(VERSION 4.1)
project(cpppicasso)

set(CMAKE_CXX_STANDARD 23)

add_executable(cpppicasso main.cpp
        Core/Canvas.h
        Core/Palette.h
        Utils.h
        command/Command.h
        command/CommandManager.cpp
        command/CommandManager.h
        commands/CanvasCommand.h
        command/CommandObject.h
        command/CommandInputParser.cpp
        command/CommandInputParser.h
        Core/Canvas.cpp
        Core/Console.cpp
        Core/Console.h
        commands/PlotCommand.h
        Core/Help.h
        commands/UndoCommand.h
        commands/SetPenCommand.h
        commands/SaveCommand.h
        commands/LoadCommand.h
        commands/LineCommand.h
        commands/RectangleCommand.h
        Core/PixelBuffer.cpp
        Core/PixelBuffer.h
        commands/FillCommand.h
        commands/TriangleCommand.h
        commands/WriteCommand.h
)
