// implementation of header 


#include <webots/GPS.hpp>
#include <webots/Display.hpp> 

#include <utility> 

#include "EPuckGreenPlusRobot.hpp"


EPuckGreenPlusRobot::EPuckGreenPlusRobot() 
: mGPS {getGPS("gps")}, mDisplay1 {getDisplay("display1")},
mDP1Width {mDisplay1->getWidth()}, mDP1Height {mDisplay1->getHeight()}
{
    mGPS->enable(TIME_STEP);

};

// call get height member function from display
// check names in webots 

// defining the specific ftn fro EPuckGreenPlusRobot not just any run function
void EPuckGreenPlusRobot::run() {
    while (step(TIME_STEP) != -1) {
        telecontrol(); // calling an inherited function 

        readGPS();
        displayTrajectory(); 
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
