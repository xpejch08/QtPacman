/**
 * @author xpejch08 Štěpán Pejchar
 * @file mainMenu.h
 * @brief Header file for the mainMenu class implementing the main menu view.
 */
#ifndef MAINMENU_H
#define MAINMENU_H

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
#include <QLabel>
#include <QGraphicsProxyWidget>

/**
 * @class mainMenu
 * @brief This class represents the main menu of the Pac-Man game.
 * 
 * The main menu displays the start button and the current number of lives and steps taken by the player.
 */
class mainMenu : public QObject {
    Q_OBJECT

public:

    bool clickedOnce = false; /**< A boolean flag indicating if the start button has been clicked. */
    QPushButton *startGameButton; /**< A QPushButton representing the start button. */
    QGraphicsScene *mainScene; /**< A QGraphicsScene representing the main menu scene. */
    QGraphicsView *mainView; /**< A QGraphicsView representing the main menu view. */
    QGraphicsScene *gameScene; /**< A QGraphicsScene representing the game scene. */
    QGraphicsView *gameView; /**< A QGraphicsView representing the game view. */
    QTimer * slotTimer; /**< A QTimer for updating the scene. */
    Log * m_log; /**< A pointer to a Log object for logging game events. */
    QLabel *livesLabel; /**< A QLabel for displaying the current number of lives. */
    QLabel *stepsLabel; /**< A QLabel for displaying the current number of steps taken. */
    MazeObject *pacmanForLives; /**< A pointer to a MazeObject representing the Pac-Man object*/
    QGraphicsProxyWidget* proxyWidget; /**< A pointer to a QGraphicsProxyWidget for displaying the current number of steps taken. */

    int currentLives; /**< An integer representing the current number of lives. */
    int previousLives = 3; /**< An integer representing the previous number of lives starting with 3. */

    int positionx; /**< An integer representing the x-coordinate of the main menu. */
    int positiony; /**< An integer representing the y-coordinate of the main menu. */
    bool isPressed = false; /**< A boolean flag indicating if the start button has been pressed. */

    bool getPressed(); /**< Returns true if the start button has been pressed. */

    /**
     * @brief Constructs a mainMenu object.
     * @param scene A pointer to a QGraphicsScene representing the main menu scene.
     * @param timer A pointer to a QTimer for updating the scene.
     * @param xPos An integer representing the x-coordinate of the main menu.
     * @param yPos An integer representing the y-coordinate of the main menu.
     * @param pacman A pointer to a MazeObject representing the Pac-Man object.
     */
    mainMenu(QGraphicsScene *scene, QTimer *timer, int xPos, int yPos, MazeObject * pacman);

    /**
     * @brief Displays the main menu.
     */
    void startMenu();

public slots:
    /**
     * @brief A slot for handling the start button click event.
     */
    void buttonClicked();

    /**
     * @brief A slot for updating the scene labels .
     */
    void interactivesUpdate();

private:

    std::ifstream file; /**< Used for reading the maze/log */
};

#endif