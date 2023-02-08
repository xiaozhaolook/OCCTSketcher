cmake_minimum_required(VERSION 3.12)
project( OCCTSketcher)  

set(CMAKE_INCLUDE_CURRENT_DIR ON)  

#find_package(Qt5 REQUIRED Core QUIET COMPONENTS Xml Script OpenGL Svg)
#
#find_package(Qt5Widgets)
#include_directories(${PROJECT_SOURCE_DIR}
#                    ${CMAKE_CURRENT_BINARY_DIR}
#					$ENV{OCCT_INCLUDES}
#					)
#FILE(GLOB OCCT_LIBRARIES "D:/Program Files (x86)/OCCT/win32/vc14/lib/*.lib")
#LINK_LIBRARIES(${OCCT_LIBRARIES})

# find QT
set(TARGET_QT_PATH "" CACHE PATH "QT install path")
if(EXISTS ${TARGET_QT_PATH})
	message(STATUS "Directory to search QT at ${TARGET_QT_PATH}")
	list(APPEND CMAKE_PREFIX_PATH ${TARGET_QT_PATH})
else()
	message(WARNING "File/Directory at variable TARGET_QT_PATH not exists!")
endif()
find_package(Qt5 COMPONENTS Core OpenGL Widgets Gui Gamepad PrintSupport REQUIRED QUIET)
find_package(Qt5Widgets)

# find OpenCascade
set(TARGET_OCC_PATH "" CACHE PATH "OCC install path")
if(EXISTS ${TARGET_OCC_PATH})
	message(STATUS "Directory to search OCC at ${TARGET_OCC_PATH}")
	list(APPEND CMAKE_PREFIX_PATH ${TARGET_OCC_PATH})
else()
	message(WARNING "File/Directory at variable TARGET_OCC_PATH not exists!")
endif()
find_package(OpenCASCADE CONFIG REQUIRED)

include_directories(${OpenCASCADE_INCLUDE_DIR})

FILE(GLOB PROJECT_SRC_FILES
	"src/*.h"
	"src/*.cpp"
)

SET(PROJECT_UI
	mainwindow.ui
)

SET( RESOURCE
	occqt.qrc
)

FILE(GLOB PROJECT_MOC_HDRS  
	"src/*.h"
)  

QT5_WRAP_UI( PROJECT_UIS_H  
	${PROJECT_UI}  
	)  

QT5_WRAP_CPP( PROJECT_MOC_SRCS  
	${PROJECT_MOC_HDRS}  
	)

QT5_ADD_RESOURCES(RESOURCE_ADDED ${RESOURCE})

	
ADD_EXECUTABLE( ${PROJECT_NAME}
	${PROJECT_SRC_FILES}  
	${PROJECT_UIS_H}  
	${PROJECT_MOC_SRCS} 
	${RESOURCE_ADDED}
	)

target_link_libraries(${PROJECT_NAME}  Qt5::Core Qt5::Gui Qt5::Widgets Qt5::PrintSupport Qt5::Gamepad Qt5::OpenGL)
target_link_libraries(${PROJECT_NAME} ${OpenCASCADE_LIBRARIES})
#TARGET_LINK_LIBRARIES ( ${PROJECT_NAME}
#	Qt5::Widgets
#	Qt5::Core
#	Qt5::Gui
#	Qt5::OpenGL
#  )
