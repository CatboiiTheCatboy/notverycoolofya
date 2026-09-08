/*
    Copyright (C) 2026 catboiithecatboy/pluem_plu

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "res/options.h"
#include "h/utils.h"
#include "h/graphicsBank.h"
//#include "h/detector.h"
//#include "h/sutils.h"
#include "h/fileAccess.h"

void toPath(const char* dir, const char* name, const char* extension, char* toString){
    char file[50] = "";

    strcat(file, dir);
    strcat(file, name);
    strcat(file, extension);
    //printf("querying %s\n", file);

    strcpy(toString, file);
}

char hovering(XEvent event, int x, int y, int X, int Y){
    if(event.xmotion.x > x && event.xmotion.x <= x + X && event.xmotion.y > y && event.xmotion.y <= y + Y)
        return true;
    else return false;
}

int main(){
    Display* display = XOpenDisplay(NULL);
    if(!display) return 1;
    int screen = DefaultScreen(display);
    char version[50];
    strcat(version, Title);
    strcat(version, " ");
    strcat(version, Version);

    Window window = XCreateSimpleWindow(
        display, RootWindow(display, screen), //Parent
        0, 0, 640, 480, 0,
        BlackPixel(display, screen),//Border color
        WhitePixel(display, screen) //Background color
    );
    XStoreName(display, window, version);
    XMapWindow(display, window);

    XEvent event;
    XSelectInput(display, window, ButtonPressMask | PointerMotionMask | ButtonPress);
    XNextEvent(display, &event);
    Pixmap whole = XCreatePixmap(display, window,
        640, 480, DefaultDepth(display, screen)
    );

    GC graph = XCreateGC(display, window, 0, NULL);
    XSetForeground(display, graph, WhitePixel(display, screen));
    XFillRectangle(display, whole, graph, 0, 0, 640, 480);
    XSetForeground(display, graph, BlackPixel(display, screen));

    char loop = true;
    //char temp[50];
    while(loop){ //                         menu
        sleep(0.016666);
        //strcpy(temp, "");
        //readALineOfFile("res/novel", temp, 2);
        //printf("%s", temp);

        GC mask = XCreateGC(display, whole, 0, NULL);
        Pixmap title = loadXpm(display, window, "res/gui/title.png.xpm", &mask, 0, 0);
        Pixmap start = makeButton(display, window, "Start", 0);
        Pixmap start_= makeButton(display, window, "Start", 1);
        Pixmap quit  = makeButton(display, window, "Quit", 0);
        Pixmap quit_ = makeButton(display, window, "Quit", 1);
        //XDrawString(display, whole, graph, 0, 14, "A Cool Fan-game", 15);
        XDrawString(display, whole, graph, 0, 414, "simpleVisual - Copyright (C) 2026  catboiithecatboy/pluem_plu", 61);
        XDrawString(display, whole, graph, 0, 446, "This program comes with ABSOLUTELY NO WARRANTY.", 47);
        XDrawString(display, whole, graph, 0, 462, "This is free software, and you are welcome to redistribute it", 61);
        XDrawString(display, whole, graph, 0, 478, "under certain conditions; see COPYING for details.", 50);
        XCopyArea(display, title, whole, mask, 0, 0, 640, 480, 0, 0);
        XCopyArea(display, start, whole, graph, 0, 0, 64, 16, 288, 320);
        XCopyArea(display, quit , whole, graph, 0, 0, 64, 16, 288, 352);
        XFreePixmap(display, title);
        XFreePixmap(display, start);
        XFreePixmap(display, quit);

        while(XPending(display)){
            XNextEvent(display, &event);
            if(event.type == ButtonPressMask){
                //printf("%d, %d\n", event.xmotion.x, event.xmotion.y);
                if(hovering(event, 288, 320, 64, 16)){
                    XCopyArea(display, start_, whole, graph, 0, 0, 64, 16, 288, 320);
                    XFreePixmap(display, start_);
                    //printf("Startin'...\n");
                    sleep(0.016666);
                    loop = false;
                }
                if(hovering(event, 288, 352, 64, 16)){
                    XCopyArea(display, quit_, whole, graph, 0, 0, 64, 16, 288, 352);
                    XFreePixmap(display, quit_);
                    //printf("See ya!\n");
                    XDestroyWindow(display, window);
                    XCloseDisplay(display);
                    return 0;
                }
            }
        }
        XCopyArea(display, whole, window, graph, 0, 0, 640, 480, 0, 0);
    }
    XSetForeground(display, graph, WhitePixel(display, screen));
    XFillRectangle(display, whole, graph, 0, 0, 640, 480);
    XSetForeground(display, graph, BlackPixel(display, screen));


    char character[10] = "1", background[10] = "1";
    short characterWidth = 267, characterHeight = 533;
    int index = 1, characterX = 640 - characterWidth, characterY = 0;
    char dialog[200], name[20], visual[50], tempVisual[50], path[50], choices[6][50];
    char choicesEnabled = false;
    //Pixmap pixmap;
    while(true){ //                     ----visual novel----
        sleep(0.016666);

        GC mask = XCreateGC(display, window, 0, NULL);

        readALineOfFile("res/visual", visual, index);
        while(visual[0] == '!' || visual[0] == '?'){ // function handler
            //printf("%s", visual);
            if(visual[0] == '!'){
                int i = 1;
                char function[10] = "", value[10] = "";
                for(i = i; visual[i] != ' '; i ++)
                    function[strlen(function)] = visual[i];
                function[strlen(function)] = '\0';
                i ++;
                for(i = i; visual[i] != '\n'; i ++)
                    value[strlen(value)] = visual[i];
                value[strlen(value)] = '\0';

                if(!strcmp(function, "bg")){
                    strcpy(background, value);
                    //printf("new background: %s", background);
                }
                if(!strcmp(function, "end") && !choicesEnabled){
                    strcpy(choices[0], "");
                    for (int j = 0; j < atoi(value); j ++){
                        readALineOfFile("res/visual", tempVisual, index + j + 1);
                        strcpy(choices[j], tempVisual);
                        strcpy(choices[j + 1], "");
                        choicesEnabled ++;
                    }
                }
            }
            
            index ++;
            readALineOfFile("res/visual", visual, index);
        }

        if(!choicesEnabled/* && visual[0] != '~' - unused """quality of life""" feature*/){
            int item = 1;
            strcpy(character, "");
            strcpy(name, "");
            for(int i = 0; visual[i] != '\n'; i ++){ // visual handler){
                if(visual[i] == ' '){
                    item ++;
                    i ++;
                }
                if(item == 1/* && visual[i] != '~'*/)
                    character[strlen(character)] = visual[i];
                if(item == 2)
                    if(visual[i] == 'l')
                        characterX = 0;
                    else characterX = 640 - characterWidth;
                if(item == 3/* && visual[i] != '~'*/){
                    //printf("%i > ", strlen(name));
                    //printf("%lu, %c > ", strlen(name), visual[i]);
                    name[strlen(name) + 1] = '\0';
                    name[strlen(name)] = visual[i];
                    //printf("%lu, %s\n", strlen(name), name);
                }
            }
        }
        
        toPath("res/backgrounds/", background, ".png.xpm", path);
        Pixmap backgroundMap = loadXpm(display, window, path, NULL, 0, 0);
        XCopyArea(display, backgroundMap, whole, graph, 0, 0, 640, 480, 0, 0);
        toPath("res/chars/", character, ".png.xpm", path);
        Pixmap charMap = loadXpm(display, window, path, &mask, characterX, characterY);
        XCopyArea(display, charMap, whole, mask, 0, 0, characterWidth, characterHeight, characterX, characterY);
        
        if(!choicesEnabled){
            Pixmap textboxMap = loadXpm(display, window, "res/gui/box.png.xpm", &mask, 0, 0);
            XCopyArea(display, textboxMap, whole, mask, 0, 0, 640, 480, 0, 0);
            XFreePixmap(display, textboxMap);
            readALineOfFile("res/novel", dialog, index);
            //printf("%s", dialog);
            XDrawString(display, whole, graph, 32, 392, dialog, strlen(dialog) - 1);
            XDrawString(display, whole, graph, 16, 360, name, strlen(name));
        } else{
            for(int i = 0; choices[i][0] != '\0'; i ++){
                Pixmap buttonMap = loadXpm(display, window, "res/gui/button.png.xpm", &mask, 32, 100 + i * 40);
                XCopyArea(display, buttonMap, whole, mask, 0, 0, 169, 30, 32, 100 + i * 40);
                XFreePixmap(display, buttonMap);
                readALineOfFile("res/novel", dialog, index + i);
                XDrawString(display, whole, graph, 44, 100 + 20 + i * 40, dialog, strlen(dialog) - 1);
            }
        }
        
        Pixmap quit = makeButton(display, window, "Quit", 0);
        Pixmap quit_= makeButton(display, window, "Quit", 1);
        XCopyArea(display, quit, whole, graph, 0, 0, 64, 16, 0, 0);

        while(XPending(display)){
            XNextEvent(display, &event);
            if(event.type == ButtonPress){
                //printf("_");
            }
            if(event.type == ButtonPressMask){
                //printf("%d, %d\n", event.xmotion.x, event.xmotion.y);
                if(hovering(event, 0, 0, 64, 16)){
                    XCopyArea(display, quit_, whole, graph, 0, 0, 64, 16, 0, 0);
                    XDestroyWindow(display, window);
                    XCloseDisplay(display);
                    return 0;
                }
                if(!choicesEnabled){
                    if(hovering(event, 0, 0, 640, 480))
                        index ++;
                } else{
                    if(hovering(event, 0, 100, 640, 40 * choicesEnabled)){
                        readALineOfFile("res/visual", visual, 1);
                        strcpy(tempVisual, "?");
                        strcat(tempVisual, choices[(event.xmotion.y - 100) / 40]);
                        //printf("Looking for %s\n", tempVisual);

                        for(index = 2; strcmp(tempVisual, visual); index ++){
                            readALineOfFile("res/visual", visual, index);
                            //printf("At %i - %s : %s \n", index, tempVisual, visual);
                        }
                        choicesEnabled = false;
                    }
                }
            }
        }
        XCopyArea(display, whole, window, graph, 0, 0, 640, 480, 0, 0);
        XFreeGC(display, mask);
        XFreePixmap(display, backgroundMap);
        XFreePixmap(display, charMap);
        XFreePixmap(display, quit);
        XFreePixmap(display, quit_);
    }
}
