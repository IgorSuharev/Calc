#pragma once

#include <vector>
#include <string>
#include <utility>

using std::string;
using std::vector;
using std::pair;

enum class TokenType {
    number,
    name,
    add, substract, multiply, divide, modulo,
    factorial,
    leftParenthesis, rightParenthesis,
    equal,
    statementEnding,
    calculationEnding,
    exit,
    declarationKeyword,
    bad,
    empty
};

#pragma warning(push)
#pragma warning(disable: 4820)

class Token {
public:
    Token(TokenType type);
    Token(TokenType type, string value);

    double toNumeric() const;
    TokenType getType() const;
    string getValue() const;

    static bool hasCharacterValue(TokenType type);
    static string typeToValue(TokenType type);
    static TokenType characterToType(char ch);
    static TokenType stringToType(const string& str);

private:
    TokenType type;
    string value;
    static const vector<pair<TokenType, char>> typeToCharacter_pairs;
    static const vector<pair<TokenType, string>> typeToString_pairs;
};

#pragma warning(pop)
