TEMPLATE = app
TARGET   = QDrink
CONFIG	+= c++11
CONFIG  -= app_bundle
CONFIG  += qt

QT		+= xml core gui


SOURCES += main.cpp \
    model/ingridiente.cpp \
    model/base.cpp \
    model/aromatizzante.cpp \
    model/colorante.cpp \
    model/drink.cpp \
    model/cocktail.cpp \
    model/ricettario.cpp \
    view/mainwindow.cpp \
    view/cocktaildialog.cpp \
    view/ricettariodialog.cpp


HEADERS += \
    model/ingridiente.h \
    model/base.h \
    model/aromatizzante.h \
    model/colorante.h \
    model/drink.h \
    model/cocktail.h \
    model/ricettario.h \
    model/clist.h \
    view/mainwindow.h \
    view/cocktaildialog.h \
    view/ricettariodialog.h

FORMS += \
    forms/mainwindow.ui \   
    forms/cocktaildialog.ui \
    forms/ricettariodialog.ui

RESOURCES += \
    resources/icons.qrc



