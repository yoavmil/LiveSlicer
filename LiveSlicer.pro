#-------------------------------------------------
#
# Project created by QtCreator 2014-12-24T22:00:00
#
#-------------------------------------------------

QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LiveSlicer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mesh/meshloader.cpp \
    common/logger.cpp \
    gui/taskgui.cpp \
    common/task.cpp \
    gui/tasksmanager.cpp \
    gui3d/viewer3d.cpp \
    mesh/mesh.cpp \
    mesh/facet.cpp \
    mesh/sharedvertex.cpp \
    gui3d/viewitem.cpp \
    gui3d/viewsimplemesh.cpp \
    gui3d/viewerprovider.cpp \
    gui3d/viewworld.cpp \
    common/aabb3d.cpp \
    gui3d/trackball.cpp

HEADERS  += mainwindow.h \
    mesh/meshloader.h \
    common/logger.h \
    gui/taskgui.h \
    common/task.h \
    gui/tasksmanager.h \
    gui3d/viewer3d.h \
    mesh/mesh.h \
    mesh/facet.h \
    mesh/sharedvertex.h \
    common/exceptions.h \
    gui3d/viewerprovider.h \
    gui3d/viewitem.h \
    gui3d/viewsimplemesh.h \
    common/common.h \
    gui3d/viewworld.h \
    common/aabb3d.h \
    gui3d/trackball.h

FORMS    += mainwindow.ui \
    gui/taskgui.ui

DISTFILES +=

INCLUDEPATH += common
INCLUDEPATH += mesh
INCLUDEPATH += gui gui3d

CONFIG += c++11

RESOURCES += \
    resources.qrc
