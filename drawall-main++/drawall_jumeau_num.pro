QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calculMath.cpp \
    chariot.cpp \
    configuration.cpp \
    gcode.cpp \
    graphique.cpp \
    ligne.cpp \
    main.cpp \
    motion_control.cpp \
    planner.cpp \
    point.cpp \
    vecteur.cpp \
    vitrine.cpp \
    widget.cpp

HEADERS += \
    calculMath.h \
    chariot.h \
    configuration.h \
    gcode.h \
    graphique.h \
    grbl.h \
    ligne.h \
    montion_control.h \
    planner.h \
    point.h \
    vecteur.h \
    vitrine.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    drawall_jumeau_num.pro.user
