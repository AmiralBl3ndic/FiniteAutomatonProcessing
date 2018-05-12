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
        logBasicError(string("(Warning) Initializing alphabet of Automaton with no values, adding the empty symbol \"") + EMPTY_SYMBOL + "\"");

        // Adding the empty symbol '*' to the alphabet so that it contains at least one symbol
        alphabet.push_back(EMPTY_SYMBOL);
        _alphabet = alphabet;

        // TODO: check for the alphabet in the passed states
    }

    if (states.empty()) {
        logBasicError("(Warning) Initializing Automaton with no states");
        _activeStateIndex = -1;
    }
}


void Automaton::logBasicError(const std::string &error) {
    if (_verbose)
        cerr << "ERROR: " << error << endl;
}


void Automaton::logVerbose(const std::string &message) {
    if (_verbose)
        cout << message << endl;
}


/** @description Updates the _alphabet property of an Automaton to match all the symbols of its transitions (from State class), by default this method will not remove the symbol in the alphabet that are not used by the instance
 *
 *  @param forceMatch {bool} If the alphabet has to be cleared to match exactly all the symbols found, default is false
 */
void Automaton::updateAlphabet(bool forceMatch) { // TODO: test this method
    int i(0), j(0);
    vector<string> stateSymbols;

    // If the alphabet has to be cleared before finding symbols
    if (forceMatch) {
        _alphabet.clear();
        logVerbose("Alphabet cleared");
    }

    // Exploring the states
    for (i = 0; i < _states.size(); i++) {
        // Getting a shortcut to the state's symbols
        stateSymbols = _states[i].getSymbols();

        // Adding the symbols that were found to the alphabet if they are not already in
        for (j = 0; j < stateSymbols.size(); j++)
            if (find(_alphabet.begin(), _alphabet.end(), stateSymbols[i]) != _alphabet.end()) {
                _alphabet.push_back(stateSymbols[i]);
                logVerbose("New symbol found and added to the alphabet");
            }
    }
}


/** @description Checks whether the instance is an asynchronous automaton or not
 *
 *  @return {bool} If the instance is asynchronous
 */
bool Automaton::isAsynchronous() const { // TODO: test this method
    int i(0), j(0);
    vector<string> stateSymbols;
    bool asynchronous = false;

    for (i = 0; i < _states.size(); i++) {
        stateSymbols = _states[i].getSymbols();

        // Checking if the state contains a transition labeled with the EMPTY_SYMBOL
        if (find(stateSymbols.begin(), stateSymbols.end(), EMPTY_SYMBOL) != stateSymbols.end()) {
            if (!asynchronous) {
                cout << "This automaton is asynchronous... Looking for the transitions labeled with \"" << EMPTY_SYMBOL << "\"" << endl;
                asynchronous = true;
            }

            cout << "The state #" << i << " of this automaton contains a transition labeled with \"" << EMPTY_SYMBOL << "\"" << endl;

            for (j = 0; j < _states[i].getTransitions().size(); j++) {
                if (_states[i].getTransitions()[j].getSymbol() == EMPTY_SYMBOL)
                    cout << "    The transition #" << j << " is responsible for this automaton being asynchronous" << endl;
            }
        }
    }

    return asynchronous;
}


bool Automaton::addTransition(const std::string &from, const std::string &symbol, const std::string &to) { // TODO: test this method
    bool checkFrom(false), checkTo(false);
    int i(0), fromID(-1);

    for (i = 0; i < _states.size(); i++) {
        if (_states[i].getIdentifier() == from) {
            checkFrom = true;
            fromID = i;
        }
        if (_states[i].getIdentifier() == to)
            checkTo = true;
    }

    if (checkFrom && checkTo)
        _states[fromID].addTransition(symbol, to);
    else
        logBasicError("Cannot add transition, outgoing or target state (or both) are not recognized");

    return checkFrom && checkTo;
}

