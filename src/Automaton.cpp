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
Automaton::Automaton(std::vector<std::string> alphabet, std::vector<State> states, bool verbose) : _alphabet(alphabet), _states(states), _verbose(verbose), _activeStateIndex(0) { //TODO: test this method
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


/** @description Updates the _alphabet property of an Automaton to match all the symbols of its transitions (from State class), by default this method will not remove the symbol in the alphabet that are not used by the instance
 *
 *  @param forceMatch {bool} If the alphabet has to be cleared to match exactly all the symbols found, default is false
 */
void Automaton::updateAlphabet(bool forceMatch) { // TODO: test this method
    int i(0), j(0);
    vector<string> stateSymbols;

    // If the alphabet has to be cleared before finding symbols
    if (forceMatch)
        _alphabet.clear();

    // Exploring the states
    for (i = 0; i < _states.size(); i++) {
        // Getting a shortcut to the state's symbols
        stateSymbols = _states[i].getSymbols();

        // Adding the symbols that were found to the alphabet if they are not already in
        for (j = 0; j < stateSymbols.size(); j++)
            if (find(_alphabet.begin(), _alphabet.end(), stateSymbols[i]) != _alphabet.end())
                _alphabet.push_back(stateSymbols[i]);
    }
}

