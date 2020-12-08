//
// Created by Javid Asgarov on 31.05.20.
//

#ifndef THREADS_WORLD_H
#define THREADS_WORLD_H

#include <vector>
#include <cstdlib>
#include <iostream>

class World {
    std::vector<std::vector<int>> fields;
    int size;

public:
    void initialiseFields(int maxFieldValue);

    explicit World(int size, int maxFieldValue) {
        this->size = size;
        initialiseFields(maxFieldValue);
    }

    void displayWorld();

    int getField(int x, int y);

    void decrementField(int x, int y);

    bool checkIfAllFieldsAreZero();

    int getSize() const;
};

#endif //THREADS_WORLD_H
