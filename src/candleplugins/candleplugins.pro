TEMPLATE = subdirs

TRANSLATIONS =  camera/translation_ru.ts \
                usercommands/translation_ru.ts \
                coordinatesystem/translation_ru.ts \
                emergencybutton/translation_ru.ts

macx:DESTDIR = ../../Candle.app/Contents/MacOS/plugins
else:DESTDIR = ../../bin/plugins

copy_plugins.target = copy_plugins
copy_plugins.commands = \
    $(QINSTALL) $$PWD/camera $$DESTDIR/camera && \
    $(QINSTALL) $$PWD/usercommands $$DESTDIR/usercommands && \
    $(QINSTALL) $$PWD/coordinatesystem $$DESTDIR/coordinatesystem && \
    $(QINSTALL) $$PWD/emergencybutton $$DESTDIR/emergencybutton

phony.target = .PHONY
phony.depends = copy_plugins

all.target = first
all.depends = copy_plugins

QMAKE_EXTRA_TARGETS += copy_plugins phony all
