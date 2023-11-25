// file main.rs

mod fsm;
mod light_fsm;

use std::rc::Rc;
use crate::light_fsm::light_fsm::LightFsm;

fn main() {
    let mut light_fsm = LightFsm::new("off");

    // Inject actions
    light_fsm.fsm.states.get_mut("off").unwrap().entry_action = Some(Box::new(|| println!("entering off state")));
    //light_fsm.fsm.states.get_mut("off").unwrap().exit_action = Some(Box::new(|| println!("exiting off state")));

    //light_fsm.fsm.states.get_mut("on").unwrap().entry_action = Some(Box::new(|| println!("entering on state")));
    light_fsm.fsm.states.get_mut("on").unwrap().exit_action = Some(Box::new(|| println!("exiting on state")));

    light_fsm.fsm.transitions.get_mut("turnOn_offStateOnState_0").unwrap().action = Some(Rc::new(|| println!("turning on")));
    light_fsm.fsm.transitions.get_mut("turnOff_onStateOffState_0").unwrap().action = Some(Rc::new(|| println!("turning off")));

    // Simulate events
    light_fsm.turn_on();
    light_fsm.turn_off();
    println!("off is off");
    light_fsm.turn_off();
}