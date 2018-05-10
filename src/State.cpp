//
// Created by camboy on 06/05/18.
//

#include "State.h"


using namespace std;


/** @description
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
    int i(0);

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
