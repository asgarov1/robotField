//
// Created by Javid Asgarov on 31.05.20.
//

#ifndef THREADS_ROBOT_H
#define THREADS_ROBOT_H

#include <string>
#include <vector>
#include "World.h"

class Robot {

public:
    Robot(const std::string &name, int size, bool diagonalStrategy);

    int getPointsCollected() const;

    void moveAndCollect(World *world);


    Robot operator+ (const Robot& other);

private:
    int coordinateX{};
    int coordinateY{};

    std::string name;

    int pointsCollected;

    void collectPoint(World *world);

    void moveToRandomField(int size);

    void moveToRandomQuadraticNeighbourField(int maxCoordinate);
    void moveToRandomDiagonalNeighbourField(int maxCoordinate);

    bool diagonalStrategy;

    void moveOnXAxis();

    void moveOnYAxis();
};


#endif //THREADS_ROBOT_H
