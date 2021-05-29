#include "Token.h"
#include "TokenStream.h"
#include <stdexcept>
#include <cctype>

using std::runtime_error;
using std::out_of_range;
using std::domain_error;
using std::invalid_argument;

void TokenStream::toNextStatement() {
    while (!isEmpty()) {
        Token token{ buffer.top() };
        buffer.pop();
        if (token.getType() == TokenType::statementEnding) {
            return;
        }
    }

    char untilCharacter{ Token::typeToValue(TokenType::statementEnding)[0] };
    for (char ch{ '\0' }; ch != untilCharacter; is >> ch);
}

bool TokenStream::isEmpty() const {
    return buffer.empty();
}

bool TokenStream::reachedNewLine() const {
    return is.peek() == '\n';
}

void TokenStream::putback(Token token) {
    buffer.push(token);
}

TokenStream::TokenStream(istream& is)
    : is{ is } {}

Token TokenStream::get() {
    if (!isEmpty()) {
        Token result{ buffer.top() };
        buffer.pop();
        return result;
    }

    char ch;
    is >> ch;
    try {
        return Token{ Token::characterToType(ch) };
    } catch (const domain_error&) {}
    
    if (isdigit(ch) || ch == '.') {
        string stringValue;
        do {
            stringValue += ch;
        } while (is >> ch && (isdigit(ch) || ch == '.'));
        is.putback(ch);
        return Token{ TokenType::number, stringValue };
    }
    
    if (isalpha(ch)) {
        string stringValue;
        do {
            stringValue += ch;
        } while (is.get(ch) && isalnum(ch));
        is.putback(ch);
        try {
            return Token{ Token::stringToType(stringValue), stringValue };
        } catch (domain_error &) {
            return Token{ TokenType::name, stringValue };
        }
    }
    throw runtime_error{ "bad token" };
}