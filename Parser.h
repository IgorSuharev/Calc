#pragma once

#include "TokenStream.h"
#include "VariableTable.h"

#pragma warning(push)
#pragma warning(disable: 4820)

class Parser {
public:
    Parser(TokenStream& tokenStream, const VariableTable& variableTable);
    
    double statement();
    double declaration();
    double assignment();
    double expression();
    double term();
    double secondary();
    double primary();

    bool reachedTerminalToken() const;
private:
    TokenStream& tokenStream;
    VariableTable variableTable;
    bool field_reachedTerminalToken;
    bool field_isReady;
};

#pragma warning(pop)
