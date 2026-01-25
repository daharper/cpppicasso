cmake_minimum_required(VERSION 4.1)
project(cpppicasso)

set(CMAKE_CXX_STANDARD 23)

add_executable(cpppicasso main.cpp
        Core/Canvas.h
        Core/Palette.h
        Utils.h
        commands/Command.h
        commands/CommandManager.cpp
        commands/CommandManager.h
        commands/CreateCanvasCommand.cpp
        commands/CreateCanvasCommand.h
        commands/CommandObject.h
        commands/CommandInputParser.cpp
        commands/CommandInputParser.h
        Core/Canvas.cpp
        Core/Console.cpp
        Core/Console.h
        commands/PlotCommand.cpp
        commands/PlotCommand.h
)
