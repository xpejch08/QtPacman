/**
 * @author xpejch08 Štěpán Pejchar
 * @file pacman.h
 * @brief Header file for the pacman Class, used for implementing the view of the pacman.
 */
#ifndef PACMAN_H
#define PACMAN_H

#include <QGraphicsItem>
#include <QPainter>
#include <QKeyEvent>
#include <QObject>
#include <headers/MazeObject.hpp>
#include <QTimer>
#include <QMainWindow>
#include <QLabel>

/**
 * @brief The Pacman class represents the view of the main character of the game.
 *
 * This class inherits from QObject and QGraphicsItem. It contains handling
 * key events that correspond to movement. It also contains references to other
 * game objects, such as the maze and the end scene.
 */
class Pacman :public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    MazeObject *pacmanMove;
    Maze * m_maze;
    QTimer *m_timer;
    QGraphicsScene *m_endScene;
    QMainWindow *m_endWindow;
    QLabel *endLabelLoose;
    QLabel *endLabelWin;

    /**
     * @brief Constructs a new Pacman object.
     *
     * @param pacman The Pacman's MazeObject.
     * @param maze The game maze.
     * @param mainTimer The main game timer.
     * @param endScene The game over scene.
     * @param endWindow The game over window.
     * @param parent The parent object.
     */
    Pacman(MazeObject *pacman, Maze *maze, QTimer *mainTimer, QGraphicsScene *endScene, QMainWindow *endWindow,  QGraphicsItem *parent = nullptr);

    QWidget *m_parentWidget;
    int quitNext = 0;
    int rows = 0;
    int cols = 0;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    /**
     * @brief Handles key press events.
     * @param event The key event.
     */
    void keyPressEvent(QKeyEvent *event) override;
public slots:

    /**
     * @brief Moves the Pacman object.
     */
    void move();

private:
    enum class Dir {
        Up,
        Down,
        Left,
        Right,
    };

    /**
     * @brief Paints the Pacman's image on the screen.
     *
     * @param pacman The Pacman's MazeObject.
     */
    void paintPacman(MazeObject *pacman);

    const int m_step = 50;
    Direction lastDir = Direction::None;
protected:

};

#endif // PACMAN_H
