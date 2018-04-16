#include <iostream>
#include "server.h"

#include <sstream>
int main() {

    http::server::server s("127.0.0.1", "8080", "/home/liuzheng");

    s.run();



    return 0;
}