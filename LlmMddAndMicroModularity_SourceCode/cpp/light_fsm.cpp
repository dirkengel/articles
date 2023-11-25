// file light_fsm.cpp -> test or application code

#include <iostream>
#include "light_fsm.h"

int main() {
    LightFsm lightFsm;

    // Inject actions
    lightFsm.offState.entryAction = [] {std::cout << "entering off state" << std::endl;};
    //lightFsm.offState.exitAction = [] {std::cout << "exiting off state" << std::endl;};
   
    //lightFsm.onState.entryAction = [] {std::cout << "entering on state" << std::endl;};
    lightFsm.onState.exitAction = [] {std::cout << "exiting on state" << std::endl;};
      
    lightFsm.turnOn_off_on.action = [] {std::cout << "turning on" << std::endl;};
    lightFsm.turnOff_on_off.action = [] {std::cout << "turning off" << std::endl;};

    // Simulate events
    lightFsm.turnOn();
    lightFsm.turnOff();
    std::cout << "off is off" << std::endl;
    lightFsm.turnOff();

    return 0;
}