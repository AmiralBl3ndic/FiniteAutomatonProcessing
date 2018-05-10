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

}

/** @description Getter for _symbol attributes of the Transition instances composing the _transitions attribute
 *
 *  @return {std::vector<std::string>} The list of all the symbols of the transitions from this state
 */
std::vector<std::string> State::getSymbols() const {
    vector<string> ret;
    int i(0);

    for (i = 0; i < _transitions.size(); i++) {
        if (find(ret.begin(), ret.end(), _transitions[i].getSymbol()) != ret.end())
            ret.push_back(_transitions[i].getSymbol());
    }

    return ret;
}
