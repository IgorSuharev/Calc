#pragma once

#include <map>
#include <string>

using std::map;
using std::string;

class VariableTable {
public:
    double getValue(string name) const;
    bool isDeclared(string name) const;
    double declare(string name, double value);
    double assign(string name, double value);

private:
    map<string, double> variables;
};
