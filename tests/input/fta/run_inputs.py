#!/usr/bin/env python

import sys
import subprocess

def main():
    # Correct corner case inputs
    pass_inputs = [
            "correct_tree_input.xml",
            "mixed_definitions.xml",
            "model_data_mixed_definitions.xml",
            "trailing_spaces.xml",
            ]

    pass_probs = [
            "correct_tree_input_with_probs.xml",
            ]

    # Wrong input files in the current directory
    bad_inputs = [
            "../xml_formatting_error.xml",
            "../schema_fail.xml",
            "../unsupported_feature.xml",
            "unsupported_gate.xml",
            "nonexistent_file.xml",
            "doubly_defined_gate.xml",
            "doubly_defined_house.xml",
            "doubly_defined_basic.xml",
            "missing_event_definition.xml",
            "missing_basic_event_definition.xml",
            "missing_house_event_definition.xml",
            "missing_gate_definition.xml",
            "name_clash_basic_gate.xml",
            "name_clash_house_gate.xml",
            "name_clash_gate_primary.xml",
            "name_clash_basic_house.xml",
            "name_clash_house_basic.xml",
            "def_clash_basic_gate.xml",
            "def_clash_house_gate.xml",
            "def_clash_gate_primary.xml",
            "def_clash_basic_house.xml",
            "def_clash_house_basic.xml",
            "def_name_house_basic.xml",
            "def_name_basic_house.xml",
            "atleast_gate.xml",
            "unordered_structure.xml",
            "dangling_gate.xml",
            "non_top_gate.xml",
            "cyclic_tree.xml",
            ]

    # Run correct inputs
    print("\nRUNNING CORRECT INPUTS\n\n")
    for ic in pass_inputs:
        print("\nRUNNING : " + ic + "\n")
        args = ["scram", ic]
        subprocess.call(args)

    # Run correct probabilities
    print("\nRUNNING CORRECT PROBABILITY INPUTS\n\n")
    for p in pass_probs:
        print("\nRUNNING : " + p + "\n")
        args = ["scram", p]
        subprocess.call(args)

    # Run incorrect inputs
    print("\nRUNNING INCORRECT INPUTS\n\n")
    for i in bad_inputs:
        print("\nRUNNING : " + i + "\n")
        msg = ""
        args = ["scram", i]
        try:
            subprocess.call(args)
        except:
            msg = sys.exc_info()[0]
        print(msg)

if __name__ == "__main__":
    main()
