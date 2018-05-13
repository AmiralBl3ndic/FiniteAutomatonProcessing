//
// Created by camboy on 06/05/18.
//

#include "State.h"


using namespace std;


/** @description This method is not implemented yet
 *
 * @param identifier
 * @param isInitial
 * @param isFinal
 */
State::State(const std::string &identifier, const bool isInitial, const bool isFinal) : _identifier(identifier), _isInitial(isInitial), _isFinal(isFinal) {
    // TODO: implement this method
}


/** @description Getter for _symbol attributes of the Transition instances composing the _transitions attribute
 *
 *  @return {std::vector<std::string>} The list of all the symbols of the transitions from this state
 */
std::vector<std::string> State::getSymbols() const { // TODO: test this method
    vector<string> ret;
    unsigned int i(0);

    for (i = 0; i < _transitions.size(); i++) {
        if (find(ret.begin(), ret.end(), _transitions[i].getSymbol()) != ret.end())
            ret.push_back(_transitions[i].getSymbol());
    }

    return ret;
}


/** @description Getter for the _transition attribute
 *
 *  @return {std::vector<Transition>} List (std::vector) of the transitions (Transition) of the instance
 */
std::vector<Transition> State::getTransitions() const {
    return _transitions;
}


/** @description Part setter for the _transitions attribute: this method allows a `push_back()` to the _transitions attribute
  * @warning Do not use this method if you are not sure the passed symbol is included in the alphabet of the associated Automaton instance
  * @warning Do not use this method if you are not sure the passed identifier is attributed for the associated Automaton instance
  * @warning To allow a safer use of this method, use the `addTransition()` method of the Automaton class
  *
  * @param symbol The symbol that labels the Transition instance
  * @param identifier The identifier of the arrival State instance
  */
void State::addTransition(const std::string &symbol, const std::string &identifier) {
    Transition toAdd(symbol, identifier);

    if (!transitionExists(toAdd))
        _transitions.push_back(toAdd);
}



bool State::transitionExists(Transition ref) const {
    return find(_transitions.begin(), _transitions.end(), ref) != _transitions.end();
}


std::string State::getIdentifier() {
    return _identifier;
}


/** @description Setter for _isInitial attribute
 *
 *  @param setter The value to set the attribute to
 */
void State::setInitial(bool setter) {
    _isInitial = setter;
}


/** @description Setter for _isFinal attribute
 *
 *  @param setter The value to set the attribute to
 */
void State::setFinal(bool setter) {
    _isFinal = setter;
}

