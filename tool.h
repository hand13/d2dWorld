#pragma once
#include <windows.h>
#include <string>
bool hr2str(HRESULT hr,void * buffer,size_t size);
class Time {
    private:
    long createdTime;
    long lastTime;
    public:
    Time();
    void init();
    long getDelta();
    long getElapsedTime();
    long getCurrentTime();
};
std::wstring m2wstr(std::string k);
std::wstring nowStr();