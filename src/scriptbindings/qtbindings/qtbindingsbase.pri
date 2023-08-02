TEMPLATE = lib
DEPENDPATH += .
INCLUDEPATH += .

macx:DESTDIR = ../../../../Candle.app/Contents/MacOS/script
else:DESTDIR = ../../../../bin/script

#win32:{
#    QMAKE_CXXFLAGS += /MP /GS /Zi
#    QMAKE_LFLAGS += /DEBUG /OPT:REF /OPT:ICF
#}

QT += script
CONFIG += plugin
GENERATEDCPP = $$PWD/../generated_cpp
TARGET=$$qtLibraryTarget($$TARGET)
