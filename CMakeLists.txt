cmake_minimum_required(VERSION 4.1)
project(cpppicasso)

set(CMAKE_CXX_STANDARD 23)

add_executable(cpppicasso main.cpp
        Graphics/Canvas.h
        Graphics/Palette.h
        Utils.h
        commands/Command.h
        commands/CommandManager.cpp
        commands/CommandManager.h
        commands/CreateCanvasCommand.cpp
        commands/CreateCanvasCommand.h
        commands/CommandObject.h
        commands/CommandInputParser.cpp
        commands/CommandInputParser.h
        Graphics/Canvas.cpp
        Graphics/Renderer.cpp
        Graphics/Renderer.h
)
