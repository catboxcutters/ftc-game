#include "robot_simulation.h"
#include <iostream>
#include <sstream>

int collected = 0;

Robot::Robot(int r, int c, char dir, Field* f) : row(r), col(c), direction(dir), field(f) {
    currentCell = field->getCell(row, col);
    field->setCell(row, col, 'R');
    field->setRobot(this);
}

void Robot::moveForward() {
    field->setCell(row, col, currentCell);
    int newRow = row, newCol = col;
    switch (direction) {
    case 'N': if (row > 0) newRow--; break;
    case 'E': if (col < field->getCols() - 1) newCol++; break;
    case 'S': if (row < field->getRows() - 1) newRow++; break;
    case 'W': if (col > 0) newCol--; break;
    }
    if (field->getCell(newRow, newCol) != '#') {
        row = newRow;
        col = newCol;
        currentCell = field->getCell(row, col);
        field->setCell(row, col, 'R');
    }
}

void Robot::turnLeft() {
    switch (direction) {
    case 'N': direction = 'W'; break;
    case 'E': direction = 'N'; break;
    case 'S': direction = 'E'; break;
    case 'W': direction = 'S'; break;
    }
}

void Robot::turnRight() {
    switch (direction) {
    case 'N': direction = 'E'; break;
    case 'E': direction = 'S'; break;
    case 'S': direction = 'W'; break;
    case 'W': direction = 'N'; break;
    }
}

int Robot::distanceToObstacle() {
    int distance = 0;
    int r = row, c = col;
    while (true) {
        switch (direction) {
        case 'N': r--; break;
        case 'E': c++; break;
        case 'S': r++; break;
        case 'W': c--; break;
        }
        if (field->getCell(r, c) == '#' || field->getCell(r, c) == 'G') {
            return distance;
        }
        distance++;
    }
}
bool Robot::isObjectiveNearby(int radius) {
    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
            if (std::sqrt(i * i + j * j) <= radius) {
                if (field->getCell(row + i, col + j) == 'C') {
                    return true;
                }
            }
        }
    }
    return false;
}

int Robot::getCollectiblesCount() {
    int count = 0;
    for (int i = 0; i < field->getRows(); i++) {
        for (int j = 0; j < field->getCols(); j++) {
            if (field->getCell(i, j) == 'C') {
                count++;
            }
        }
    }
    return count;
}
bool Robot::collectObjective() {
    if (currentCell == 'C') {
        currentCell = '.';
        collected++;
        return true;
    }
    return false;
}

bool Robot::reachedGoal() {
    return currentCell == 'G';
}

void Robot::getPosition(int& r, int& c) const {
    r = row;
    c = col;
}

Field::Field(int r, int c) : rows(r), cols(c), robot(nullptr) {
    grid = std::vector<std::vector<char>>(rows, std::vector<char>(cols, '.'));
}

void Field::display() const {
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
}

void Field::setCell(int r, int c, char value) {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        grid[r][c] = value;
    }
}

char Field::getCell(int r, int c) const {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        return grid[r][c];
    }
    return '#';  
}

void Field::setRobot(Robot* r) { robot = r; }
Robot* Field::getRobot() const { return robot; }
int Field::getRows() const { return rows; }
int Field::getCols() const { return cols; }

void saveFieldToString(const Field& field, std::string& output) {
    std::stringstream ss;
    for (int r = 0; r < field.getRows(); ++r) {
        for (int c = 0; c < field.getCols(); ++c) {
            ss << field.getCell(r, c) << ' ';
        }
        ss << '\n';
    }
    output = ss.str();
}