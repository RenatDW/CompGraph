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
        render_engine/RenderEngine.cpp
        render_engine/Camera.cpp
        model/Polygon.cpp
        math/Vector2D.cpp
        math/Vector3D.cpp
        math/Vector4D.cpp
        render_engine/GraphicConveyor.cpp
        math/Matrix4D.cpp
        math/Matrix4D.cpp
        forms/mainwindow.cpp
        forms/mainwindow.ui
        headers/mainwindow.h
        objreader/ObjReader.cpp
        headers/ObjReader.h
        objwriter/ObjWriter.cpp
        objreader/ObjReaderException.cpp
        headers/ObjReaderException.h
        main.cpp
        main.cpp
        main.cpp
        main.cpp
        main.cpp
        main.cpp
        main.cpp)


target_link_libraries(CompGraph
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

