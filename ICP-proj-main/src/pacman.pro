QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    GridLog.cpp \
    Log.cpp \
    MazeButton.cpp \
    classes/Field.cpp \
    classes/Maze.cpp \
    classes/MazeObject.cpp \
    ghost.cpp \
    grid.cpp \
    main.cpp \
    mainMenu.cpp \
    pacman.cpp\


HEADERS += \
    GridLog.h \
    Log.h \
    MazeButton.h \
    ghost.h \
    grid.h \
    headers/Field.hpp \
    headers/Maze.hpp \
    headers/MazeObject.hpp \
    mainMenu.h \
    pacman.h



FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
