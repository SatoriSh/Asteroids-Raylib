#pragma once
#include "raylib.h"


struct Timer
{
    float timeoutTime;
    float leftTime;

    void update();
    bool timeout() const;
    void reset();
};
