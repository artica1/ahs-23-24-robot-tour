#ifndef MOUSE_H
#define MOUSE_H

#include <PS2MouseHandler.h>

extern float leftdxraw;
extern float leftdyraw;
extern float rightdxraw;
extern float rightdyraw;

bool initializeMice();

bool storeMouseData();

bool flushMouseData();

#endif