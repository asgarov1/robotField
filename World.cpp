//
// Created by Javid Asgarov on 31.05.20.
//

#include <vector>
#include <cstdlib>
#include <iostream>

#include "World.h"

using namespace std;

/**
 * Called in the constructor
 * I am initialising the fields by random numbers up to max set value
 * Also the total of all points is displayed
 */
void World::initialiseFields(int maxFieldValue) {
    long totalPoints = 0;
    for (int i = 0; i < size; ++i) {
        vector<int> temp;
        for (int j = 0; j < size; ++j) {
            int value = rand() % maxFieldValue;
            temp.push_back(value);
            totalPoints += value;
        }
        fields.push_back(temp);
    }
    cout << "Total value of world's points: " << totalPoints << endl;
}

/**
 * Function to display the field values of the world
 */
void World::displayWorld() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%3d ", fields.at(i).at(j));
        }
        cout << endl;
    }
}

/**
 * Gets field based on coordinates
 * @param x
 * @param y
 * @return
 */
int World::getField(int x, int y) {
    return fields.at(x).at(y);
}

/**
 * Decrements the field's value
 * @param x
 * @param y
 */
void World::decrementField(int x, int y) {
    fields.at(x).at(y) = fields.at(x).at(y) - 1;
}

/**
 * Checks if all fields are zero
 * @return
 */
bool World::checkIfAllFieldsAreZero() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (fields.at(i).at(j) != 0) {
                return false;
            }
        }
    }
    return true;
}

/**
 * Getter for size field
 * @return
 */
int World::getSize() const {
    return size;
}
