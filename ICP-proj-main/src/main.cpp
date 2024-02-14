#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>
#include <iostream>
#include <fstream>
#include "grid.h"
#include "pacman.h"
#include "ghost.h"
#include "headers/Maze.hpp"
#include "mainMenu.h"
#include <QDebug>
#include <QPushButton>
#include "MazeButton.h"
#include <QFile>
#include <QMainWindow>
#include "Log.h"



int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    QMainWindow window;
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    window.setCentralWidget(&view);

    QMainWindow window2;
    QGraphicsScene scene2;
    QGraphicsView view2(&scene2);
    window2.setCentralWidget(&view2);

    QMainWindow endWindow;;
    QGraphicsScene endScene;
    QGraphicsView endView(&endScene);
    endWindow.setCentralWidget(&endView);

    //opening new maze, we can add a switch that picks specific maze depending on the players choice
    /**
     * @brief Reading Maze 1
     */
    std::ifstream file;
    Maze *mazeFile = new Maze();

    file.open("save/map.txt");
    qDebug() << "Error opening file: " << file.rdstate();
    int rows;
    int cols;

    if (file.is_open()){
        std::string str_rows;
        file >> str_rows;
        rows = stoi(str_rows);
        std::string str_cols;
        file >> str_cols;
        cols = stoi(str_cols);

        std::string inputstring;

        mazeFile->startReading(rows, cols);

        while (file.good()){
            file >> inputstring;
            if (int(inputstring.length()) != cols){
                qDebug() << "wrong input";
                return 1;
            }
            mazeFile->processLine(inputstring);
        }
    }
    else{
        qDebug() << "couldnt read map\n";
        return 1;
    }

    QTimer commonTimer;
    commonTimer.stop();


    //initializing maze
    mazeFile->stopReading();
    Maze maze = mazeFile->createMaze();

    //getting starting point of pacman
    MazeObject *pacmanTmp = nullptr;
    MazeObject *iterator = nullptr;
    MazeObject *ghost1 = nullptr;
    MazeObject *ghost2 = nullptr;
    MazeObject *ghost3 = nullptr;
    MazeObject *ghost4 = nullptr;
    int ghostCounter = 0;
    int setPosR = 0;
    int setPosC = 0;
    int ghost1PosR = 0;
    int ghost1PosC = 0;
    int ghost2PosR = 0;
    int ghost2PosC = 0;
    int ghost3PosR = 0;
    int ghost3PosC = 0;
    int ghost4PosR = 0;
    int ghost4PosC = 0;
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            if((iterator = maze.getField(r,c)->get())){
                if(iterator->isPacman() == true){
                    pacmanTmp = iterator;
                    setPosR = r;
                    setPosC = c;
                    break;
                }
                if(iterator->isGhost() == true){
                    ghostCounter++;
                    if(ghostCounter == 1){
                        ghost1 = iterator;
                        ghost1PosR = r;
                        ghost1PosC = c;
                    }
                    else if(ghostCounter == 2){
                        ghost2 = iterator;
                        ghost2PosR = r;
                        ghost2PosC = c;
                    }
                    else if(ghostCounter == 3){
                        ghost3 = iterator;
                        ghost3PosR = r;
                        ghost3PosC = c;
                    }
                    else if(ghostCounter == 4){
                        ghost4 = iterator;
                        ghost4PosR = r;
                        ghost4PosC = c;
                    }
                }
            }
        }
    }

    scene.setSceneRect(-50, -50, (rows+2)*50+200, (cols+2)*50);
    scene2.setSceneRect(-50, -50, (rows+2)*50+200, (cols+2)*50);




    mainMenu *menu = new mainMenu(&scene, &commonTimer, (rows+2)*50-20, 25, pacmanTmp);
    menu->startMenu();

    Log *log = new Log(&maze, rows, cols, &commonTimer);

    MazeButton *mazeButton = new MazeButton(&scene, &scene2, (rows+2)*50-20, 100, &window, &window2, log);
    mazeButton->startMenu();

    Grid grid(&maze);
    scene.addItem(&grid);


    Ghost ghostClass1(ghost1, &maze, &commonTimer, 1);
    ghostClass1.setPos((ghost1PosC * 50) - 50, (ghost1PosR * 50) - 50);
    scene.addItem(&ghostClass1);

    Ghost ghostClass2(ghost2, &maze, &commonTimer, 2);
    ghostClass2.setPos((ghost2PosC * 50) - 50, (ghost2PosR * 50) - 50);
    scene.addItem(&ghostClass2);

    Ghost ghostClass3(ghost3, &maze, &commonTimer, 3);
    ghostClass3.setPos((ghost3PosC * 50) - 50, (ghost3PosR * 50) - 50);
    scene.addItem(&ghostClass3);

    Ghost ghostClass4(ghost4, &maze, &commonTimer, 4);
    ghostClass4.setPos((ghost4PosC * 50) - 50, (ghost4PosR * 50) - 50);
    scene.addItem(&ghostClass4);

    Pacman pacman(pacmanTmp, &maze, &commonTimer, &endScene, &endWindow);
    pacman.setPos((setPosC * 50) - 50, (setPosR * 50) - 50);
    scene.addItem(&pacman);


    window.show();

    /**
     * Maze 2
     **/


    return a.exec();
}
