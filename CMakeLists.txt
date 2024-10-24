cmake_minimum_required(VERSION 3.29)
project(CompGraph)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB
        CPPS "*.cpp"
        HPP "*.h")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(${PROJECT_NAME} ${CPPS} ${HPP}
        math/Vector2D.cpp
        render_engine/RenderEngine.cpp
        render_engine/Camera.cpp
        model/Polygon.cpp
        math/Vector3D.cpp
        math/Vector4D.cpp
        render_engine/GraphicConveyor.cpp
        headers/Model.h
        math/Matrix4D.cpp
        headers/Matrix4D.h
        math/Matrix4D.cpp)


target_link_libraries(CompGraph
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

