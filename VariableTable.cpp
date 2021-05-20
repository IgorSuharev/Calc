#include "VariableTable.h"

#pragma warning(push)
#pragma warning(disable: 4365)
#include <stdexcept>
#pragma warning(pop)

using std::out_of_range;
using std::runtime_error;

double VariableTable::getValue(string name) const {
    try {
        return variables.at(name);
    } catch (const out_of_range&) {
        throw runtime_error{ "undefined variable \"" + name + "\"" };
    }
}

bool VariableTable::isDeclared(string name) const {
    return variables.find(name) != variables.end();
}

double VariableTable::declare(string name, double value) {
    if (isDeclared(name)) {
        throw runtime_error{ name + " re-declaration" };
    }
    variables[name] = value;
    return value;
}

double VariableTable::assign(string name, double value) {
    if (!isDeclared(name)) {
        throw runtime_error{ name + " is not declared" };
    }
    variables[name] = value;
    return value;
}
