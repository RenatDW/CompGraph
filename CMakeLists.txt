cmake_minimum_required(VERSION 3.29)
project(CompGraph)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(CompGraph main.cpp
        main.cpp
        main.cpp
        render_engine/Camera.cpp
        render_engine/Camera.h
        render_engine/GraphicConveyor.cpp
        render_engine/GraphicConveyor.h
        render_engine/RenderEngine.cpp
        render_engine/RenderEngine.h
        render_engine/Camera.cpp
        render_engine/Camera.h
        math/Vector2D.cpp
        math/Vector2D.h)
target_link_libraries(CompGraph
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

