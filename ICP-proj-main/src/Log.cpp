#include <iostream>
#include <fstream>
#include <string>
#include "headers/Field.hpp"
#include "headers/Maze.hpp"
#include <QDir>
#include "Log.h"
#include <iostream>
#include <fstream>
#include <QDebug>

Log::Log(Maze * maze, int rowsLog, int colsLog, QTimer *timerLog){
    m_maze = maze;
    m_rows = rowsLog;
    m_cols = colsLog;
    QTimer *m_timer = timerLog;
    if(m_timer != nullptr){
    connect(m_timer, SIGNAL(timeout()), this, SLOT(createLog()));
    }
}

void Log::clearLogFolder()
{
    QDir logFolder("data/log");
    if (logFolder.exists()) {
        QFileInfoList logFiles = logFolder.entryInfoList(QDir::Files);
        for (const QFileInfo& logFile : logFiles) {
            QFile::remove(logFile.absoluteFilePath());
        }
    }
}

void Log::createLog() {
    try {
        std::string logFolderPath = "data/log";
        std::string logFilePath = logFolderPath + "/" + std::to_string(logIteration) + ".txt";

        std::ofstream logFile(logFilePath);
        if (!logFile.is_open()) {
            throw std::runtime_error("Failed to create log file");
        }

        // Write "m_rows m_cols" on the first line
        logFile << m_rows << " " << m_cols << std::endl;

        for (int rows = 1; rows <= m_rows; rows++) {
            for (int cols = 1; cols <= m_cols; cols++) {
                Field *field = m_maze->getField(rows, cols);
                if (field->ghost != nullptr) {
                    logFile << "G";
                } else if (field->pacman != nullptr) {
                    logFile << "S";
                } else if (field->target != nullptr) {
                    logFile << "T";
                } else if (field->key != nullptr) {
                    logFile << "K";
                } else if (field->move) {
                    logFile << ".";
                } else {
                    logFile << "X";
                }
            }
            logFile << std::endl;
        }
        logFile << std::endl;
        logIteration++;
        logFile.close();
    } catch (const std::exception& e) {
        std::cerr << "Error creating log: " << e.what() << std::endl;
    }
}

void Log::readSourceLog(int iteration){
    int rows;
    int cols;
        std::string filename = "data/log/" + std::to_string(iteration) + ".txt";
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
        }

    if (file.is_open()){
        std::string str_rows;
        file >> str_rows;
        rows = stoi(str_rows);
        std::string str_cols;
        file >> str_cols;
        cols = stoi(str_cols);

        std::string inputstring;

        m_maze->startReading(rows, cols);

        while (file.good()){
            file >> inputstring;
            if (int(inputstring.length()) != cols){
                qDebug() << "wrong input";
            }
            m_maze->processLine(inputstring);
        }
    }
    else{
        qDebug() << "couldnt read map\n";
    }
}

int Log::countLogs() {
    QDir logFolder("data/log");
    if (logFolder.exists()) {
        QFileInfoList logFiles = logFolder.entryInfoList(QDir::Files);
        return logFiles.count();
    } else {
        return 0;
    }
}

