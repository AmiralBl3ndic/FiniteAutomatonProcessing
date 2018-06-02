//
// Created by camboy on 06/05/18.
//

#include "Automaton.h"

using namespace std;


/** @description Default constructor, requires an alphabet vector({std::string}) and a states vector ({State}), it has a verbose option (default set to false) for displaying warnings in case of use of default values
*
*   @param alphabet {std::vector<std::string> = empty symbol} Is the alphabet of the Automaton represented under a list ({std::vector}) of strings ({std::string}), default set to only empty symbol "*"
*   @param states {std::vector<State> = empty} Is the list of the Automaton's states ({State}), default set to 0 state
*   @param verbose {bool = false} Is an optional parameter (default is false) to give more information about the processing of the method when set to true
*/
Automaton::Automaton(std::vector<std::string> alphabet, std::vector<State> states, bool verbose) : _alphabet(alphabet), _states(states), _activeStateIndex(0), _verbose(verbose) { //TODO: test this method
    if (alphabet.empty()) {
        logBasicError(string("(Warning) Initializing alphabet of Automaton with no values, adding the empty symbol \"") + EMPTY_SYMBOL + "\"");

        // Adding the empty symbol '*' to the alphabet so that it contains at least one symbol
        alphabet.push_back(EMPTY_SYMBOL);
        _alphabet = alphabet;

        // TODO: check for the alphabet in the passed states
    }

    if (states.empty()) {
        logBasicError("(Warning) Initializing Automaton with no states");
        _activeStateIndex = -1;
    }
}


/** @description Constructor with file path
 *
 *  @param filePath The absolute (or relative) path to the file to read
 *  @param verbose (optional, default is false) Give more information about the processing of the method when set to true
 */
Automaton::Automaton(const std::string &filePath, bool verbose) {
    int i(0), toAdd(0);
    string addStr, subAdd, outState, trSymbol, targetState;
    stringstream stream;
    int numberOfSymbols(0), numberOfStates(0), numberOfInitialStates(0), numberOfFinalStates(0), numberOfTransitions(0);
    ifstream file;

    _activeStateIndex = 0;
    _verbose = verbose;

    logVerbose("Checking if file can be read...");
    if (!checkFileIntegrity(filePath)) {
        logBasicError("Cannot read the passed file\nAborting");
        return;
    }
    logVerbose("Done");


    file.open(filePath.c_str());

    // Checking if the file has been correctly opened
    if (!file) {
        logBasicError(string("Cannot open file ") + filePath);
        return;
    }


    // Reading the size of the alphabet
    logVerbose("Reading the size of the alphabet...");
    file >> numberOfSymbols;
    _alphabet.reserve(static_cast<unsigned long>(numberOfSymbols)); // Reserving enough space for all the symbols in the alphabet
    logVerbose("Done");

    // Reading the number of states
    logVerbose("Reading the number of states...");
    file >> numberOfStates;
    for (i = 0; i < numberOfStates; i++) {
        stream.str(string());
        stream << i;
        _states.push_back(State(stream.str()));
    }
    logVerbose("Done");

    // Reading the number of initial states
    logVerbose("Reading the number of initial states...");
    file >> numberOfInitialStates;
    // Setting the right states to initial states
    for (i = 0; i < numberOfInitialStates; i++) {
        file >> toAdd;
        _states[toAdd].setInitial();
    }
    logVerbose("Done");

    // Reading the number of final states
    logVerbose("Reading the number of final states...");
    file >> numberOfFinalStates;
    // Setting the right states to final states
    for (i = 0; i < numberOfFinalStates; i++) {
        file >> toAdd;
        _states[toAdd].setFinal();
    }
    logVerbose("Done");

    // Reading the number of transitions
    logVerbose("Reading the number of transitions...");
    file >> numberOfTransitions;
    logVerbose("Done");

    // Reading the transitions
    logVerbose("Reading the transitions...");
    for (i = 0; i < numberOfTransitions; i++) {
        logVerbose("  Reading new transition...");
        file >> addStr;

        // Parsing the line
        Transition::parseFromLine(addStr, outState, trSymbol, targetState);

        // Adding the transition
        cerr << "  "; // For readability in case of error
        if (!addTransition(outState, trSymbol, targetState)) {
            logVerbose("Aborting process, please check your file...");
            return;
        }
        cerr << endl; // To avoid polluting the error flux

        logVerbose("  Done");
    }
    logVerbose("Done");

    updateAlphabet(true);
}


