cmake_minimum_required(VERSION 3.29)
project(CompGraph)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/mingw_64/lib/cmake")
#set(CMAKE_PREFIX_PATH "/Applications/QT/6.8.0/macos/lib/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
add_definitions(-DQT_NO_OPENGL)
file(GLOB
        CPPS "*.cpp"
        HPP "*.h")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

include_directories(src/forms)

add_executable(${PROJECT_NAME} ${CPPS} ${HPP}
        src/forms/CustomView.h
        src/forms/CustomView.cpp
        src/forms/mainwindow.cpp
        src/math/src/DepthBuffer.cpp
        src/math/src/MathCast.cpp
        src/math/src/MathOperations.cpp
        src/math/src/Matrix3D.cpp
        src/math/src/Matrix4D.cpp
        src/math/src/PixelBuffer.cpp
        src/math/src/Point2D.cpp
        src/math/src/Point3D.cpp
        src/math/src/Vector2D.cpp
        src/math/src/Vector3D.cpp
        src/math/src/Vector4D.cpp
        src/model/src/Polygon.cpp
        src/model/src/Triangle.cpp
        src/obj_utils/objreader/ObjReader.cpp
        src/obj_utils/objwriter/ObjWriter.cpp
        src/render_engine/src/GraphicConveyor.cpp
        src/render_engine/src/Camera.cpp
        src/render_engine/src/Illumination.cpp
        src/render_engine/src/Mesh.cpp
        src/render_engine/src/Rasterization.cpp
        src/render_engine/src/RenderEngine.cpp
        src/render_engine/src/Texture.cpp
        resources/resources.qrc
        src/render_engine/src/RenderEngine.cpp
        src/render_engine/src/Camera.cpp
        src/model/src/Polygon.cpp
        src/math/src/Vector2D.cpp
        src/math/src/Vector3D.cpp
        src/math/src/Vector4D.cpp
        src/render_engine/src/GraphicConveyor.cpp
        src/math/src/Matrix4D.cpp
        src/math/src/Matrix4D.cpp
        src/forms/mainwindow.cpp
        src/forms/mainwindow.ui
        src/forms/mainwindow.h
        src/obj_utils/objreader/ObjReader.cpp
        src/obj_utils/objreader/ObjReader.h
        src/obj_utils/objwriter/ObjWriter.cpp
        src/obj_utils/objreader/ObjReaderException.h
        src/math/src/Matrix3D.cpp
        src/math/src/Point2D.cpp
        src/model/src/Triangle.cpp
        src/model/headers/Triangle.h
        src/obj_utils/objwriter/ObjWriter.h
        src/render_engine/headers/Camera.h
        src/model/headers/Model.h
        src/math/headers/Matrix3D.h
        src/math/headers/Matrix4D.h
        src/math/headers/Point2D.h
        src/math/headers/Vector3D.h
        src/math/headers/Vector4D.h
        src/math/src/Point3D.cpp
        src/math/src/DepthBuffer.cpp
        src/math/headers/DepthBuffer.h
        src/render_engine/headers/TypeOfRender.h
        src/render_engine/headers/Renderable.h
        src/render_engine/src/Illumination.cpp
        src/render_engine/src/Illumination.cpp
        src/render_engine/src/Texture.cpp
        src/render_engine/headers/Texture.h
        src/render_engine/src/Rasterization.cpp
        src/render_engine/headers/Rasterization.h
        src/math/headers/MathCast.h
        src/math/src/MathCast.cpp
        src/render_engine/src/Mesh.cpp
        src/math/headers/MathOperations.h
        src/math/src/MathOperations.cpp
        src/math/src/MathOperations.cpp
        src/render_engine/headers/Material.h
        src/render_engine/src/Material.cpp
        src/render_engine/src/RemoveElements.cpp
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
