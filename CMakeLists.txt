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
        render_engine/Camera.cpp
        headers/Camera.h
        render_engine/GraphicConveyor.cpp
        headers/GraphicConveyor.h
        render_engine/RenderEngine.cpp
        headers/RenderEngine.h
        render_engine/Camera.cpp
        headers/Camera.h
        math/Vector2D.cpp
        headers/Vector2D.h
        headers/Vector4D.h
        math/Vector4D.cpp
        math/Vector3D.cpp
        headers/Camera.h
        model/Model.h
        model/Polygon.cpp)
target_link_libraries(CompGraph
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

