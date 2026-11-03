#pragma once 

#include "EPuckGreenRobot.hpp"
#include <webots/GPS.hpp>
#include <webots/Display.hpp>

#include <utility> 
// for std::pair 

const double WORLD_WIDTH {1.0};
const double WORLD_HEIGHT {1.0};

class EPuckGreenPlusRobot : public EPuckGreenRobot {
public:
    EPuckGreenPlusRobot();
    void run();

protected:
    void readGPS();
    void displayTrajectory() const;

private: 
    webots::GPS* mGPS {};
    std::pair<double, double> mPosition {}; // x, y coords
    webots::Display* mDisplay1 {};
    int mDP1Width {};
    int mDP1Height {};
};