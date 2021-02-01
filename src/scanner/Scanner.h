//
// Created by ich on 1/31/21.
//

#ifndef DOUBLE_TO_FLOAT_SCANNER_H
#define DOUBLE_TO_FLOAT_SCANNER_H

extern "C"
int yylex(void);

#include <string>
#include <unordered_map>

enum readout {TOKEN, TOKEN_STRING};

enum class Token {
    END_OF_FILE,
    INTEGER,
    DOUBLE, FLOAT, MATH_FUNCTION, FLOAT_TYPE, END_OF_STATEMENT, BIN_OPERATOR, DUCK_BILL, STRING, IDENTIFIER,
    MATH_FUNCTION_F, BLANK, NAMESPACE, DEREF, ARGUMENT_LIST, BRACKES, PREPROCESSOR
};

using ScannerOutput = std::pair<Token, std::string>;

class Scanner {
public:
    Scanner();
    virtual ~Scanner() = 0;
    virtual ScannerOutput read();
private:
    std::unordered_map<int, Token> assignment;
};

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}
#endif //DOUBLE_TO_FLOAT_SCANNER_H
