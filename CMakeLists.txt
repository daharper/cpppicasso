cmake_minimum_required(VERSION 4.1)
project(cpppicasso)

set(CMAKE_CXX_STANDARD 23)

add_executable(cpppicasso main.cpp
        Graphics/Canvas.h
        Graphics/Palette.h
        Utils.h
        commands/UserCommand.h
        commands/UserCommandManager.cpp
        commands/UserCommandManager.h
        commands/CreateCanvasUserCommand.cpp
        commands/CreateCanvasUserCommand.h
        commands/CommandObject.h
        commands/CommandInputParser.cpp
        commands/CommandInputParser.h
        Graphics/Canvas.cpp
)
