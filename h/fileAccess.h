/*
    Copyright (C) 2026 catboiithecatboy/pluem_plu

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include <stdio.h>
#include <string.h>

void readALineOfFile(const char* from, char* toString, int line){
    FILE* file = fopen(from, "r");
    char string[50] = "";
    
    for(int i = 1; i < line; i ++) // duct tape solution for line scrolling
        fgets(string, 50, file);

    if(fgets(string, 50, file))
        strcpy(toString, string);
    else strcpy(toString, "");
}
void readFile(const char* from, char* toString){
    FILE* file = fopen(from, "r");
    char string[100] = "";
    
    while(fgets(string, 50, file))
        strcpy(toString, string);
}