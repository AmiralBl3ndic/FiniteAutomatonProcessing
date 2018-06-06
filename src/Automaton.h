//
// Created by camboy on 06/05/18.
//

#ifndef TAI_AUTOMATON_H
#define TAI_AUTOMATON_H


#include "constants.h"
#include "State.h"
#include "Transition.h"
#include "checkers.h"
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstddef>


/** @description This class is the representation of an Automaton : it contains a list of states (State) which all contain a list of transitions (Transition)
 */
class Automaton {
private:

	std::vector<std::string> _alphabet;
	std::vector<State> _states;
	int _activeStateIndex;
	bool _verbose;

	Automaton(const Automaton*);


	void logBasicError(const std::string& error) const;


	void logVerbose(const std::string& message) const;


	/** @description Adds a transition to the instance by appending it to the right State (in the _states attribute), it does it only if the identifiers are recognized
	 *
	 *  @param from Identifier of the outgoing state
	 *  @param symbol Symbol that labels the transition
	 *  @param to Identifier of the target state
	 *  @return Whether the transition has been added to the Automaton or not
	 */
	bool addTransition(const std::string& from, const std::string& symbol, const std::string& to);


    /** @description Checks the integrity of a file (if it contains all the needed information) based on its number of lines
     *
     *  @param filePath The path to the file
     *  @return Whether the file can be read to create an automaton or not (based on the number of lines)
     */
	bool checkFileIntegrity(const std::string& filePath);


	/** @description Get the stateIndex ({int}) from its identifier
	 *
	 *  @param identifier The string identifier of the State to identify
	 *
	 *  @return the corresponding stateIndex, -1 if the identifier is not recognized
	 */
	 int getStateIndexFromIdentifier(const std::string& identifier) const;


	 /** @description Recursive method to check if a word is recognized by the instance Automaton
	  *
	  *  @param word the word to recognize
	  *
	  *  @return If the passed word has been recognized by the instance Automaton
	  */
	 bool recognizeRecur(const std::string& word);

	 /** @description Transform final states into non-final states and vice-versa
 	 *
 	 */
	 void makeComplementary();

public:

    /** @description Default constructor, requires an alphabet vector({std::string}) and a states vector ({State}), it has a verbose option (default set to false) for displaying warnings in case of use of default values
     *
     * @param alphabet {std::vector<std::string> = empty symbol} Is the alphabet of the Automaton represented under a list ({std::vector}) of strings ({std::string}), default set to only empty symbol "*"
     * @param states {std::vector<State> = empty} Is the list of the Automaton's states ({State}), default set to 0 state
     * @param verbose {bool = false} Is an optional parameter (default is false) to give more information about the processing of the method when set to true
     */
    explicit Automaton(std::vector<std::string> alphabet = std::vector<std::string>(), std::vector<State> states = std::vector<State>(), bool verbose = false);


	/** @description Constructor with  path
	 *
	 *  @param filePath The absolute (or relative) path to the file to read
	 *  @param verbose (optional, default is false) Give more information about the processing of the method when set to true
	 */
    explicit Automaton(const std::string& filePath, bool verbose = false);


	/** @description Updates the _alphabet property of an Automaton to match all the symbols of its transitions (from State class), by default this method will not remove the symbol in the alphabet that are not used by the instance
	 *
	 *  @param forceMatch {bool} If the alphabet has to be cleared to match exactly all the symbols found, default is false
	 */
    void updateAlphabet(bool forceMatch = false);


    /** @description Checks whether the instance is an asynchronous automaton or not
     *
     *  @return {bool} If the instance is asynchronous
     */
    bool isAsynchronous() const;


    /** @description Checks if all the characters of a string belong to the alphabet of the instance
     *
     *  @param str The string to check
     *
     *  @return {bool} If all the characters of the passed string belong to the alphabet of the instance
     */
     bool checkStringAlphabet(const std::string& str) const;


     /** @description Reads a word from keyboard input
      *
      *  @return {std::string} The read string
      */
     static std::string readWord();


     /** @description Getter for the number of states of the instance
      *
      *  @return The number of states of the instance
      */
     int numberOfStates() const;


     /** @description Tries to recognize a word following the states (State) and transitions (Transition) of the instance Automaton
      *
      *  @param word The word to try to recognize
      *
      *	 @return Whether or not the word has been recognized by the instance Automaton
      */
      bool recognize(const std::string& word);


     /** @description Checks if an automaton is deterministic or not
      *
      * @return {bool} If the instance is deterministic
      */
	  bool isDeterminist() const;


	 /** @description Checks if an automaton is standard or not
	  *
  	  * @return {bool} If the instance is standard
	  */
	  bool isStandard();


	  /** @description Standardizes an Automaton instance
	   *
	   */
	  void standardize();


	  /** @description Checks if the Automaton instance is complete (i.e. if it is a complete Automaton)
	   *
	   *  @return Whether or not the instance is complete
	   */
	  bool isComplete() const;


	  /** @description Makes the Automaton instance complete
	   *
	   */
	  void complete();

	  /** @description Create a complementary automaton
      *
      *   @return The complementary automaton
      */
	  Automaton complementaryAutomaton() const;


	  /** @description Display an automaton
	  *
	  */
	  void display();
	
	
		/// MAKING A NON-ACCESSIBLE STATE FREE AUTOMATON
	/** @description Suppresses all the Non-Accessible States and their Transitions
	*
	*/
	void MakeNonAccessibleState_Free_Automaton();

	/** @description Create an automaton without Non-Accessible State
	*
	*   @return The automaton without Non-Accessible State
	*/
	Automaton SuppressNonAccessibleStates() const;



	/// MINIMIZING AN AUTOMATON
	/** @description Makes the Automaton instance Minimized
	*
	*/
	void MakeMinimized();

	/** @description Create a Minimized automaton
	*
	*   @return The Minimized automaton
	*/
	Automaton MinimizedAutomaton() const;
};


#endif //TAI_AUTOMATON_H
