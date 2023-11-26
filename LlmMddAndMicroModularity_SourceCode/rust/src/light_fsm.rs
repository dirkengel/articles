// file light_fsm.rs

pub mod light_fsm {
    use crate::fsm::fsm::StateMachine;
 
    pub struct LightFsm {
       pub fsm: StateMachine
    }
 
    impl LightFsm {
       pub fn new(initial_state: &str) -> Self {
          let mut fsm = StateMachine::new(initial_state);
 
          fsm.add_state("off");
          fsm.add_state("on");
          fsm.add_transition("turnOff_on_off", "on", "off");
          fsm.add_transition("turnOn_off_on", "off", "on");
          Self { fsm }
       }
 
       pub fn turn_off(&mut self) -> bool {
          let mut result = false;
          if !result {
             let transition = self.fsm.transitions["turnOff_on_off"].clone();
             result =self.fsm.do_transition_call_actions(transition)
          }
          result
       }
 
       pub fn turn_on(&mut self) -> bool {
          let mut result = false;
          if !result {
             let transition = self.fsm.transitions["turnOn_off_on"].clone();
             result =self.fsm.do_transition_call_actions(transition)
          }
          result
       }
 
    }
 }