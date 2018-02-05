//
// Created by liuzheng on 18-2-3.
//

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/time.h>
#include <map>
#include <cstring>
#include <list>


#ifdef __GNUC__
#include <ext/hash_map>
#else
#include <hash_map>
#endif

#define log(info, args...) printf(info, args)


inline uint64_t get_tick_count()
{
    struct timeval tval;
    uint64_t ret_tick;

    gettimeofday(&tval, nullptr);

    ret_tick = tval.tv_sec * 1000L + tval.tv_usec / 1000L;
    return ret_tick;
}


#endif //COMMON_H
