#include "timer.h"

void Timer::update()
{
    if (leftTime > 0.0f)
        leftTime -= GetFrameTime();
}

bool Timer::timeout()
{
    return leftTime <= 0.0f;
}

void Timer::reset()
{
    leftTime = timeoutTime;
}
