QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gui/AddWordScreen.cpp \
    gui/DeleteScreen.cpp \
    gui/SearchScreen.cpp \
    gui/ViewDictionaryScreen.cpp \
    gui/menu.cpp \
    main.cpp \
    mainwindow.cpp \
    Backend/Search.cpp \
    Backend/trie.cpp \
    Backend/trie_node.cpp \
    Backend/Validator.cpp

HEADERS += \
    MainWindow.h \
    gui/AddWordScreen.h \
    gui/DeleteScreen.h \
    gui/SearchScreen.h \
    gui/ViewDictionaryScreen.h \
    gui/menu.h \
    mainwindow. \
    Backend/Search.h \
    Backend/trie.h \
    Backend/trie_node.h \
    Backend/Validator.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
