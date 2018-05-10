//
// Created by camboy on 06/05/18.
//

#ifndef TAI_AUTOMATON_H
#define TAI_AUTOMATON_H


#include "constants.h"
#include "State.h"
#include <string>
#include <vector>
#include <algorithm>


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


	/** @description Updates the _alphabet property of an Automaton to match all the symbols of its transitions (from State class), by default this method will not remove the symbol in the alphabet that are not used by the instance
	 *
	 *  @param forceMatch {bool} If the alphabet has to be cleared to match exactly all the symbols found, default is false
	 */
    void updateAlphabet(bool forceMatch = false);
};


#endif //TAI_AUTOMATON_H
