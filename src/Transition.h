#ifndef TAI_TRANSITION_H
#define TAI_TRANSITION_H

#include <string>
#include <iostream>

/** @description This class is a composant of the State class, it represents a Transition from one State to another relying on their identifiers (std::string)
 *
 */
class Transition {
	
	private:
		std::string _symbol;
		std::string _endStateIdentifier;
		
	public:
		/** @description Default constructor
		 *
		 *  @param symbol The symbol that labels the Transition. By default: "*" (empty word)
		 *  @param endStateIdentifier The identifier of the State on which points the transition. By default: "trash" (trash state)
		 */
		explicit Transition (const std::string& symbol = "*", const std::string& endStateIdentifier = "trash");
};


#endif //TAI_TRANSITION_H
