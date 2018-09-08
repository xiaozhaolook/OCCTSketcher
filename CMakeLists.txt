cmake_minimum_required( VERSION 2.8.11 )  
project( OCCTSketcher)  

set(CMAKE_INCLUDE_CURRENT_DIR ON)  

find_package(Qt5 REQUIRED Core QUIET COMPONENTS Xml Script OpenGL Svg)

find_package(Qt5Widgets)  
include_directories(${PROJECT_SOURCE_DIR}  
                    ${CMAKE_CURRENT_BINARY_DIR}
					$ENV{OCCT_INCLUDES}
					)  
FILE(GLOB OCCT_LIBRARIES "D:/Program Files (x86)/OCCT/win32/vc14/lib/*.lib")
LINK_LIBRARIES(${OCCT_LIBRARIES})

FILE(GLOB PROJECT_SRC_FILES
	"*.h"
	"*.cpp"
)

SET(PROJECT_UI
	mainwindow.ui
)

SET( RESOURCE
	occqt.qrc
)

FILE(GLOB PROJECT_MOC_HDRS  
	"*.h"
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

TARGET_LINK_LIBRARIES ( ${PROJECT_NAME}
	Qt5::Widgets  
	Qt5::Core
	Qt5::Gui
	Qt5::OpenGL
  )
