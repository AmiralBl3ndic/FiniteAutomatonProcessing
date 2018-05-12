//
// Created by camboy on 06/05/18.
//

#include "Transition.h"

/** @description Default constructor
 *
 *  @param symbol The symbol that labels the Transition. By default: "*" (empty word)
 *  @param endStateIdentifier The identifier of the State on which points the transition. By default: "trash" (trash state)
*/
Transition::Transition(const std::string &symbol, const std::string &endStateIdentifier) : _symbol(symbol), _endStateIdentifier(endStateIdentifier){
	//ctor
}


/** @description Getter for the _symbol attribute
 *
 * @return {std::string} The _symbol attribute of the current instance of the class
 */
std::string Transition::getSymbol() const { // TODO: test this method
    return _symbol;
}

bool operator==(Transition const &tr1, Transition const &tr2) {
    return (tr1._symbol == tr2._symbol && tr1._endStateIdentifier == tr2._endStateIdentifier);
};

