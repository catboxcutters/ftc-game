#ifndef ROBOT_SIMULATION_H
#define ROBOT_SIMULATION_H

#include <vector>
#include <string>

class Robot;
class Field;

class Robot {
private:
    int row, col;
    char direction;  // 'N', 'E', 'S', 'W'
    Field* field;
    char currentCell; 

public:
    Robot(int r, int c, char dir, Field* f);
    void moveForward();
    void turnLeft();
    void turnRight();
    int distanceToObstacle();
    bool collectObjective();
    bool reachedGoal();
    void getPosition(int& r, int& c) const;
    bool isObjectiveNearby(int radius);
    int getCollectiblesCount();
};

class Field {
private:
    std::vector<std::vector<char>> grid;
    int rows, cols;
    Robot* robot;

public:
    Field(int r, int c);
    void display() const;
    void setCell(int r, int c, char value);
    char getCell(int r, int c) const;
    void setRobot(Robot* r);
    Robot* getRobot() const;
    int getRows() const;
    int getCols() const;
};

void saveFieldToString(const Field& field, std::string& output);

extern int collected;

#endif // ROBOT_SIMULATION_H#pragma once
