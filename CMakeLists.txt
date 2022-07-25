cmake_minimum_required(VERSION 3.5)

project(sokoban
    DESCRIPTION "Sokoban clone written in C++ using OpenGL API"
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_EXTENSIONS OFF)

find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(sokoban
    src/glwrp/Context.cpp
    src/glwrp/Context.h
    src/glwrp/gl31.cpp
    src/glwrp/gl31.h
    src/glwrp/GLImportedFunction.cpp
    src/glwrp/GLImportedFunction.h
    src/glwrp/ShaderProgramMaker.cpp
    src/glwrp/ShaderProgramMaker.h
    src/platform/win32.h
    src/sokoban/CloseEvent.cpp
    src/sokoban/CloseEvent.h
    src/sokoban/Game.cpp
    src/sokoban/Game.h
    src/sokoban/KeyEvent.cpp
    src/sokoban/KeyEvent.h
    src/sokoban/LevelLogic.cpp
    src/sokoban/LevelLogic.h
    src/sokoban/RedrawEvent.cpp
    src/sokoban/RedrawEvent.h
    src/sokoban/ResizeEvent.cpp
    src/sokoban/ResizeEvent.h
    src/sokoban/shaderProgram.cpp
    src/sokoban/shaderProgram.h
    src/sokoban/Terminal.cpp
    src/sokoban/Terminal.h
    src/sokoban/Terminal_priv.h
    src/util/ArrayTextureDataProvider.cpp
    src/util/ArrayTextureDataProvider.h
    src/util/BitmapTextureDataProvider.cpp
    src/util/BitmapTextureDataProvider.h
    src/util/Event.h
    src/util/EventHelper.h
    src/util/handlers2.h
    src/util/ITextureDataProvider.cpp
    src/util/ITextureDataProvider.h
    src/util/mat.cpp
    src/util/mat.h
    src/util/matrixmath.h
    src/util/Observer.cpp
    src/util/Observer.h
    src/util/observer1.h
    src/util/util.cpp
    src/util/util.h
    src/util/vec.cpp
    src/util/vec.h
)
target_include_directories(sokoban PRIVATE src/gl src)
target_compile_definitions(sokoban PRIVATE _WIN32_WINNT=0x602)
target_compile_options(sokoban PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors)
target_link_libraries(sokoban PRIVATE Threads::Threads OpenGL::GL)

install(TARGETS sokoban DESTINATION .)
install(DIRECTORY assets DESTINATION .)
