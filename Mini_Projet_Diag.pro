QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
LIBS   += -lws2_32


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    can.cpp \
    datagramsocketclient.cpp \
    main.cpp \
    mainwindow.cpp \
    mux.cpp \
    tcpsocketclient.cpp

HEADERS += \
    can.h \
    canframe.h \
    datagramsocketclient.h \
    mainwindow.h \
    mux.h \
    refmux.h \
    tcpsocketclient.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/./ -lMuxDLL

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

DISTFILES += \
    //0801327h-ad/rakotoarimanana$/profiles/Téléchargements/cliggOff.png \
    //0801327h-ad/rakotoarimanana$/profiles/Téléchargements/cliggOn.png \
    MuxDLL.dll \
    MuxDLL.lib

RESOURCES += \
    resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../release/ -lMuxDLL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../debug/ -lMuxDLL

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
