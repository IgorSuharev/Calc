#pragma once

#include "TokenStream.h"
#include "VariableTable.h"

#pragma warning(push)
#pragma warning(disable: 4820)

class Parser {
public:
    Parser(TokenStream& tokenStream, const VariableTable& variableTable);
    double expression();
    double primary();
    double secondary();
    double term();
    double declaration();
    
    double statement();
    double assignment();

    bool reachedTerminalToken();
private:
    TokenStream& tokenStream;
    VariableTable variableTable;
    bool field_reachedTerminalToken;
    bool field_isReady;
};

#pragma warning(pop)
