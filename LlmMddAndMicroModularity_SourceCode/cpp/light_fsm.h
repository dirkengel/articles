// file: light_fsm.h -> generated code

#include "fsm.h"

class LightFsm {
public:
   LightFsm() = default;
   ~LightFsm() = default;

   bool turnOff() {
      bool result = false;
      if (not result) {
         result = fsm.doTransitionCallActions(turnOff_on_off);
      }
      return result;
   }

   bool turnOn() {
      bool result = false;
      if (not result) {
         result = fsm.doTransitionCallActions(turnOn_off_on);
      }
      return result;
   }

   State offState {};
   State onState {};

   Transition turnOff_on_off {Transition(&onState, &offState)};
   Transition turnOn_off_on {Transition(&offState, &onState)};

private:
   StateMachine fsm {StateMachine(&offState)};
};