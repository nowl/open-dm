#include <sstream>
#include <cstdio>

#include "UniqueName.h"

using namespace std;

unsigned int UniqueName::Counter = 0;

UniqueName::UniqueName(string name)
{
    stringstream ss;
    ss << "__" << name << "-" << Counter;
    this->name = ss.str();

    Counter++;
}

const std::string&
UniqueName::getName() const
{    
    return name;
}
