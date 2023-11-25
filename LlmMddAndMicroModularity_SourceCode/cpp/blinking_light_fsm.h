// file: blinking_light_fsm.h -> generated code

#include "fsm.h"

class BlinkingLightFsm {
public:
   BlinkingLightFsm() = default;
   ~BlinkingLightFsm() = default;

   bool turnOff() {
      bool result = false;
      if (not result) {
         result = fsm.doTransitionCallActions(turnOff_on_off);
      }
      if (not result) {
         result = fsm.doTransitionCallActions(turnOff_blinking_off);
      }
      return result;
   }

   bool turnOn() {
      bool result = false;
      if (not result) {
         result = fsm.doTransitionCallActions(turnOn_off_on);
      }
      if (not result) {
         result = fsm.doTransitionCallActions(turnOn_off_blinking);
      }
      return result;
   }

   State offState {};
   State onState {};
   State blinkingState {};

   Transition turnOff_blinking_off {Transition(&blinkingState, &offState)};
   Transition turnOn_off_on {Transition(&offState, &onState)};
   Transition turnOn_off_blinking {Transition(&offState, &blinkingState)};
   Transition turnOff_on_off {Transition(&onState, &offState)};

private:
   StateMachine fsm {StateMachine(&offState)};
};