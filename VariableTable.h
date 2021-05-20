#pragma once

#pragma warning(push)
#pragma warning(disable: 4365)
#include <map>
#include <string>
#pragma warning(pop)

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
