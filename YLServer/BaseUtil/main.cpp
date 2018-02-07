#include <iostream>
#include <list>

#include "util/SimpleBuffer.h"
#include "network/test.h"
using namespace youliao::util;
int main()
{
    SimpleBuffer *simpleBuffer = new SimpleBuffer;

    char str[4] = "123";
    char str2[4];

    simpleBuffer->write(str, 4);

    simpleBuffer->read(str2, 4);

    std::cout << str2 << std::endl;

    int i = 9, j = 10;
    simpleBuffer->write(&i, 4);
    simpleBuffer->write(&j, 4);

    simpleBuffer->read(&j, 4);
    simpleBuffer->read(&i, 4);
    std::cout << i << " " << j << std::endl;

    typedef struct {
        int i = 10;
        int j = 20;
        char str[3] = "12";
    }T;

    T t;
    T tt;
    tt.j = 200;
    simpleBuffer->write(&t, sizeof(T));
    simpleBuffer->read(&tt, sizeof(T));

    std::cout << tt.j;


    return 0;
}