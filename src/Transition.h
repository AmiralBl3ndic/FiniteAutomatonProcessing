#ifndef TAI_TRANSITION_H
#define TAI_TRANSITION_H

#include "constants.h"
#include "checkers.h"
#include <string>
#include <iostream>

/** @description This class is a composant of the State class, it represents a Transition from one State to another relying on their identifiers (std::string)
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
	explicit Transition (const std::string& symbol = EMPTY_SYMBOL, const std::string& endStateIdentifier = "trash");


	/** @description Getter for the _symbol attribute
	 *
	 * @return {std::string} The _symbol attribute of the current instance of the class
	 */
	 std::string getSymbol() const;

	 /** @description Getter for the _endStateIdentifier attribute
	 *
	 * @return {std::string} The _endStateIdentifier attribute of the current instance of the class
	 */
	 std::string getEndStateIdentifier() const;


	 friend bool operator==(Transition const&, Transition const&);


    /** @description Parses a line that represents a Transition
     *  @warning This method does not check if the states identifiers are attributed
     *
     *  @param line The line to parse
     *  @param outgoing (Modified parameter) The original state
     *  @param symbol (Modified parameter) The symbol that labels the Transition
     *  @param target (Modified parameter) The target state
     *  @return If the line has been correctly parsed
     */
    static bool parseFromLine(const std::string& line, std::string& outgoing, std::string& symbol, std::string target);
};


#endif //TAI_TRANSITION_H
