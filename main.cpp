#include "robot_simulation.h"
#include <iostream>

int main() {
    // Create the field and robot
    Field field(10, 10);
    Robot robot(0, 0, 'E', &field);

    field.setCell(1, 1, '#');
    field.setCell(1, 2, '#');
    field.setCell(1, 3, '#');
    field.setCell(3, 1, '#');
    field.setCell(3, 2, '#');
    field.setCell(3, 3, '#');
    field.setCell(3, 5, '#');
    field.setCell(3, 6, '#');
    field.setCell(3, 7, '#');
    field.setCell(5, 3, '#');
    field.setCell(5, 4, '#');
    field.setCell(5, 5, '#');
    field.setCell(5, 7, '#');
    field.setCell(5, 8, '#');
    field.setCell(7, 1, '#');
    field.setCell(7, 2, '#');
    field.setCell(7, 3, '#');
    field.setCell(7, 5, '#');
    field.setCell(7, 6, '#');
    field.setCell(7, 7, '#');
    field.setCell(8, 8, '#');
    field.setCell(9, 8, '#');

    // Place collectibles
    field.setCell(0, 9, 'C');
    field.setCell(2, 4, 'C');
    field.setCell(4, 1, 'C');
    field.setCell(6, 8, 'C');
    field.setCell(8, 5, 'C');

    // Place the goal
    field.setCell(9, 9, 'G');

    std::string initialField, finalField;
    saveFieldToString(field, initialField);

    // TODO: Implement your algorithm here
    // Use robot.moveForward(), robot.turnLeft(), robot.turnRight(), 
    // robot.distanceToObstacle(), robot.collectObjective(), and robot.reachedGoal()
    // to navigate the robot to the goal while collecting objectives
    // make sure to be as efficient as possible and use the functions you are given:
    // moveForward() -> robot moves forward 
    // turnLeft() -> robot turns 90 degrees to the left
    // turnRight() -> robot turns 90 degrees to the right
    // distanceToObstacle() -> returns the number of cells to the next obstacle in front of the robot
    // collectObjective() -> collects an objective if the robot is on a cell with one, returns true if collected
    // reachedGoal() -> returns true if the robot has reached the goal cell
    // isObjectiveNearby(radius) -> returns true if an objective is within the given radius
    // getCollectiblesCount() -> returns the total number of collectibles remaining on the field


    std::cout << "Initial distance to obstacle: " << robot.distanceToObstacle() << std::endl;
    while (robot.distanceToObstacle() > 0)
        robot.moveForward();
    std::cout << robot.getCollectiblesCount()<<' '<<robot.isObjectiveNearby(2);


    saveFieldToString(field, finalField);
    std::cout << "INITIAL_FIELD\n" << initialField << "FINAL_FIELD\n" << finalField;
    std::cout << "OBJECTIVES_COLLECTED\n" << collected << "\n";

    return 0;
}