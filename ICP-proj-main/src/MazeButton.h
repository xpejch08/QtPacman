/**
 * @author xpejch08 Štěpán Pejchar
 * @file MazeButton.h
 * @brief This file contains the declaration of the MazeButton class, which represents a button for controlling the logging of the game.
 */

#ifndef MAZEBUTTON_H
#define MAZEBUTTON_H

#include "qmainwindow.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QKeyEvent>
#include <QObject>
#include <headers/MazeObject.hpp>
#include <QTimer>
#include <QGraphicsScene>
#include <QPushButton>
#include <QFile>
#include <iostream>
#include <fstream>
#include <QGraphicsView>
#include "Log.h"

/**
 * @class MazeButton
 * @brief This class represents a button for controlling logs.
 */
class MazeButton :public QObject{
    Q_OBJECT
public:

    QPushButton *logForwardButton; /**< The button to move the log forward. */
    QPushButton *logBackwardsButton; /**< The button to move the log backwards. */
    QGraphicsScene *mainScene; /**< The main scene. */
    QGraphicsView *mainView; /**< The main view. */
    QGraphicsScene *logScene; /**< The log scene. */
    QGraphicsView *gameView; /**< The game view. */
    QTimer * slotTimer; /**< The timer for the slots. */
    QMainWindow *windowMaze; /**< The main window for the maze game. */
    QMainWindow *windowLog; /**< The main window for the log. */

    QTimer m_timer; /**< The timer for the game. */

    Log *m_log; /**< The log object. */

    bool forwardLog = true; /**< A boolean indicating whether the log is moving forward or backwards */

    int positionx; /**< The x position. */
    int positiony; /**< The y position. */
    bool isPressed = false; /**< A boolean indicating whether the button is pressed or not. */

    /**
     * @brief Gets the status of the button.
     * @return A boolean indicating whether the button is pressed or not.
     */
    bool getPressed();


    /**
     * @brief Constructor for the MazeButton class.
     * @param scene The main scene.
     * @param logScene The log scene.
     * @param xPos The x position.
     * @param yPos The y position.
     * @param w The main window for the maze game.
     * @param newWindow The main window for the log.
     * @param log The log object.
     */
    MazeButton(QGraphicsScene *scene, QGraphicsScene * logScene, int xPos, int yPos, QMainWindow *w, QMainWindow *newWindow, Log *log);

    /**
     * @brief Starts the menu.
     */
    void startMenu();

public slots:
    /**
     * @brief Handles the button clicked logging forwards signal.
     */
    void buttonClicked();

    /**
     * @brief Handles the logging backwards button clicked signal.
     */
    void backwardsButtonClicked();

    /**
     * @brief Plays the log.
     */
    void playLog();

private:
    std::ifstream file; /**< The file stream for reading maze/log. */
};

#endif
