QT       += core gui bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    com_frame.cpp \
    main.cpp \
    corewidget.cpp \
    src/bt_com_if.cpp \
    src/frameconverter.cpp \
    src/graphics/btcontrolwidget.cpp \
    src/graphics/logterminal.cpp

HEADERS += \
    com_frame.h \
    corewidget.h \
    src/bt_com_if.h \
    src/frameconverter.h \
    src/graphics/logterminal.h \
    src/graphics/btcontrolwidget.h

FORMS += \
    corewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ANDROID_ABIS = armeabi-v7a
