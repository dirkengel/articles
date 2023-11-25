#!/usr/bin/python3

import re
import argparse

def parse_plantuml(plantuml_code):
    state_pattern = re.compile(r'state (\w+)\s*{')
    entry_action_pattern = re.compile(r'\s*(\w+)\s*:\s*>\s*(.+)')
    exit_action_pattern = re.compile(r'\s*(\w+)\s*:\s*<\s*(.+)')
    transition_pattern = re.compile(r'(\w+)\s*-->\s*(\w+)\s*:\s*(\w+)\s*(\[.*\])?\s*/\s*(.+)')
    init_pattern = re.compile(r'\[\*\]\s*-->\s*(\w+)')

    states = []
    transitions = []

    lines = plantuml_code.split('\n')
    current_state = None

    for line in lines:
        state_match = state_pattern.match(line)
        if state_match:
            current_state = state_match.group(1)
            states.append({'name': current_state, 'entry_action': None, 'exit_action': None})

        entry_action_match = entry_action_pattern.match(line)
        if entry_action_match and current_state:
            states[-1]['entry_action'] = entry_action_match.group(2)

        exit_action_match = exit_action_pattern.match(line)
        if exit_action_match and current_state:
            states[-1]['exit_action'] = exit_action_match.group(2)

        transition_match = transition_pattern.match(line)
        if transition_match:
            from_state = transition_match.group(1)
            to_state = transition_match.group(2)
            event = transition_match.group(3)
            action = transition_match.group(4)
            transitions.append({'from_state': from_state, 'to_state': to_state, 'event': event, 'action': action})
        
        init_match = init_pattern.match(line)
        if init_match:
            init_state = init_match.group(1)

    return states, transitions, init_state

def main():
    parser = argparse.ArgumentParser(description="Parse PlantUML file and print state and transition information.")
    parser.add_argument("plantuml_file", help="Path to the PlantUML file")
    parser.add_argument("-l", "--language", choices=["c++", "rust"], help="Select between C++ and Rust")
    args = parser.parse_args()

    plantuml_file = args.plantuml_file

    try:
        with open(plantuml_file, 'r') as file:
            plantuml_code = file.read()
            name = plantuml_file.split('.')[0]
            states, transitions, init_state = parse_plantuml(plantuml_code)

            # Print collected information
            print("Name:", name)
            print("Initial State:", init_state)

            print("\nStates:")
            for state in states:
                print(state)

            print("\nTransitions:")
            for transition in transitions:
                print(transition)

            if args.language is not None:
                language = args.language.upper()
                if language == "C++":
                    print("\nC++:\n")
                    generate_cpp(name, states, transitions, init_state)
                elif language == "RUST":
                    print("\nRust:\n")
                    generate_rust(name, states, transitions, init_state)

    except FileNotFoundError:
        print(f"Error: File '{plantuml_file}' not found.")
        exit(1)


###############################################################################

def events(transitions):
    events = set(transition['event'] for transition in transitions)
    return list(events)

def transitions_for_event(transitions, event):
    return [transition for transition in transitions if transition['event'] == event]

def indent(depth):
    return " " * depth * 3

def generate_cpp(name, states, transitions, init_state):
    print("#include \"fsm.h\"\n")
    print("class " + name + " {")
    print("public:")
    print(indent(1) + name + "() = default;")
    print(indent(1) + "~" + name + "() = default;\n")
    transition_members = set()
    for e in events(transitions):
        print(indent(1) + "bool " + e + "() {")
        print(indent(2) + "bool result = false;")
        ets = transitions_for_event(transitions, e)
        for et in ets:
            print(indent(2) + "if (not result) {")
            transition_name = et['event'] + "_" + et["from_state"] + "_" + et["to_state"]
            transition_members.add((transition_name, et["from_state"], et["to_state"]))
            print(indent(3) + "result = fsm.doTransitionCallActions(" + transition_name + ");")
            print(indent(2) + "}")
        print(indent(2) + "return result;")
        print(indent(1) + "}\n")
    for s in states:
        print(indent(1) + "State " + s['name'] + "State {};")
    print()    
    for t in transition_members:
        print(indent(1) + "Transition " + t[0] + " {Transition(&" + t[1] + "State, &" + t[2] + "State)};")
    print("\nprivate:")
    print(indent(1) + "StateMachine fsm {StateMachine(&" + init_state + "State)};")
    print("};")


###############################################################################


if __name__ == "__main__":
    main()
