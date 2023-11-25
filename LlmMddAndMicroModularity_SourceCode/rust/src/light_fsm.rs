// file light_fsm.rs

pub mod light_fsm {
    use crate::fsm::fsm::StateMachine;
    
    pub struct LightFsm {
        pub fsm: StateMachine
    }

    impl LightFsm {
        pub fn new(initial_state: &str) -> Self {
            let mut fsm = StateMachine::new(initial_state);

            fsm.add_state("on");
            fsm.add_state("off");

            fsm.add_transition("turnOn_offStateOnState_0", "off", "on");
            fsm.add_transition("turnOff_onStateOffState_0", "on", "off");

            Self { fsm }
        }

        pub fn turn_on(&mut self) -> bool {
            let transition = self.fsm.transitions["turnOn_offStateOnState_0"].clone();
            self.fsm.do_transition_call_actions(transition)
        }

        pub fn turn_off(&mut self) -> bool {
            let transition = self.fsm.transitions["turnOff_onStateOffState_0"].clone();
            self.fsm.do_transition_call_actions(transition)
        }
    }
}