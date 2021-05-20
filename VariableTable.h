#pragma once

#include <map>
#include <string>

using std::map;
using std::string;

class VariableTable {
public:
    double getValue(string name);
    bool isDeclared(string name);
    double defineName(string name, double value);
    double assign(string name, double value);

private:
    map<string, double> variables;
};

