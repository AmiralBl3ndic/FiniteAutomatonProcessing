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


	bool transitionExists(const Transition&);

	
public:
	explicit State (const std::string& identifier, bool isInitial = false, bool isFinal = false);


	/** @description Getter for _symbol attributes of the Transition instances composing the _transitions attribute
	 *
	 *  @return {std::vector<std::string>} The list of all the symbols of the transitions from this state
	 */
	std::vector<std::string> getSymbols() const;


	/** @description Getter for the _transition attribute
	 *
	 *  @return {std::vector<Transition>} List (std::vector) of the transitions (Transition) of the instance
	 */
	std::vector<Transition> getTransitions() const;


	/** @description Getter for the _identifier attribute
	 *
	 * 	@return The value of the _identifier attribute of the instance
	 */
	std::string getIdentifier();



    /** @description Part setter for the _transitions attribute: this method allows a `push_back()` to the _transitions attribute
      * @warning Do not use this method if you are not sure the passed symbol is included in the alphabet of the associated Automaton instance
      * @warning Do not use this method if you are not sure the passed identifier is attributed for the associated Automaton instance
      * @warning To allow a safer use of this method, use the `addTransition()` method of the Automaton class
      *
      * @param symbol The symbol that labels the Transition instance
      * @param identifier The identifier of the arrival State instance
      */
    void addTransition(const std::string& symbol, const std::string& identifier);
};


#endif //TAI_STATE_H
