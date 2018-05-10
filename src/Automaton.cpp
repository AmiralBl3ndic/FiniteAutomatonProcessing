//
// Created by camboy on 06/05/18.
//

#include "Automaton.h"

using namespace std;


/** @description Default constructor, requires an alphabet vector({std::string}) and a states vector ({State}), it has a verbose option (default set to false) for displaying warnings in case of use of default values
*
*   @param alphabet {std::vector<std::string> = empty symbol} Is the alphabet of the Automaton represented under a list ({std::vector}) of strings ({std::string}), default set to only empty symbol "*"
*   @param states {std::vector<State> = empty} Is the list of the Automaton's states ({State}), default set to 0 state
*   @param verbose {bool = false} Is an optional parameter (default is false) to give more information about the processing of the method when set to true
*/
Automaton::Automaton(std::vector<std::string> alphabet, std::vector<State> states, bool verbose) : _alphabet(alphabet), _states(states), _verbose(verbose), _activeStateIndex(0) {
    if (alphabet.empty()) {

        // Displaying warnings only if verbose mode
        if (_verbose)
            cerr << "Warning: initializing alphabet of Automaton with no values, adding empty symbol '*'" << endl;

        // Adding the empty symbol '*' to the alphabet so that it contains at least one symbol
        alphabet.push_back("*");
        _alphabet = alphabet;

        // TODO: check for the alphabet in the passed states
    }

    if (states.empty()) {
        if (_verbose)
            cerr << "Warning: initializing Automaton with no states" << endl;

        _activeStateIndex = -1;
    }
}

