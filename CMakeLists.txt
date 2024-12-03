cmake_minimum_required(VERSION 3.29)
project(CompGraph)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/mingw_64/lib/cmake")
#set(CMAKE_PREFIX_PATH "/Applications/QT/6.8.0/macos/lib/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

file(GLOB
        CPPS "*.cpp"
        HPP "*.h")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(${PROJECT_NAME} ${CPPS} ${HPP}
        resources/resources.qrc
        render_engine/src/RenderEngine.cpp
        render_engine/src/Camera.cpp
        model/src/Polygon.cpp
        math/src/Vector2D.cpp
        math/src/Vector3D.cpp
        math/src/Vector4D.cpp
        render_engine/src/GraphicConveyor.cpp
        math/src/Matrix4D.cpp
        math/src/Matrix4D.cpp
        forms/src/mainwindow.cpp
        forms/mainwindow.ui
        forms/headers/mainwindow.h
        obj_utils/objreader/src/ObjReader.cpp
        obj_utils/objreader/headers/ObjReader.h
        obj_utils/objwriter/src/ObjWriter.cpp
        obj_utils/objreader/headers/ObjReaderException.h
        math/src/Matrix3D.cpp
        math/src/Point2D.cpp
        model/src/Triangle.cpp
        model/headers/Triangle.h
        obj_utils/objwriter/headers/ObjWriter.h
        render_engine/headers/Camera.h
        model/headers/Model.h
        math/headers/Matrix3D.h
        math/headers/Matrix4D.h
        math/headers/Point2D.h
        math/headers/Vector3D.h
        math/headers/Vector4D.h
        math/src/Point3D.cpp
        math/src/DepthBuffer.cpp
        math/headers/DepthBuffer.h
        render_engine/headers/TypeOfRender.h
        render_engine/headers/Renderable.h
        render_engine/src/Illumination.cpp
        render_engine/src/Illumination.cpp
        render_engine/src/Texturezation.cpp
        render_engine/headers/Texturezation.h
        render_engine/src/Rasterization.cpp
        render_engine/headers/Rasterization.h
        math/headers/MathCast.h
        math/src/MathCast.cpp
        render_engine/src/Mesh.cpp
        math/headers/MathOperations.h
        math/src/MathOperations.cpp
        math/src/MathOperations.cpp
        math/headers/PixelBuffer.h
        math/src/PixelBuffer.cpp
)

target_link_libraries(CompGraph
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

add_subdirectory(Google_tests)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
