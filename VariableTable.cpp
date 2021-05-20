#include "VariableTable.h"
#include <stdexcept>

using std::out_of_range;
using std::runtime_error;

double VariableTable::getValue(string name) {
    try {
        return variables.at(name);
    } catch (const out_of_range&) {
        throw runtime_error("undefined variable \"" + name + "\"");
    }
}

bool VariableTable::isDeclared(string name) {
    return variables.find(name) != variables.end();
}

double VariableTable::defineName(string name, double value) {
    if (isDeclared(name)) {
        throw runtime_error(name + " re-declaration");
    }
    variables[name] = value;
    return value;
}

double VariableTable::assign(string name, double value) {
    if (!isDeclared(name)) {
        throw runtime_error(name + " is not declared");
    }
    variables[name] = value;
    return value;
}
