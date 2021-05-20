#define _USE_MATH_DEFINES

#pragma warning(push)
#pragma warning(disable: 4365)
#include <cmath>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <climits>
#pragma warning(pop)

#include "Token.h"
#include "TokenStream.h"
#include "VariableTable.h"
#include "Parser.h"


using std::numeric_limits;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::runtime_error;
using std::exception;

const string prompt{ ">>> " };
const string resultPrefix{ "  = " };

inline void keepWindowOpen(string s) {
    if (s == "") {
        return;
    }
    cin.clear();
    cin.ignore(120, '\n');
    for (string ss{ "" }; ss != s; cin >> ss) {
        cout << "Please enter " << s << " to exit" << endl;
    }
    return;
}

void runCalculator(TokenStream& tokenStream, const VariableTable& variableTable) {
    Parser parser{ tokenStream, variableTable };

    cout << prompt;
    while (true) {
        try {
            double result{ parser.statement() };
            if (parser.reachedTerminalToken()) {
                return;
            }
            cout << resultPrefix << result << endl;
        } catch (exception& e) {
            cerr << "Error: " << e.what() << endl;
            tokenStream.toNextStatement();
        }
        if (tokenStream.reachedNewLine()) {
            cout << prompt;
        }
    }
}

int main() try {
    TokenStream tokenStream{cin};
    VariableTable variableTable;
    variableTable.declare("pi", M_PI);
    variableTable.declare("e", M_E);

    cout << "Welcome to the calculator program!" << endl;
    cout << "Enter expressions with float-point numbers." << endl;
    cout << "End each statement with \"" << Token::typeToValue(TokenType::statementEnding) << "\" character." << endl;
    cout << "For quit the program, enter \"" << Token::typeToValue(TokenType::exit) << "\"." << endl;

    runCalculator(tokenStream, variableTable);
    
    keepWindowOpen("~~");
    return EXIT_SUCCESS;

} catch (exception &e) {
    cerr << "Error: " << e.what() << endl;
    keepWindowOpen("~~");
    return EXIT_FAILURE;

} catch (...) {
    cerr << "Unhandled exception!" << endl;
    keepWindowOpen("~~");
    return EXIT_FAILURE + 1;
}
