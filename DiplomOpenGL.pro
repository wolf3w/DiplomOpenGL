#-------------------------------------------------
#
# Project created by QtCreator 2019-04-10T07:12:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -L/path/to/glew/lib -lGLEW -fopenmp

TARGET = DiplomOpenGL
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

CONFIG += c++17
QMAKE_CXXFLAGS += -O2 -fopenmp
QMAKE_LFLAGS += -fopenmp

SOURCES += \
    src/camera.cpp \
    src/datastorage.cpp \
    src/kgfequ.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/oglwidget.cpp \
    src/optionsdialog.cpp \
    src/shader.cpp

HEADERS += \
    headers/camera.h \
    headers/kgfequ.h \
    headers/mainwindow.h \
    headers/oglwidget.hpp \
    headers/optionsdialog.h \
    headers/shader.h \
    headers/datastorage.h

FORMS += \
    forms/mainwindow.ui \
    forms/optionsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    other/vshader.vert \
    other/fshader.frag
