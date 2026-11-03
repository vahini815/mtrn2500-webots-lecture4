#pragma once 

#include "EPuckGreenRobot.hpp"
#include <webots/GPS.hpp>
#include <webots/Display.hpp>
#include <webots/Compass.hpp> 
#include <webots/Lidar.hpp> 

#include <utility> 
#include <vector> 
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
    
    void readCompass();
    void readLidar();
    void displayMap() const; 

private: 
    webots::GPS* mGPS {};
    std::pair<double, double> mPosition {}; // x, y coords
    
    webots::Compass* mCompass {};
    double mHeading {}; 
    
    webots::Lidar* mLidar {}; 
    std::vector<std::pair<double, double>> mPointCloud {}; 
    
    webots::Display* mDisplay1 {};
    webots::Display* mDisplay2 {};
    int mDP1Width {};
    int mDP1Height {};
    int mDP2Width {};
    int mDP2Height {};
};