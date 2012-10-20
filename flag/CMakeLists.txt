project(flag)
cmake_minimum_required(VERSION 2.4.0)

find_package(Qt4 REQUIRED)

set(QT_USE_QTOPENGL TRUE)
include(${QT_USE_FILE})

set(flag_SRCS 
	main.cpp
    GLFlagWidget.cpp
    GLWidget.cpp
    GLMesh.cpp
    GLProgram.cpp
    FlagMesh.cpp
    )

set(flag_MOC_HDRS
    GLFlagWidget.h
    GLWidget.h
	)

QT4_WRAP_CPP(flag_MOC_SRCS ${flag_MOC_HDRS})

add_executable(flag ${flag_SRCS} ${flag_MOC_SRCS})

target_link_libraries(flag ${QT_LIBRARIES} GL GLEW)
