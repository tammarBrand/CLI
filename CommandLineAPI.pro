QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../../gas_cam/GAS/Queu.c \
        ../gas_cam/Queu.c \
        HashTable.c \
        functions.c \
        main.c \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../gas_cam/Queue.h \
    HashTable.h \
    Queue.h \
    functions.h \
    gas_cam.h

DISTFILES += \
    CommandLineAPI.pro.user
