#pragma once
#include "raylib.h"


struct Timer
{
    float leftTime;
};


void setLeftTime(Timer *timer, float leftTime);
void start(Timer* timer);
bool timeout(Timer* timer);
