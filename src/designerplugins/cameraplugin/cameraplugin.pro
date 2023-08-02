CONFIG += plugin
TEMPLATE = lib
QT += widgets uiplugin multimedia multimediawidgets

macx:DESTDIR = ../../../Candle.app/Contents/MacOS/plugins/camera/plugins
else:DESTDIR = ../../../bin/plugins/camera/plugins

TARGET = cameraplugin

HEADERS +=  overlay.h \
            camerawidget.h \
            cameraplugin.h

SOURCES +=  overlay.cpp \
            camerawidget.cpp \
            cameraplugin.cpp
