#include "tool.h"
#include <ctime>
#include <memory>
#include <sstream>
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
std::wstring m2wstr(std::string k) {
    const char * tmp = k.c_str();
    int bs = static_cast<int>(strlen(tmp));
    std::unique_ptr<WCHAR[]> buffer(new WCHAR[bs]);
    MultiByteToWideChar(CP_ACP,0,tmp,static_cast<int>(strlen(tmp)),buffer.get(),bs);
    std::wstring result(buffer.get());
    return result;
}
std::wstring nowStr() {
    time_t now;
    time(&now);
    tm t;
    localtime_s(&t,&now);
    std::wstringstream ws;
    ws << t.tm_year + 1900 <<L"-"<<t.tm_mon + 1<<L"-"<<t.tm_mday
    <<L" "<<t.tm_hour <<L":"<<t.tm_min<<L":"<<t.tm_sec;
    return ws.str();
}