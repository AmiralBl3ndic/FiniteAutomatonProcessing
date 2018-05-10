//
// Created by camboy on 06/05/18.
//

#ifndef TAI_AUTOMATON_H
#define TAI_AUTOMATON_H


#include "State.h"
#include <string>
#include <vector>


class Automaton {
private:
	std::vector<std::string> _alphabet;
	std::vector<State> _states;
	int _activeStateIndex;


public:
};


#endif //TAI_AUTOMATON_H
