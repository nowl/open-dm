#ifndef __FILE_H__
#define __FILE_H__

#include <cstdio>

class File
{
public:
    File(const char *name, const char *type)
    {
        // TODO: throw exception
        fp = fopen(name, type);
    }

    ~File()
    {
        fclose(fp);
    }

    FILE *getFP()
    {
        return fp;
    }

private:
    FILE *fp;
};

#endif  // __FILE_H__
