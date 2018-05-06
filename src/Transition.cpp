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
};

