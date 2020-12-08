//
// Created by Javid Asgarov on 31.05.20.
//

#include <mutex>
#include "Robot.h"
#include "World.h"


std::mutex my_mutex;

/**
 * Only constructor
 * @param name
 */
Robot::Robot(const std::string &name, int size, bool diagonalStrategy) : name(name) {
    this->name = name;
    pointsCollected = 0;
    diagonalStrategy = diagonalStrategy;
    moveToRandomField(size);
}

/**
 * This function calculates the coordinates for the field to move on to randomly
 * and afterwards collects the point from that field
 * @param world
 */
void Robot::moveToRandomField(int size) {
    coordinateX = rand() % size;
    coordinateY = rand() % size;
}

/**
 * Function that moves the robot to neighbour field and then collects the point
 * @param world
 */
void Robot::moveAndCollect(World *world) {
    int maxCoordinate = world->getSize() - 1;
    if (diagonalStrategy) {
        moveToRandomDiagonalNeighbourField(maxCoordinate);
    } else {
        moveToRandomQuadraticNeighbourField(maxCoordinate);
    }
    moveToRandomField(world->getSize());
    collectPoint(world);
}

/**
 * Moves robot to the random neighbour field
 * @param maxCoordinate
 */
void Robot::moveToRandomQuadraticNeighbourField(int maxCoordinate) {
    int direction = rand() % 4;

    switch (direction) {
        case 0: {
            if (coordinateX > 0) {
                coordinateX--;
            } else {
                //if end of x axis is reached go down or up
                moveOnYAxis();
            }
        }
        case 1: {
            if (coordinateX < maxCoordinate) {
                coordinateX++;
            } else {
                //if end of x axis is reached go down or up
                moveOnYAxis();
            }
        }
        case 2: {
            if (coordinateY > 0) {
                coordinateY--;
            } else {
                //if end of Y axis is reached move on X axis
                moveOnXAxis();
            }
        }
        default: {
            if (coordinateY < maxCoordinate) {
                coordinateY++;
            } else {
                //if end of Y axis is reached move on X axis
                moveOnXAxis();
            }
        }
    }

}

/**
 * Helper method to move on Y axis
 */
void Robot::moveOnYAxis() {
    if (coordinateY > 0) {
        coordinateY--;
    } else {
        coordinateY++;
    }
}

/**
 * Helper method to move on X axis
 */
void Robot::moveOnXAxis() {
    if (coordinateX > 0) {
        coordinateX--;
    } else {
        coordinateX++;
    }
}

/**
 * Moves robot to the random diagonal neighbour field
 * @param maxCoordinate
 */
void Robot::moveToRandomDiagonalNeighbourField(int maxCoordinate) {
//    If on the edge move quadratically to avoid endless diagonal loops
    if (coordinateX == 0) {
        coordinateX++;
    }
    if (coordinateX == maxCoordinate) {
        coordinateX--;
    }
    if (coordinateY == 0) {
        coordinateY++;
    }
    if (coordinateY == maxCoordinate) {
        coordinateY--;
    }

    int num = rand() % 4;
    if (num == 0) {
        coordinateX++;
        coordinateY++;
    } else if (num == 1) {
        coordinateX++;
        coordinateY--;
    } else if (num == 2) {
        coordinateX--;
        coordinateY++;
    } else if (num == 3) {
        coordinateX--;
        coordinateY--;
    }
}

/**
 * Collects the point from the field provided the field value > 0
 * It is important that the operation of incrementing robot's point and decrementing fields point was atomic
 * therefore mutex is used here
 * lock_guard is used for automatic resource management
 * @param world
 */
void Robot::collectPoint(World *world) {
    std::lock_guard<std::mutex> guard(my_mutex);
    if (world->getField(coordinateX, coordinateY) > 0) {
        pointsCollected++;
        world->decrementField(coordinateX, coordinateY);
    }
}

/**
 * Overloading the plus operator to produce new robot
 * @param other
 * @return
 */
Robot Robot::operator+(const Robot &other) {
    Robot newRobot = *this;
    newRobot.name = this->name + other.name;
    return newRobot;
}

/**
 * Getter for points collected
 * @return
 */
int Robot::getPointsCollected() const {
    return pointsCollected;
}
