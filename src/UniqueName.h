#ifndef __UNIQUE_NAME_H__
#define __UNIQUE_NAME_H__

#include <string>

class UniqueName
{
public:
    UniqueName(std::string name = "gensym");

    const std::string& getName() const;

private:
    std::string name;

    static unsigned int Counter;
};

#endif    // __UNIQUE_NAME_H__
