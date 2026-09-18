/*
    Copyright (C) 2026 catboiithecatboy/pluem_plu

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include <time.h>
#define byte char
#define true 1
#define false 0
//#include <stdio.h>

// HIGHLY unoptimized "sleep" and "wait" functions lie here
void wait(int waitFor){
    long long until = time(NULL) + waitFor;
    while (time(NULL) < until){}
}

void sleep(double waitFor){
    struct timespec time;
    if(clock_gettime(CLOCK_BOOTTIME, &time)) return;
    double from = (double)time.tv_sec + (double)time.tv_nsec / 1e9;
    double until = from + waitFor;
    //printf("Waiting from %f, %f\n",from, until);
    while ((double)time.tv_sec + (double)time.tv_nsec / 1e9 < until){
        clock_gettime(CLOCK_BOOTTIME, &time);
    }
}