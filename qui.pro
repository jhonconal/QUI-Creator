#-------------------------------------------------
#
# Project created by QtCreator 2017-02-19T12:55:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET          = qui
TEMPLATE        = app
MOC_DIR         = temp/moc
RCC_DIR         = temp/rcc
UI_DIR          = temp/ui
OBJECTS_DIR     = temp/obj
DESTDIR         = bin
win32:RC_FILE   = other/main.rc
PRECOMPILED_HEADER  = head.h

INCLUDEPATH     += $$PWD
INCLUDEPATH     += $$PWD/form
INCLUDEPATH     += $$PWD/demo
CONFIG          += qt warn_off release
DEFINES         += demo1

SOURCES += main.cpp\    
    form/quiwidget.cpp \
    form/quicreator.cpp \
    form/highlighter.cpp \
    form/panelwidget.cpp \
    form/frmdevice.cpp \
    demo/appinit.cpp \
    demo/uidemo1.cpp \
    demo/uidemo2.cpp \
    demo/uidemo3.cpp \
    demo/uidemo4.cpp

HEADERS  += head.h\
    form/quiwidget.h \
    form/quicreator.h \
    form/highlighter.h \
    form/panelwidget.h \
    form/frmdevice.h \
    demo/appinit.h \
    demo/uidemo1.h \
    demo/uidemo2.h \
    demo/uidemo3.h \
    demo/uidemo4.h

FORMS    += \
    form/quicreator.ui \
    form/frmdevice.ui \
    demo/uidemo1.ui \
    demo/uidemo2.ui \
    demo/uidemo3.ui \
    demo/uidemo4.ui

RESOURCES += \
    other/qss.qrc \
    other/main.qrc \
    demo/demo.qrc
