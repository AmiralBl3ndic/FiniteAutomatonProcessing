//
// Created by camboy on 12/05/18.
//

#include "checkers.h"

using namespace std;


/** @description Converts an integer to a std::string using stringstream
 *
 *  @return The given integer casted as a string
 */
std::string int_to_string(int toConvert) {
    stringstream stream;

    stream.str(string()); // Empty the stream
    stream << toConvert;
    return stream.str();
}


/** @description Generates a vector containing digits from 0 to size (excluded) formatted as strings
 *
 *  @param size The size of the vector to generate
 *  @return A vector containing digits from 0 to size (excluded) in increasing order formatted as strings
 */
vector<string> intStringVector(unsigned int size) {
    int i(0);
    vector<string> ret;

    for (i = 0; i < size; i++)
        ret.push_back(int_to_string(i));

    return ret;
}


/** @description Generates a vector containing digits from 0 to 9 formatted as chars
 *
 *  @return A vector containing digits from 0 to 9 formatted as chars
 */
vector<char> digitsVector() {
    int i(0);
    vector<char> ret;

    for (i = 0; i < 10; i++)
        ret.push_back(int_to_string(i)[0]);

    return ret;
}



/** @description Checks if a string is composed only of digits (0 to 9)
 *
 *  @param toCheck The string to check
 *  @return Whether or not the given string is composed only of digits
 */
bool isDigits(const string& toCheck) {
    int i(0);
    vector<char> digits = digitsVector();

    for (i = 0; i < toCheck.size(); i++)
        if (find(digits.begin(), digits.end(), toCheck[i]) == digits.end())
            return false;

    return true;
}


/** @description Checks if a char is a digit
 *
 *  @param toCheck The char to check
 *  @return Whether or not the given char is a digit
 */
bool isDigit(const char toCheck) {
    vector<char> digits = digitsVector();

    return find(digits.begin(), digits.end(), toCheck) != digits.end();
}
