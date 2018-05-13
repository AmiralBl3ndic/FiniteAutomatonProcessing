//
// Created by camboy on 06/05/18.
//

#include "Transition.h"

using namespace std;

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
}


/** @description Parses a line that represents a Transition
 *  @warning This method does not check if the states identifiers are attributed
 *
 *  @param line The line to parse
 *  @param outgoing (Modified parameter) The original state
 *  @param symbol (Modified parameter) The symbol that labels the Transition
 *  @param target (Modified parameter) The target state
 *  @return If the line has been correctly parsed
 */
bool Transition::parseFromLine(const std::string &line, std::string &outgoing, std::string &symbol, std::string target) {
    int i(0);

    // Emptying the strings
    outgoing = "";
    symbol = "";
    target = "";

    if (!line.empty() && isDigit(line[0])) {
        // Reading the first part (outgoing state identifier) of the line
        while (i < line.size() && isDigit(line[i]))
            outgoing.push_back(line[i++]);

        // Checking if the line can still be read
        if (i >= line.size() - 2) {
            outgoing = ""; // Clearing the result to avoid any errors outside the function
            cerr << "ERROR: cannot parse line \"" << line << "\"" << endl;
            return false;
        }

        // Reading the symbol of the transition
        while (i < line.size() && !isDigit(line[i]))
            symbol.push_back(line[i++]);

        // Checking if the line can still be read
        if (i >= line.size() - 1) {
            outgoing = "";
            symbol = "";
            cerr << "ERROR cannot parse line \"" << line << "\"" << endl;
            return false;
        }

        // Reading the last part (target state identifier) of the line
        while (i < line.size() && isDigit(line[i]))
            target.push_back(line[i++]);
    }

    return true;
};

