#ifndef TAI_STATE_H
#define TAI_STATE_H

#include <string>
#include <vector>
#include <cstdlib>
#include "Transition.h"


class State {
private:
	std::string _identifier;
	bool _isInitial;
	bool _isFinal;
	std::vector<Transition> _transitions;
	
public:
	explicit State (const std::string& identifier, bool isInitial = false, bool isFinal = false);
};


#endif //TAI_STATE_H
