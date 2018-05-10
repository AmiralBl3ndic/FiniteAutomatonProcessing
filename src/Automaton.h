//
// Created by camboy on 06/05/18.
//

#ifndef TAI_AUTOMATON_H
#define TAI_AUTOMATON_H


#include "State.h"
#include <string>
#include <vector>

/** @description This class is the representation of an Automaton : it contains a list of states (State) which all contain a list of transitions (Transition)
 */
class Automaton {
private:
	std::vector<std::string> _alphabet;
	std::vector<State> _states;
	int _activeStateIndex;
	bool _verbose;

public:
    /** @description Default constructor, requires an alphabet vector({std::string}) and a states vector ({State}), it has a verbose option (default set to false) for displaying warnings in case of use of default values
     *
     * @param alphabet {std::vector<std::string> = empty symbol} Is the alphabet of the Automaton represented under a list ({std::vector}) of strings ({std::string}), default set to only empty symbol "*"
     * @param states {std::vector<State> = empty} Is the list of the Automaton's states ({State}), default set to 0 state
     * @param verbose {bool = false} Is an optional parameter (default is false) to give more information about the processing of the method when set to true
     */
    explicit Automaton(std::vector<std::string> alphabet = std::vector<std::string>(), std::vector<State> states = std::vector<State>(), bool verbose = false);
};


#endif //TAI_AUTOMATON_H