void Automaton::logBasicError(const std::string &error) const {
    if (_verbose)
        cerr << "ERROR: " << error << endl;
}


void Automaton::logVerbose(const std::string &message) const {
    if (_verbose)
        cout << message << endl;
}


/** @description Updates the _alphabet property of an Automaton to match all the symbols of its transitions (from State class), by default this method will not remove the symbol in the alphabet that are not used by the instance
 *
 *  @param forceMatch {bool} If the alphabet has to be cleared to match exactly all the symbols found, default is false
 */
void Automaton::updateAlphabet(bool forceMatch) { // TODO: test this method
    unsigned int i(0), j(0);
    vector<string> stateSymbols;

    // If the alphabet has to be cleared before finding symbols
    if (forceMatch) {
        _alphabet.clear();
        logVerbose("Alphabet cleared");
    }

    // Exploring the states
    for (i = 0; i < _states.size(); i++) {
        // Getting a shortcut to the state's symbols
        stateSymbols = _states[i].getSymbols();

        // Adding the symbols that were found to the alphabet if they are not already in
        for (j = 0; j < stateSymbols.size(); j++)
            if (find(_alphabet.begin(), _alphabet.end(), stateSymbols[i]) != _alphabet.end()) {
                _alphabet.push_back(stateSymbols[i]);
                logVerbose("New symbol found and added to the alphabet");
            }
    }
}


/** @description Checks whether the instance is an asynchronous automaton or not
 *
 *  @return {bool} If the instance is asynchronous
 */
bool Automaton::isAsynchronous() const { // TODO: test this method
    unsigned int i(0), j(0);
    vector<string> stateSymbols;
    bool asynchronous = false;

    for (i = 0; i < _states.size(); i++) {
        stateSymbols = _states[i].getSymbols();

        // Checking if the state contains a transition labeled with the EMPTY_SYMBOL
        if (find(stateSymbols.begin(), stateSymbols.end(), EMPTY_SYMBOL) != stateSymbols.end()) {
            if (!asynchronous) {
                cout << "This automaton is asynchronous... Looking for the transitions labeled with \"" << EMPTY_SYMBOL << "\"" << endl;
                asynchronous = true;
            }

            cout << "The state #" << i << " of this automaton contains a transition labeled with \"" << EMPTY_SYMBOL << "\"" << endl;

            for (j = 0; j < _states[i].getTransitions().size(); j++) {
                if (_states[i].getTransitions()[j].getSymbol() == EMPTY_SYMBOL)
                    cout << "    The transition #" << j << " is responsible for this automaton being asynchronous" << endl;
            }
        }
    }

    return asynchronous;
}


/** @description Adds a transition to the instance by appending it to the right State (in the _states attribute), it does it only if the identifiers are recognized
 *
 *  @param from Identifier of the outgoing state
 *  @param symbol Symbol that labels the transition
 *  @param to Identifier of the target state
 *  @return Whether the transition has been added to the Automaton or not
 */
bool Automaton::addTransition(const std::string &from, const std::string &symbol, const std::string &to) { // TODO: test this method
    bool checkFrom(false), checkTo(false);
    unsigned int i(0);
    int fromID(-1);

    for (i = 0; i < _states.size(); i++) {
        if (_states[i].getIdentifier() == from) {
            checkFrom = true;
            fromID = i;
        }
        if (_states[i].getIdentifier() == to)
            checkTo = true;
    }

    if (checkFrom && checkTo)
        _states[fromID].addTransition(symbol, to);
    else
        logBasicError("Cannot add transition, outgoing or target state (or both) are not recognized");

    return checkFrom && checkTo;
}



/** @description Checks the integrity of a file (if it contains all the needed information) based on its number of lines
 *
 *  @param filePath The path to the file
 *  @return Whether the file can be read to create an automaton or not (based on the number of lines)
 */
