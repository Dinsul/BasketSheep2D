TEMPLATE = app
CONFIG -= console
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    info.h \
    units/unit.h \
    game.h \
    options.h \
    units/mobileunit.h \
    randomnix.h \
    menu.h

SOURCES += main.cpp \
    units/unit.cpp \
    game.cpp \
    options.cpp \
    units/mobileunit.cpp \
    controlhandler.cpp \
    randomnix.cpp \
    menu.cpp

include(deployment.pri)
qtcAddDeployment()


unix:!macx: LIBS += -L/usr/lib/x86_64-linux-gnu/ \
    -lsfml-audio  \
    -lsfml-system \
    -lsfml-window \
    -lsfml-graphics \
    -ltinyxml


mac: LIBS += -F/Library/Frameworks/ \
    -framework sfml-graphics \
    -framework sfml-system \
    -framework sfml-window \
    -framework SFML

INCLUDEPATH += /usr/local/include/
DEPENDPATH  += /usr/local/include/

mac: LIBS += -L/usr/local/Cellar/tinyxml/2.6.2/lib -ltinyxml

INCLUDEPATH += /usr/local/Cellar/tinyxml2/2.6.2/include
DEPENDPATH  += /usr/local/Cellar/tinyxml2/2.6.2/include
