
#include "netlib.h"
int main() {


    netlib_init();

    netlib_listen("127.0.0.1", 8001, nullptr, nullptr);

    netlib_eventloop();

    netlib_destroy();

    return 0;
}