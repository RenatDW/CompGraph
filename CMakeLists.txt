cmake_minimum_required(VERSION 3.29)
project(CompGraph)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/mingw_64/lib/cmake")

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
        headers/ObjReaderException.h
        main.cpp
        main.cpp
        main.cpp
        main.cpp
        main.cpp
        main.cpp
        main.cpp
        main.cpp
        main.cpp
        main.cpp
        math/Matrix3D.cpp
        headers/ObjReaderTest.h
        math/Point2D.cpp
        main.cpp
        model/Triangle.cpp
        headers/Triangle.h
        model/Model.cpp)


target_link_libraries(CompGraph
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

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

