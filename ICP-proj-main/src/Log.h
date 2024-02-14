/**
 * @author xpejch08 Štěpán Pejchar
 * @file Log.h
 * @brief Header file for the Log class, used for loggindg the Pac-Man game.
 */
#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QTime>
#include <QTimer>
#include <chrono>
#include "headers/MazeObject.hpp"
#include "headers/Maze.hpp"


/**
 * @brief The Log class is responsible for creating log files for a Pacman game.
 */
class Log : public QObject
{
    Q_OBJECT
public:
    int logIteration = 1; /**< The current log iteration. */

    int readingLogFromStart = 1; /**Used for iterating, when the logs play from the beginning*/

    /**
     * @brief A timer for creating log files.
     */
    QTimer timeline;

    /**
     * @brief The maze to log.
     */
    Maze* m_maze;

    Maze* mazeLog; /**< The maze object to log. */

    /**
     * @brief The number of rows in the maze.
     */
    int m_rows;

    /**
     * @brief The number of columns in the maze.
     */
    int m_cols;

    /**
     * @brief Clears the log folder.
     */
    void clearLogFolder();

    /**
     * @brief Reads a source log for a specified iteration.
     *
     * @param iteration the iteration number of the log to read
     */
    void readSourceLog(int iteration);

    /**
     * @brief Counts the number of logs in the log folder.
     *
     * @return the number of logs in the log folder
     */
    int countLogs();

    /**
     * @brief Creates a new Log object with the specified maze, number of rows, and number of columns.
     *
     * @param maze the maze to log
     * @param rows the number of rows in the maze
     * @param cols the number of columns in the maze
     * @param timer the timer to control the creation of log files
     */
    Log(Maze* maze, int rows, int cols, QTimer *timer);

public slots:
    /**
     * @brief Creates a log file for the current iteration.
     */
    void createLog();
};

#endif // LOG_H
