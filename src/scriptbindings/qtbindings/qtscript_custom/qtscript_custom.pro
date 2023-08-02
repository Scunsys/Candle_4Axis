TARGET = qtscript_custom
include(../qtbindingsbase.pri)
QT += widgets gui
SOURCES += plugin.cpp
HEADERS += plugin.h
INCLUDEPATH += ./include/ $$PWD/../../../designerplugins/customwidgetsplugin

macx {
    CWLIBDIR = ../../../../Candle.app/Contents/MacOS
    CWLIB = libcustomwidgets.dylib

    rpath_fix.target = rpath_fix
    rpath_fix.commands = install_name_tool -change $$CWLIB @executable_path/$$CWLIB $<
    rpath_fix.depends = $(DESTDIR)$(TARGET)

    phony.target = .PHONY
    phony.depends = rpath_fix

    all.target = first
    all.depends = rpath_fix

    QMAKE_EXTRA_TARGETS += rpath_fix phony all
} else {
    CWLIBDIR = ../../../../bin
}

LIBS += -L$$CWLIBDIR -lcustomwidgets
include($$GENERATEDCPP/com_trolltech_qt_custom/com_trolltech_qt_custom.pri)
