#include <iostream>
#include <string>
#include <vector>
#include "UtilPdu.h"

using namespace std;

/********test YLSimplerBuffer***************/

void testSimplerBuffer()
{
    YLSimpleBuffer ylSimpleBuffer;

    for(int i = 0; i < 4; ++i)
    {
        ylSimpleBuffer.write((void*)&i, sizeof(int));
    }

    for(int i = 0; i < 4; ++i)
    {
        int n;
        ylSimpleBuffer.read((void*)&n, sizeof(int));
        cout << n << endl;
    }

}

int main() {
    testSimplerBuffer();
    return 0;
}