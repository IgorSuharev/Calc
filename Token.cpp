#include "Token.h"

#include <string>
#include <stdexcept>
#include <cmath>
#include <utility>
#include <algorithm>
#include <climits>

using std::domain_error;
using std::find;
using std::find_if;
using std::string;
using std::stod;
using std::numeric_limits;

Token::Token(TokenType type)
: type{type} {
    value = typeToValue(type);
}

Token::Token(TokenType type, string value)
: type{type}, value{value} {}

double Token::toNumeric() const try {
    return stod(value);
} catch (const std::exception&) {
    throw domain_error("\"" + value + "\" is not a real number record");
}

TokenType Token::getType() const {
    return type;
}

string Token::getValue() const {
    return value;
}

const vector<pair<TokenType, char>> Token::typeToCharacter_pairs = {
    {TokenType::add, '+'},
    {TokenType::substract, '-'},
    {TokenType::multiply, '*'},
    {TokenType::divide, '/'},
    {TokenType::modulo, '%'},
    {TokenType::factorial, '!'},
    {TokenType::leftParenthesis, '('},
    {TokenType::rightParenthesis, ')'},
    {TokenType::equal, '='},
    {TokenType::add, '+'},
    {TokenType::statementEnding, ';'},
    {TokenType::calculationEnding, '\n'}
};

const vector<pair<TokenType, string>> Token::typeToString_pairs = {
    {TokenType::exit, "quit"},
    {TokenType::declarationKeyword, "let"},
    {TokenType::empty, ""}
};

bool Token::hasCharacterValue(TokenType type) {
    auto searchAmongCharactersPredicate = [type](const pair<TokenType, char>& p) -> bool {
        return p.first == type;
    };
    auto itChar = find_if(typeToCharacter_pairs.begin(), typeToCharacter_pairs.end(), searchAmongCharactersPredicate);
    return itChar != typeToCharacter_pairs.end();
}

string Token::typeToValue(TokenType type) {
    auto searchAmongCharactersPredicate = [type](const pair<TokenType, char>& pair) -> bool {
        return pair.first == type;
    };
    auto itChar = find_if(Token::typeToCharacter_pairs.begin(), Token::typeToCharacter_pairs.end(), searchAmongCharactersPredicate);
    if (itChar != Token::typeToCharacter_pairs.end()) {
        return string() + itChar->second;
    }

    auto searchAmongStringsPredicate = [type](const pair<TokenType, string>& pair) -> bool {
        return pair.first == type;
    };
    auto itString = find_if(Token::typeToString_pairs.begin(), Token::typeToString_pairs.end(), searchAmongStringsPredicate);
    if (itString != Token::typeToString_pairs.end()) {
        return itString->second;
    }
    throw domain_error("given token type has no definite value");
}

TokenType Token::characterToType(char ch) {
    auto searchPredicate =
        [ch](const pair<TokenType, char>& pair) -> bool {
            return pair.second == ch;
        };
    auto it = find_if(typeToCharacter_pairs.begin(), typeToCharacter_pairs.end(), searchPredicate);
    if (it == typeToCharacter_pairs.end()) {
        throw domain_error(string("there is not a token type that represents the character \"") + ch + "\"");
    } else {
        return it->first;
    }
}

TokenType Token::stringToType(const string& str) {
    auto searchPredicate =
        [str](const pair<TokenType, string>& p) -> bool {
            return p.second == str;
        };
    auto it = find_if(typeToString_pairs.begin(), typeToString_pairs.end(), searchPredicate);
    if (it == typeToString_pairs.end()) {
        throw domain_error(string("there is not a token type that represents the string \"") + str + "\"");
    } else {
        return it->first;
    }
}
