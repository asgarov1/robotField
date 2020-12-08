#include <thread>
#include "World.h"
#include "Robot.h"

using namespace std;

// I didn't use friends because I am against the concept.
// It increases coupling between the 2 classes, breaks encapsulation. Even if it would make my code a bit shorter.
// Basically it is against everything OOP stands for and I happen to like OOP:)

// Also to be RAII compliant I am using lock_guard in order to automatically free mutex in Robot class

/**
 * A helper method that creates a vector of Robots each of which is initialised with a capital letter as a name
 * Fulfilling one of the assignment tasks the overloaded operator+ is used in this function
 * @param numberOfRobots to be created
 * @return vector of ready Robots
 */
std::vector<Robot> createRobots(int numberOfRobots, int size, bool isDiagonalStrategy);

/**
 * Function that is used for threads callback to move robot
 * @param world
 * @param robot
 */
void moveRobot(World *world, Robot *robot);

/**
 * Sums all of the robots collected points
 * @param robots
 * @return
 */
long sumAllRobotsPoints(const vector<Robot>& robots);

/**
 * Running the main program (where robots start collecting from fields) with the following variable parameters
 * @param worldSize
 * @param maxFieldValue
 * @param numberOfRobots
 * @param isDiagonalStrategy if true diagonal movement will be used, else quadratic (horizontal/vertical axes)
 */
void runProgram(int worldSize, int maxFieldValue, int numberOfRobots, bool isDiagonalStrategy);

/**
 * Prompts user for a number with try catch and keeps re-asking until proper input is entered
 * @param message that explains what number should be entered
 * @return number entered
 */
int promptNumber(const string& message);

/**
 * Prompts to choose either diagonal or quadratic movement strategy for robots
 * @return
 */
int promptStrategy();

/**
 * Main function
 * @return
 */
int main() {
    int worldSize = promptNumber("Please enter the world size: ");
    int maxFieldValue = promptNumber("Please enter max field value: ");
    int numberOfRobots = promptNumber("Please enter the number of robots: ");

    bool diagonalStrategy = promptStrategy() == 1;

    runProgram(worldSize, maxFieldValue, numberOfRobots, diagonalStrategy);
    return 0;
}

int promptStrategy() {
    int strategyChoice = 0;
    bool error = true;
    cout << "Enter 1 for diagonal or 2 for quadratic movement strategy ";
    while (error) {
        try {
            cin >> strategyChoice;
            if (cin.fail()) {
                throw std::invalid_argument("You must enter a number! ");
            } else if (strategyChoice < 1 || strategyChoice > 2) {
                throw std::invalid_argument("You must choose either 1 or 2! ");
            } else {
                error = false;
            }
        } catch (const invalid_argument &exc) {
            cin.clear();
            cin.ignore();
            cout << exc.what() << endl;
        }
    }
    return strategyChoice;
}

int promptNumber(const string& message) {
    int size = 0;
    bool error = true;
    cout << message;
    while (error) {
        try {
            cin >> size;
            if (cin.fail()) {
                throw std::invalid_argument("Not a number!");
            } else {
                error = false;
            }
        } catch (const invalid_argument &exc) {
            cin.clear();
            cin.ignore();
            cout << "Something went wrong, please enter a number " << endl;
        }
    }
    return size;
}

void runProgram(int worldSize, int maxFieldValue, int numberOfRobots, bool isDiagonalStrategy) {
    World world(worldSize, maxFieldValue);
    cout << "Before robots: " << endl;
    world.displayWorld();

    vector<Robot> robots = createRobots(numberOfRobots, world.getSize(), isDiagonalStrategy);

    std::thread threads[robots.size()];
    for (int i = 0; i < robots.size(); ++i) {
        threads[i] = std::thread(moveRobot, &world, &robots.at(i));
    }

    cout << "\n\nmight take a couple of seconds ... " << endl;
    for (int i = 0; i < robots.size(); ++i) {
        threads[i].join();
    }

    cout << endl << endl << endl;
    cout << "After robots: " << endl;
    world.displayWorld();
    cout << "Total value of all robots' points: " << sumAllRobotsPoints(robots) << endl;
}

long sumAllRobotsPoints(const vector<Robot>& robots) {
    long total = 0;
    for (auto &robot : robots) {
        total += robot.getPointsCollected();
    }
    return total;
}

void moveRobot(World *world, Robot *robot) {
    while (!world->checkIfAllFieldsAreZero()) {
        robot->moveAndCollect(world);
    }
}

vector<Robot> createRobots(int numberOfRobots, int worldSize, bool isDiagonalStrategy) {
    vector<Robot> robots;
    char letter = 65; //ASCII for capital A
    Robot TRobot("T", worldSize, isDiagonalStrategy);
    for (int i = 0; i < numberOfRobots; ++i) {
        //Assigning names to Robots A, B, C ...
        string name(1, (char) letter++);
        Robot robot(name, worldSize, isDiagonalStrategy);

        //Creating the robot with the operator+
        robots.push_back(TRobot + robot);
    }
    return robots;
}