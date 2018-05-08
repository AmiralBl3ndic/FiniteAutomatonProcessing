//
// Created by camboy on 06/05/18.
//

#include "State.h"

/** @description
 *
 * @param identifier
 * @param isInitial
 * @param isFinal
 */
State::State(const std::string &identifier, const bool isInitial, const bool isFinal) : _identifier(identifier), _isInitial(isInitial), _isFinal(isFinal) {

}
