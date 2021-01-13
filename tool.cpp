#include "tool.h"
#include <ctime>
bool hr2str(HRESULT hr,void * buffer,size_t size) {
    return true;
}

Time::Time() {
    lastTime = getCurrentTime();
    createdTime = lastTime;
}
void Time::init() {
    lastTime = getCurrentTime();
}
long Time::getDelta() {
    auto currentTime = getCurrentTime();
    auto delta = currentTime -lastTime;
    lastTime = currentTime;
    return delta;
}
long Time::getElapsedTime() {
    return getCurrentTime() - createdTime;
}
long Time::getCurrentTime() {
    time_t now;
    time(&now);
    return now;
}