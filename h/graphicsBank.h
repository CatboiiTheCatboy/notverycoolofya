/*
    Copyright (C) 2026 catboiithecatboy/pluem_plu

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include <X11/Xlib.h>
#include <X11/xpm.h>
#include <X11/extensions/shape.h>
#include <string.h>

void drawButton(Display* display, Window* window, Pixmap* drawable, const char* string, unsigned int x, unsigned int y){
    int screen = DefaultScreen(display);
    GC graph = XCreateGC(display, *window, 0, NULL);
    Pixmap buttonBase = XCreatePixmap(display, *window,
        64, 16, DefaultDepth(display, screen)
    );

    XSetForeground(display, graph, WhitePixel(display, screen));
    XFillRectangle(display, buttonBase, graph, 1, 1, 62, 14);
    XCopyArea(display, buttonBase, *drawable, graph,
    0, 0, 64, 16,
    x, y
    );

    XSetForeground(display, graph, BlackPixel(display, screen));
    XDrawString(display, *drawable, graph, x + 2, y + 14,
        string, strlen(string)
    );
}

Pixmap makeButton(Display* display, Window window, const char* string, char down){
    int screen = DefaultScreen(display);
    GC graph = XCreateGC(display, window, 0, NULL);

    Pixmap button = XCreatePixmap(display, window,
        64, 16, DefaultDepth(display, screen)
    );

    XSetForeground(display, graph, WhitePixel(display, screen));
        XFillRectangle(display, button, graph, 1 - down, 1 - down, 61 + down, 13 + down);

    XSetForeground(display, graph, BlackPixel(display, screen));
    XDrawString(display, button, graph, 2 + down, 13 + down,
        string, strlen(string)
    );

    return button;
}

Pixmap makeFrame(Display* display, Window window, unsigned int width, unsigned int height){
    int screen = DefaultScreen(display);
    GC graph = XCreateGC(display, window, 0, NULL);

    Pixmap frame = XCreatePixmap(display, window,
        width, height, DefaultDepth(display, screen)
    );

    XSetForeground(display, graph, WhitePixel(display, screen));
        XFillRectangle(display, frame, graph, 1, 1, width - 2, width - 2);

    return frame;
}


Pixmap loadXpm(Display* display, Window window, const char* from, GC* optGraphMask, int optX, int optY){
    int screen = DefaultScreen(display);
    //GC graph = XCreateGC(display, window, 0, NULL);

    Pixmap xpm, mask;
    XpmReadFileToPixmap(display, window, from, &xpm, &mask, NULL);
    //Pixmap pixmap = XCreatePixmap(display, window, width, height, DefaultDepth(display, screen));

    //XSetForeground(display, graph, WhitePixel(display, screen));
    //XFillRectangle(display, pixmap, graph, 0, 0, width, height);

    //XShapeCombineMask(display, window, ShapeBounding, 0, 0, mask, ShapeSet);
    //XCopyArea(display, xpm, pixmap, graph, 0, 0, width, height, 0, 0);

    if(optGraphMask){
        XSetClipMask(display, *optGraphMask, mask);
        XSetClipOrigin(display, *optGraphMask, optX, optY);
    }
    return xpm;
}

/*
Pixmap makePatternMask(Display* display, Window window, unsigned int width, unsigned int height, char preset, char step, GC* graphMask, int x, int y){
    GC graph = XCreateGC(display, window, 0, NULL);
    Pixmap mask = XCreatePixmap(display, window, width, height, 1);
    XSetForeground(display, graph, 1);
    XDrawRectangle(display, mask, graph, 0, 0, width, height);
    XSetForeground(display, graph, 0);

    switch(preset){
    case '1':
        break;
    default:
        break;
    }
}
*/