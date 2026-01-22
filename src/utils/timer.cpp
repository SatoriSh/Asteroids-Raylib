#include "timer.h"

void setLeftTime(Timer* timer, float leftTime)
{
    timer->leftTime = leftTime;
}

void start(Timer *timer)
{
    if (timer->leftTime > 0.0f)
        timer->leftTime -= GetFrameTime();
}

bool timeout(Timer *timer)
{
    return timer->leftTime <= 0.0f;
}
