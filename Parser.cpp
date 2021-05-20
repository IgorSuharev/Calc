#include "Parser.h"
#include "Math.h"
#include <stdexcept>
#include <cmath>

//  Grammar.
//  statement:
//      exit
//      declaration statementEnding
//      assignment statementEnding
//      expression statementEnding
//  exit:
//      "quit"
//  statementEnding:
//      ";"
//  declaration:
//      declarationKeyword name "=" expression
//  declarationKeyword:
//      "let"
//  name:
//      @ first character is letter of latin alphabet;
//      following characters are letters of latin alphabet or digits; @
//  assignment:
//      name "=" expression
//  expression:
//      term
//      expression "+" term
//      expression "-" term
//  term:
//      secondary
//      term "*" secondary
//      term "/" secondary
//      term "%" secondary
//  secondary:
//      primary
//      secondary "!"
//  primary:
//      number
//      name
//      "(" expression ")"
//      "+" primary
//      "-" primary                 // for negative numbers too
//  number:
//      @ is read by std::cin to double variable @

using std::runtime_error;
using std::numeric_limits;

Parser::Parser(TokenStream& tokenStream, const VariableTable& variableTable)
    : tokenStream{ tokenStream }, variableTable{ variableTable }, field_reachedTerminalToken{ false }, field_isReady{ true } {}

#pragma warning(push)
#pragma warning(disable: 4061 4062)

double Parser::statement() {
    Token token{ tokenStream.get() };
    double result{ 0 };

    switch (token.getType()) {
    case TokenType::exit:
        field_reachedTerminalToken = true;
        return result;
    case TokenType::declarationKeyword:
        tokenStream.putback(token);
        result = declaration();
        break;
    case TokenType::name: {
        Token token2{ tokenStream.get() };
        tokenStream.putback(token2);
        tokenStream.putback(token);
        if (token2.getType() == TokenType::equal) {
            result = assignment();
        } else {
            result = expression();
        }
        break;
    }
    default:
        tokenStream.putback(token);
        result = expression();
    }
    token = tokenStream.get();
    if (token.getType() != TokenType::statementEnding) {
        tokenStream.putback(token);
        throw runtime_error{ Token::typeToValue(TokenType::statementEnding) + " expected" };
    }
    return result;
}

double Parser::declaration() {
    // read declaration keyword
    Token token{ tokenStream.get() };
    if (token.getType() != TokenType::declarationKeyword) {
        tokenStream.putback(token);
        throw runtime_error{ Token::typeToValue(TokenType::declarationKeyword) + " expected" };
    }

    // read variable name
    token = tokenStream.get();
    if (token.getType() != TokenType::name) {
        tokenStream.putback(token);
        throw runtime_error{ "variable name expected" };
    }
    string name{ token.getValue() };

    // read equal sign
    token = tokenStream.get();
    if (token.getType() != TokenType::equal) {
        tokenStream.putback(token);
        throw runtime_error{ Token::typeToValue(TokenType::equal) + " expected" };
    }

    return variableTable.declare(name, expression());
}

double Parser::assignment() {
    // read variable name
    Token token{ tokenStream.get() };
    if (token.getType() != TokenType::name) {
        tokenStream.putback(token);
        throw runtime_error{ "variable name expected" };
    }
    string name{ token.getValue() };

    // read equal sign
    token = tokenStream.get();
    if (token.getType() != TokenType::equal) {
        tokenStream.putback(token);
        throw runtime_error{ Token::typeToValue(TokenType::equal) + " expected" };
    }
    return variableTable.assign(name, expression());
}

double Parser::expression() {
    double left{ term() };
    Token token{ tokenStream.get() };

    while (true) {
        switch (token.getType()) {
        case TokenType::add:
            left += term();
            break;
        case TokenType::substract:
            left -= term();
            break;
        default:
            tokenStream.putback(token);
            return left;
        }
        token = tokenStream.get();
    }
}

double Parser::term() {
    double left{ secondary() };
    Token token{ tokenStream.get() };

    while (true) {
        switch (token.getType()) {
        case TokenType::multiply:
            left *= secondary();
            break;
        case TokenType::divide:
        {
            double right{ secondary() };
            if (right == 0) {
                left = numeric_limits<double>().quiet_NaN();
            } else {
                left /= right;
            }
            break;
        }
        case TokenType::modulo:
            left = fmod(left, secondary());
            break;
        default:
            tokenStream.putback(token);
            return left;
        }
        token = tokenStream.get();
    }
}

double Parser::secondary() {
    double left{ primary() };
    Token token{ tokenStream.get() };

    while (true) {
        switch (token.getType()) {
        case TokenType::factorial:
            if (isnan(left) || left < 0) {
                left = isnan(left);
            } else {
                left = static_cast<double>(Math::factorial(static_cast<unsigned>(left)));
            }
            break;
        default:
            tokenStream.putback(token);
            return left;
        }
        token = tokenStream.get();
    }
}

double Parser::primary() {
    Token token{ tokenStream.get() };

    switch (token.getType()) {
    case TokenType::leftParenthesis:
    {
        double expr{ expression() };
        token = tokenStream.get();
        if (token.getType() != TokenType::rightParenthesis) {
            tokenStream.putback(token);
            throw runtime_error{ "')' expected" };
        }
        return expr;
    }
    case TokenType::number:
        return token.toNumeric();
    case TokenType::name:
        return variableTable.getValue(token.getValue());
    case TokenType::add:
        return +primary();
    case TokenType::substract:
        return -primary();
    default:
        tokenStream.putback(token);
        throw runtime_error{ "primary expected" };
    }
}

bool Parser::reachedTerminalToken() const {
    return field_reachedTerminalToken;
}

#pragma warning(pop)