bool Automaton::checkFileIntegrity(const std::string &filePath) {
    ifstream file(filePath.c_str());
    string line;
    int neededLines(5), currentLine(0);

    if (!file)
        return false;

    while (getline(file, line) && currentLine < neededLines) {
        ++currentLine;

        if (currentLine == 5) {
            neededLines += static_cast<int>(strtol(line.c_str(), NULL, 10));
        }
    }

    return currentLine == neededLines;
}
/** @description Checks whether the instance is a deterministic automaton or not
*
*  @return {bool} If the instance is deterministic
*/
bool Automaton::isDeterminist() const {
	unsigned int i(0), j(0), flag(0), k(0);

	for (i = 0; i < _states.size(); ++i) {
		if (_states[i].getIsInitial()) 
			flag++;
		if (flag > 1){ // if there is more than one initial state the automaton is non deterministic
			cout << "There is more than one initial state, the automaton is non deterministic\n";
			return false;
		}
		for (j = 0; j < _states[i].getTransitions().size(); ++j) 
			for(k = 0; k < _states[i].getTransitions().size(); ++k)
		{
				// if there is more than one transition with the same symbol the automaton is non deterministic
				if (_states[i].getTransitions()[j].getSymbol() == _states[i].getTransitions()[k].getSymbol()){
					cout << "There is more than one transition with the same symbol " <<_states[i].getTransitions()[j].getSymbol();
					return false;
				}
		}
	}

	return true;
}

/* @description Checks if an automaton is standard or not
*
* @return {bool} If the instance is standard
*/
bool Automaton::isStandard() {
	unsigned int i(0), j(0), flag(0);
	std::string initial_identifier;

	for (i = 0; i < _states.size(); ++i) {
		if(_states[i].getIsInitial()) {
			initial_identifier = _states[i].getIdentifier(); //saving the identifier of the initial state
			for (j = 0; j < _states[i].getTransitions().size(); ++j) {
				//if a transition ends at the inital state then the automaton is not standard
				if (_states[i].getTransitions()[j].getEndStateIdentifier() == initial_identifier)
				{
					cout << "Transition from |"<< _states[i].getTransitions()[j].getEndStateIdentifier()<< "| with symbol " << _states[i].getTransitions()[j].getSymbol() << " ends at the initial state, the automaton is not standard\n";
					return false;
				}
			}
			flag++;
		}
		if (flag > 1){ // if there is more than one initial state the automaton is not standard
			cout << "More than one initial state, the automaton is not standard\n";
			return false;
		}
	}
	logVerbose("Automaton is standard");
	return true;
}
/* @description Standardization of an automaton
*
*/
void Automaton::standardize()
{
	unsigned int i(0), flag(0);

	State tmp("i", true);  // creating a new initial state called i

	bool isFinal = false;

	for(i = 0; i < _states.size(); ++i) {
		if(_states[i].getIsInitial()) {		//checking for the initial state
			_states[i].setInitial(false);	//resteing the initial state

			if(flag == 0)
				tmp.getTransitions() = _states[i].getTransitions(); // copying the transition of the original transition state to the new one
			//if we have more than one initial state then we will add the states of the other initial state to our new initial state tmp
			if (flag > 0) 
				tmp.getTransitions().insert(tmp.getTransitions().end(), _states[i].getTransitions().begin(), _states[i].getTransitions().end());
			
			flag++;
		}
	}
	for (i = 0; i < _states.size(); ++i) {
		if (_states[i].getIsFinal())		
		{
			isFinal = true;	// checking if our initial state is also final
			break;
		}
	}
	tmp.setFinal(isFinal);

	_states.insert(_states.begin(), tmp); //adding our new initial state to the automaton
}



/** @description Checks if all the characters of a string belong to the alphabet of the instance
 *
 *  @param str The string to check
 *
 *  @return {bool} If all the characters of the passed string belong to the alphabet of the instance
 */
bool Automaton::checkStringAlphabet(const std::string &str) const {  // TODO: test this method
    unsigned int i(0), j(0);
    bool charValid;

    for (i = 0; i < str.size(); i++) {
        charValid = false;
        for (j = 0; j < _alphabet.size(); j++)
            if (charToString(str[i]) == _alphabet[i])
                charValid = true;

        if (!charValid)
            return false;
    }

    return true;
}



/** @description Reads a word from keyboard input
  *
  *  @return {std::string} The read string
  */
