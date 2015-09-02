TEMPLATE = lib
CONFIG += plugin
QT -= gui
QT += core qml

TARGET = $$qtLibraryTarget(samba_core)

DESTPATH = /qml/SAMBA

SOURCES += sambacore.cpp
HEADERS += sambacore.h

# include/link sambacommon library
INCLUDEPATH += $$PWD/../../sambacommon
DEPENDPATH += $$PWD/../../sambacommon
win32:CONFIG(release, debug|release):LIBS += -L$$OUT_PWD/../../sambacommon/release/ -lsambacommon3
else:win32:CONFIG(debug, debug|release):LIBS += -L$$OUT_PWD/../../sambacommon/debug/ -lsambacommon3
else:unix:LIBS += -L$$OUT_PWD/../../sambacommon/ -lsambacommon

# set RPATH on Linux
unix:!mac:{
    QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN/../../lib\''
    QMAKE_RPATH =
}

qml.files = qmldir \
	Applet.qml \
	AppletCommType.qml \
	AppletKind.qml \
	AppletLoader.qml \
	AppletStatus.qml \
	Connection.qml \
	Device.qml

# install
target.path = $$DESTPATH
qml.path = $$DESTPATH
INSTALLS += target qml

OTHER_FILES += $$qml.files
