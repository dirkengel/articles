// file light_fsm.cpp -> test or application code

#include <iostream>
#include "blinking_light_fsm.h"

int main() {
    BlinkingLightFsm blinkingLightFsm;
    bool blinking = false;

    // Inject actions
    blinkingLightFsm.offState.entryAction = [] {std::cout << "entering off state" << std::endl;};
    blinkingLightFsm.offState.exitAction = [] {std::cout << "exiting off state" << std::endl;};
   
    blinkingLightFsm.onState.entryAction = [] {std::cout << "entering on state" << std::endl;};
    blinkingLightFsm.onState.exitAction = [] {std::cout << "exiting on state" << std::endl;};
      
    blinkingLightFsm.blinkingState.entryAction = [] {std::cout << "entering blinking state" << std::endl;};
    blinkingLightFsm.blinkingState.exitAction = [] {std::cout << "exiting blinking state" << std::endl;};
           
    blinkingLightFsm.turnOn_off_on.condition = [&blinking] {std::cout << "check steady" << std::endl;return not blinking;};
    blinkingLightFsm.turnOn_off_on.action = [] {std::cout << "turning on (steady)" << std::endl;};
    
    blinkingLightFsm.turnOn_off_blinking.condition = [&blinking] {std::cout << "check blinking" << std::endl; return blinking;};
    blinkingLightFsm.turnOn_off_blinking.action = [] {std::cout << "turning on (blinking)" << std::endl;};

    blinkingLightFsm.turnOff_on_off.action = [] {std::cout << "turning off (steady)" << std::endl;};
    blinkingLightFsm.turnOff_blinking_off.action = [] {std::cout << "turning off (blinking)" << std::endl;};

    // Simulate events
    blinkingLightFsm.turnOn();
    std::cout << "---" << std::endl;

    blinkingLightFsm.turnOff();
    std::cout << "---" << std::endl;
    
    blinking = true;
    blinkingLightFsm.turnOn();
    std::cout << "---" << std::endl;

    blinkingLightFsm.turnOff();    
    std::cout << "---" << std::endl;

    std::cout << "off is off" << std::endl;
    blinkingLightFsm.turnOff();

    return 0;
}