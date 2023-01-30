#-------------------------------------------------
#
# Project created by QtCreator 2018-09-08T06:53:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

TARGET = OCCTSketcher
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
         Geom2d_Arc.cpp \
           Geom2d_Edge.cpp \
             Sketcher.cpp \
             Sketcher_AnalyserSnap.cpp \
             Sketcher_Command.cpp \
             Sketcher_CommandArc3P.cpp \
             Sketcher_CommandArcCenter2P.cpp \
             Sketcher_CommandBezierCurve.cpp \
             Sketcher_CommandCircle2PTan.cpp \
             Sketcher_CommandCircle3P.cpp \
             Sketcher_CommandCircle3Tan.cpp \
             Sketcher_CommandCircleCenterRadius.cpp \
             Sketcher_CommandCircleP2Tan.cpp \
             Sketcher_CommandLine2P.cpp \
             Sketcher_CommandPoint.cpp \
             Sketcher_CommandTrim.cpp \
             Sketcher_GUI.cpp \
             Sketcher_Object.cpp \
             Sketcher_QtGUI.cpp \
             Sketcher_Snap.cpp \
             Sketcher_SnapCenter.cpp \
             Sketcher_SnapEnd.cpp \
             Sketcher_SnapIntersection.cpp \
             Sketcher_SnapLine.cpp \
             Sketcher_SnapLineParallel.cpp \
             Sketcher_SnapLinePerpendicular.cpp \
             Sketcher_SnapMiddle.cpp \
             Sketcher_SnapNearest.cpp \
             Sketcher_SnapTangent.cpp \


HEADERS += \
        mainwindow.h \
         Geom2d_Arc.h \
            Geom2d_Edge.h \
            Sketcher.h \
            Sketcher_AnalyserSnap.h \
            Sketcher_Command.h \
            Sketcher_CommandArc3P.h \
            Sketcher_CommandArcCenter2P.h \
            Sketcher_CommandBezierCurve.h \
            Sketcher_CommandCircle2PTan.h \
            Sketcher_CommandCircle3P.h \
            Sketcher_CommandCircle3Tan.h \
            Sketcher_CommandCircleCenterRadius.h \
            Sketcher_CommandCircleP2Tan.h \
            Sketcher_CommandLine2P.h \
            Sketcher_CommandPoint.h \
            Sketcher_CommandTrim.h \
            Sketcher_GUI.h \
            Sketcher_Object.h \
            Sketcher_ObjectGeometryType.h \
            Sketcher_ObjectType.h \
            Sketcher_ObjectTypeOfMethod.h \
            Sketcher_QtGUI.h \
            Sketcher_Snap.h \
            Sketcher_SnapCenter.h \
            Sketcher_SnapEnd.h \
            Sketcher_SnapIntersection.h \
            Sketcher_SnapLine.h \
            Sketcher_SnapLineParallel.h \
            Sketcher_SnapLinePerpendicular.h \
            Sketcher_SnapMiddle.h \
            Sketcher_SnapNearest.h \
            Sketcher_SnapTangent.h \
            Sketcher_SnapType.h \

FORMS += \
        mainwindow.ui


#INCLUDEPATH += H:/contact/6.refer_project/OcctQtWidget/OcctQtLib/libdxfrw \
#               H:/contact/6.refer_project/hal-core-1.26/src/hal/components/matrix/cpp_interface/libdxfrw \
#                "C:/Program Files (x86)/Eigen3/include" \
#                "H:/vcpkg/installed/x64-windows/include/boost" \
#                D:/app/Cygwin/usr/include

# Opencascade
INCLUDEPATH += D:/app/OpenCASCADE-7.7.0-vc14-64/opencascade-7.7.0/inc \
               D:/app/OpenCASCADE-7.7.0-vc14-64/opencascade-7.7.0/src
LIBS+= -LD:/app/OpenCASCADE-7.7.0-vc14-64/opencascade-7.7.0/win64/vc14/lib
#       -L/opt/opencascade/oce-upstream-V7_5_0beta/lin/gcc/libd


LIBS += -lTKGeomAlgo -lTKMesh -lTKHLR -lTKBO -lTKShHealing
LIBS += -lTKPrim
LIBS += -lTKernel -lTKMath -lTKTopAlgo -lTKService
LIBS += -lTKG2d -lTKG3d -lTKV3d -lTKOpenGl
LIBS += -lTKBRep -lTKXSBase -lTKGeomBase
LIBS += -lTKXSDRAW
LIBS += -lTKLCAF -lTKXCAF -lTKCAF -lTKVCAF
LIBS += -lTKCDF -lTKBin -lTKBinL -lTKBinXCAF -lTKXml -lTKXmlL -lTKXmlXCAF
# -- IGES support
LIBS += -lTKIGES
# -- STEP support
LIBS += -lTKSTEP -lTKXDESTEP -lTKXDEIGES -lTKSTEPAttr -lTKSTEPBase -lTKSTEP209
# -- STL support
LIBS += -lTKSTL
# -- OBJ/glTF support
LIBS += -lTKRWMesh -lTKMeshVS
# -- VRML support
LIBS += -lTKVRML
# -- ViewerTest
LIBS += -lTKViewerTest

DISTFILES += \
    libdxfrw/main.txt \

