#include <iostream>
#include "DBPool.h"
int main() {

   if ( DBManager::instance() == nullptr)
       return -1;


    return 0;
}