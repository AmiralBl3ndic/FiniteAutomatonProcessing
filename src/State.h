#ifndef TAI_STATE_H
#define TAI_STATE_H

#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm> // So that we can easily find values inside our vectors
#include "Transition.h"

/** @description This class represents an Automaton's State, it contains a list of transitions (Transition)
 */
class State {
private:
	std::string _identifier;
	bool _isInitial;
	bool _isFinal;
	std::vector<Transition> _transitions;
	
public:
	explicit State (const std::string& identifier, bool isInitial = false, bool isFinal = false);


	/** @description Getter for _symbol attributes of the Transition instances composing the _transitions attribute
	 *
	 *  @return {std::vector<std::string>} The list of all the symbols of the transitions from this state
	 */
	std::vector<std::string> getSymbols() const;
};


#endif //TAI_STATE_H
