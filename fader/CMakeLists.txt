project(fader)
cmake_minimum_required(VERSION 2.4.0)

find_package(Qt4 REQUIRED)

set(QT_USE_QTOPENGL TRUE)
include(${QT_USE_FILE})

set(fader_SRCS 
	main.cpp
	GLFaderWidget.cpp
 	)

set(fader_MOC_HDRS
	GLFaderWidget.h
	)

QT4_WRAP_CPP(fader_MOC_SRCS ${fader_MOC_HDRS})

add_executable(fader ${fader_SRCS} ${fader_MOC_SRCS})

target_link_libraries(fader ${QT_LIBRARIES} GL GLEW)
