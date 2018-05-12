//
// Created by camboy on 12/05/18.
//

#ifndef TAI_CHECKERS_H
#define TAI_CHECKERS_H


#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "constants.h"


/** @description Converts an integer to a std::string using stringstream
 *
 *  @return The given integer casted as a string
 */
std::string int_to_string(int);


/** @description Generates a vector containing digits from 0 to size (excluded) formatted as strings
 *
 *  @param size The size of the vector to generate
 *  @return A vector containing digits from 0 to size (excluded) in increasing order formatted as strings
 */
std::vector<std::string> intStringVector(unsigned int size);


/** @description Generates a vector containing digits from 0 to 9 formatted as chars
 *
 *  @return A vector containing digits from 0 to 9 formatted as chars
 */
std::vector<char> digitsVector();


/** @description Checks if a string is composed only of digits (0 to 9)
 *
 *  @return Whether or not the given string is composed only of digits
 */
bool isDigits(const std::string&);


/** @description Checks if a char is a digit
 *
 *  @param toCheck The char to check
 *  @return Whether or not the given char is a digit
 */
bool isDigit(char toCheck);


#endif //TAI_CHECKERS_H
