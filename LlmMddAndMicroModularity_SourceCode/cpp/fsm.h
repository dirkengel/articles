// file: fsm.h -> framework code

#include <functional>

class State {
public:
    State() = default;
    ~State() = default;

    std::function<void()> entryAction {nullptr};
    std::function<void()> exitAction {nullptr};
};

class Transition {
public:
    Transition(State* from, State* to) : fromState(from), toState(to) {}
    ~Transition() = default;

    State* getFromState() const {return fromState;}
    State* getToState() const {return toState;}

    std::function<bool()> condition {[] {return true;}}; // valid by default
    std::function<void()> action {nullptr};

private:
    State* fromState {nullptr};
    State* toState {nullptr};
};

class StateMachine {
public:
    StateMachine(State* initialState) : currentState {initialState} {}
    ~StateMachine() = default;

    bool doTransitionCallActions(const Transition& transition) {
        bool success = false;
        if (currentState == transition.getFromState() && transition.condition()) {
            if (currentState->exitAction != nullptr) {
                currentState->exitAction();
            }
            if (transition.action != nullptr) {
                transition.action();
            }
            currentState = transition.getToState();
            if (currentState->entryAction != nullptr) {
                currentState->entryAction();
            }
            success = true;
        }
        return success;
    }

private:   
    State* currentState;
};