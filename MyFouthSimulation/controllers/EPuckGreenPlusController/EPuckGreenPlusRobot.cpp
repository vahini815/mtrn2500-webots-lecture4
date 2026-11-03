// implementation of header 


#include <webots/GPS.hpp>
#include <webots/Display.hpp> 

#include <utility> 
#include <cmath> 
#include <iostream> 

#include "EPuckGreenPlusRobot.hpp"


EPuckGreenPlusRobot::EPuckGreenPlusRobot() 
: mGPS {getGPS("gps")}
, mCompass {getCompass("compass")} 
, mLidar {getLidar("lidar")}
, mDisplay1 {getDisplay("display1")}
, mDisplay2 {getDisplay("display")}
, mDP1Width {mDisplay1->getWidth()}
, mDP1Height {mDisplay1->getHeight()}
, mDP2Width {mDisplay2->getWidth()}
, mDP2Height {mDisplay2->getHeight()} 
{
    mGPS->enable(TIME_STEP);
    mCompass->enable(TIME_STEP); 
    mLidar->enable(TIME_STEP); 
    mLidar->enablePointCloud(); 
};

// call get height member function from display
// check names in webots 

// defining the specific ftn fro EPuckGreenPlusRobot not just any run function
void EPuckGreenPlusRobot::run() {
    while (step(TIME_STEP) != -1) {
        telecontrol(); // calling an inherited function 

        readGPS();
        displayTrajectory(); 
        
        readCompass(); 
    }
}

void EPuckGreenPlusRobot::readGPS() {
    const double* gpsValues {mGPS->getValues()}; // 3D double array returned by get values 

    mPosition = {gpsValues[0], gpsValues[1]}; // initialise pair 
    // std::cout << "Position: X: " << mPosition.first << " Position: Y: " << mPosition.second << std::endl; 


}

void EPuckGreenPlusRobot::displayTrajectory() const {
    // need to map between world & display (gps is world coord, we need to translate to display coord)
    // u = (W/2 + x) / (W * w)
    // v = (H/2 - y) / (H * h)
    mDisplay1->drawPixel((WORLD_WIDTH/2 + mPosition.first) / (WORLD_WIDTH * mDP1Width), (WORLD_HEIGHT/2 - mPosition.second) / (WORLD_HEIGHT * mDP1Height)); // draw dots 
};

void EPuckGreenPlusRobot::readCompass() {
    const double* compassValues {mCompass->getValues()};
    mHeading = atan2(compassValues[1], compassValues[0]); 
    std::cout << "Heading: " << (mHeading / 3.1415926535) * 180 << std::endl; 
}

void EPuckGreenPlusRobot::readLidar() {
    const webots::LidarPoint* pointCloud {mLidar->getLayerPointCloud(0)};
    mPointCloud.clear();
     
    for (int i = 0; i < mLidar->getNumberOfPoints(); i++) {
      mPointCloud.push_back({pointCloud[i].x, pointCloud[i].y});
    }
};

void EPuckGreenPlusRobot::displayMap() const {
    for (const auto& elem : mPointCloud) {
       const double xLocal {elem.first};
       const double yLocal {elem.second}; 
       
       const double xWorld {mPosition.first + xLocal * sin(mHeading) - yLocal * cos(mHeading)}; 
       const double yWorld {mPosition.second + xLocal * cos(mHeading) + yLocal * sin(mHeading)}; 
       
       mDisplay2->drawPixel((WORLD_WIDTH/2 + xWorld) / (WORLD_WIDTH * mDP2Width), (WORLD_HEIGHT/2 - yWorld) / (WORLD_HEIGHT * mDP2Height)); // draw dots 

    }
}; 
