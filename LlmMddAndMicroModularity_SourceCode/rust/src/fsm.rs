// file: fsm.rs

pub mod fsm {
    use std::collections::HashMap;
    use std::rc::Rc;

    pub struct State {
        pub entry_action: Option<Box<dyn Fn()>>,
        pub exit_action: Option<Box<dyn Fn()>>
    }

    impl State {
        fn new() -> Self {
            Self {
                entry_action: None,
                exit_action: None
            }
        }
    }

    #[derive(Clone)]
    pub struct Transition {
        from_state: String,
        to_state: String,
        pub condition: Rc<dyn Fn() -> bool>,
        pub action: Option<Rc<dyn Fn()>>
    }

    pub struct StateMachine {
        current_state: String,
        pub states: HashMap<String, State>,
        pub transitions: HashMap<String, Transition>
    }

    impl StateMachine {
        pub fn new(initial_state: &str) -> Self {
            let states = HashMap::new();
            let transitions = HashMap::new();
            //states.insert(String::from(initial_state), State::new());

            Self {
                current_state: String::from(initial_state),
                states,
                transitions        
            }
        }

        pub fn add_state(&mut self, name: &str) {
            self.states.insert(String::from(name), State::new());
        }

        pub fn add_transition(&mut self, name: &str, from_state: &str, to_state: &str) {
            self.transitions.insert(String::from(name), Transition {
                from_state: String::from(from_state),
                to_state: String::from(to_state),
                condition: Rc::new(|| true),
                action: None
            });
        }

        pub fn do_transition_call_actions(&mut self, transition: Transition) -> bool {
            if self.current_state == transition.from_state && (transition.condition)() {
                if let Some(exit_action) = self.states.get(&self.current_state).unwrap().exit_action.as_ref() {
                    exit_action();
                }
                if let Some(transition_action) = transition.action.as_ref() {
                    transition_action();
                }
                self.current_state = transition.to_state.clone();
                if let Some(entry_action) = self.states.get(&self.current_state).unwrap().entry_action.as_ref() {
                    entry_action();
                }
                return true;
            }
            false
        }
    }
}