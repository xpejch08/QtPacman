#include <QTime>
#include <QApplication>
#include <QGraphicsScene>
#include <headers/MazeObject.hpp>
#include <headers/Field.hpp>
#include <QDebug>
#include <QTimer>
#include "mainMenu.h"
#include <QPushButton>
#include <QGraphicsScene>
#include <QObject>
#include "grid.h"
#include "pacman.h"
#include "ghost.h"
#include "headers/Maze.hpp"
#include <QDebug>
#include <QPushButton>
#include <QFile>
#include "Log.h"
#include <QLabel>
#include <QTimer>
#include <QWidget>
#include <QGraphicsProxyWidget>

mainMenu::mainMenu(QGraphicsScene *scene, QTimer *timer, int xPos, int yPos, MazeObject *pacman)
{
    startGameButton = new QPushButton("Startin");
    mainScene = scene;
    QTimer *m_timer = timer;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(interactivesUpdate()));
    connect(startGameButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    slotTimer = timer;
    positionx = xPos;
    positiony = yPos;
    pacmanForLives = pacman;
    livesLabel = new QLabel("Lives: " + QString::number(pacmanForLives->get_lives()));
    stepsLabel = new QLabel("Steps: " + QString::number(pacmanForLives->get_steps()));


}


void mainMenu::startMenu(){
    startGameButton->setGeometry(positionx, positiony, 150, 50);
    mainScene->addWidget(startGameButton);
    livesLabel->setFixedSize(100, 30);
    livesLabel->move(startGameButton->pos() + QPoint(startGameButton->width()-150, +200));
    proxyWidget =  mainScene->addWidget(livesLabel);
    stepsLabel->setFixedSize(100, 30);
    stepsLabel->move(startGameButton->pos() + QPoint(startGameButton->width()-150, +250));
    proxyWidget =  mainScene->addWidget(stepsLabel);
}

void mainMenu::interactivesUpdate(){
    currentLives = pacmanForLives->get_lives();
    if (currentLives != previousLives) {
    previousLives = currentLives;
    livesLabel->setText("Lives: " + QString::number(currentLives));
    }
    stepsLabel->setText("Steps: " + QString::number(pacmanForLives->get_steps()));

}

void mainMenu::buttonClicked(){
    if(!clickedOnce){
        clickedOnce = true;
        m_log->clearLogFolder();
    }

    slotTimer->start(500);
}

bool mainMenu::getPressed(){
    return isPressed;
}
