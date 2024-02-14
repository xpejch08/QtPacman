#include <QTime>
#include <QApplication>
#include <QGraphicsScene>
#include <headers/MazeObject.hpp>
#include <headers/Field.hpp>
#include <QDebug>
#include <QTimer>
#include <QPushButton>
#include <QObject>
#include "pacman.h"
#include "ghost.h"
#include "headers/Maze.hpp"
#include "mainMenu.h"
#include <QDebug>
#include <QPushButton>
#include <QFile>
#include "Log.h"
#include "GridLog.h"
#include "MazeButton.h"
#include "qmainwindow.h"



MazeButton::MazeButton(QGraphicsScene *scene, QGraphicsScene *Logscene, int xPos, int yPos, QMainWindow *win, QMainWindow *newWindow, Log *mainLog)
{
    logForwardButton = new QPushButton("Log>>");
    logBackwardsButton = new QPushButton("Log<<");
    mainScene = scene;
    connect(logBackwardsButton, SIGNAL(clicked()), this, SLOT(backwardsButtonClicked()));
    connect(logForwardButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(playLog()));
    positionx = xPos;
    positiony = yPos;
    windowMaze = win;
    windowLog = newWindow;
    logScene = Logscene;
    m_log = mainLog;

}

void MazeButton::startMenu(){

    logForwardButton->setGeometry(positionx, positiony, 150, 50);
    logBackwardsButton->setGeometry(positionx, positiony + 70, 150, 50);
    mainScene->addWidget(logForwardButton);
    mainScene->addWidget(logBackwardsButton);
}

void MazeButton::buttonClicked(){
    windowMaze->close();
    m_timer.start(1000);
    windowLog->show();
}

void MazeButton::backwardsButtonClicked(){
    windowMaze->close();
    m_timer.start(1000);
    forwardLog = false;
    m_log->logIteration = m_log->countLogs();
    windowLog->show();
}

void MazeButton::playLog(){
    logScene->clear();
    if(forwardLog){
        if(m_log->readingLogFromStart == m_log->countLogs()){
            m_timer.stop();
        }
        m_log->readSourceLog(m_log->readingLogFromStart);
        GridLog *gridLog = new GridLog(m_log->m_maze);
        logScene->addItem(gridLog);
        m_log->readingLogFromStart++;
    }
    else{
    if(m_log->logIteration == 0){
        m_timer.stop();
    }
        m_log->readSourceLog(m_log->logIteration);
        GridLog *gridLog = new GridLog(m_log->m_maze);
        logScene->addItem(gridLog);
        m_log->logIteration--;
    }
}

bool MazeButton::getPressed(){
    return isPressed;
}