std::string Automaton::readWord() {  // TODO: test this method
    string str;

    // Clearing the input flux and reading a single word from it
    cin.clear();
    cin >> str;
    cin.clear();

    return str;
}



/** @description Get the stateIndex ({int}) from its identifier
 *
 *  @param identifier The string identifier of the State to identify
 *
 *  @return the corresponding stateIndex, -1 if the identifier is not recognized
 */
int Automaton::getStateIndexFromIdentifier(const std::string &identifier) const {
    unsigned int i(0);

    for (i = 0; i < _states.size(); i++)
        if (_states[i].getIdentifier() == identifier)
            return i;

    return -1;
}



/**  @description Getter for the number of states of the instance
  *
  *  @return The number of states of the instance
  */
int Automaton::numberOfStates() const {
    return static_cast<int>(_states.size());
}


/** @description Tries to recognize a word following the states (State) and transitions (Transition) of the instance Automaton
  *
  *  @param word The word to try to recognize
  *
  *	 @return Whether or not the word has been recognized by the instance Automaton
  */
bool Automaton::recognize(const std::string &word) {
    unsigned int i(0);
    int cpActiveIndex(_activeStateIndex);

    for (i = 0; i < _states.size(); i++) {
        if (_states[i].isInitial()) {
            _activeStateIndex = i;
            if (recognizeRecur(word)) {
                _activeStateIndex = cpActiveIndex;
                return true;
            }
        }
    }

    _activeStateIndex = cpActiveIndex;

    return false;
}


/** @description Recursive method to check if a word is recognized by the instance Automaton
  *
  *  @param word the word to recognize
  *
  *  @return If the passed word has been recognized by the instance Automaton
  */
bool Automaton::recognizeRecur(const std::string &word) {
    unsigned int i(0);
    int cpActiveIndex(_activeStateIndex);
    vector<int> trs_indexes;
    State currentState = _states[_activeStateIndex];

    if (word.empty() && currentState.isFinal())
        return true;


    if (currentState.hasTransition(charToString(word[0]))) {
        trs_indexes = currentState.getTransitionsWithSymbol(charToString(word[0]));

        for (i = 0; i < trs_indexes.size(); i++) {
            _activeStateIndex = getStateIndexFromIdentifier(currentState.getTransitions()[trs_indexes[i]].getEndStateIdentifier());

            if (recognizeRecur(word.substr(1))) {
                _activeStateIndex = cpActiveIndex;
                return true;
            }
        }
    } else {
        // Check for empty symbol labelled transitions
        if (currentState.hasTransition(EMPTY_SYMBOL)) {
            trs_indexes = currentState.getTransitionsWithSymbol(EMPTY_SYMBOL);

            for (i = 0; i < trs_indexes.size(); i++) {
                _activeStateIndex = getStateIndexFromIdentifier(currentState.getTransitions()[trs_indexes[i]].getEndStateIdentifier());

                if (recognizeRecur(word)) {
                    _activeStateIndex = cpActiveIndex;
                    return true;
                }
            }
        }
    }


    return false;
}



/** @description Checks if the Automaton instance is complete (i.e. if it is a complete Automaton)
*
*  @return Whether or not the instance is complete
*/
bool Automaton::isComplete() const {
    unsigned int i(0), j(0);

    for (i = 0; i < _states.size(); i++)
        for (j = 0; j < _alphabet.size(); j++)
            if (!_states[i].hasTransition(_alphabet[j]))
                return false;

    return true;
}


/** @description Makes the Automaton instance complete
*
*/
void Automaton::complete() {
    unsigned int i(0), j(0);
    State trashState("P");

    if (isComplete())
        return;

    // Completing the trash state (adding a transition for each symbol of the alphabet)
    for (i = 0; i < _alphabet.size(); i++)
        trashState.addTransition(_alphabet[i], "P");

    // Adding the new trash state to the list of states
    _states.push_back(trashState);

    // Exploring all the states (except the trash state) to find missing transitions
    for (i = 0; i < _states.size() - 1; i++)
        for (j = 0; j < _alphabet.size(); j++)
            if (!_states[i].hasTransition(_alphabet[j])) {
                _states[i].addTransition(_alphabet[j], "P");
            }
}



