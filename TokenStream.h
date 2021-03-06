#pragma once

#include "Token.h"
#include <stack>
#include <istream>

using std::stack;
using std::istream;

#pragma warning(push)
#pragma warning(disable: 4820)

class TokenStream {
public:
    TokenStream(istream& is);
    TokenStream& operator=(const TokenStream&) = delete;

    Token get();
    void putback(Token t);
    void toNextStatement();
    bool isEmpty() const;
    bool reachedNewLine() const;

private:
    stack<Token> buffer;
    istream& is;
};

#pragma warning(pop)
