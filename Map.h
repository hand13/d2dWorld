#pragma once
#include <d2d1.h>
#include <vector>
enum PawnType {
    EMPTY,RED,BLACK
};
class Pawn {
    private:
    PawnType pawnType;
    D2D1_RECT_F rect;
    public:
    Pawn(PawnType pawnType,D2D1_RECT_F rect);
    void draw(ID2D1HwndRenderTarget * renderTarget,ID2D1SolidColorBrush * brush);
    bool touched(D2D1_POINT_2F& point);
    void onTouch(D2D1_POINT_2F& point);
};
class Map {
    private:
    UINT width;
    UINT height;
    D2D1_RECT_F rect;
    std::vector<Pawn> pawns;
    public:
    bool touched(D2D1_POINT_2F& point);
    Map(UINT width,UINT height,D2D1_RECT_F rect);
    void draw(ID2D1HwndRenderTarget * renderTarget,ID2D1SolidColorBrush * brush);
    void onTouch(D2D1_POINT_2F& point);
};

class WebPoint {
    private:
    D2D1_POINT_2F position;
    D2D1_POINT_2F speed;
    D2D1_POINT_2F beforeSpeed;
    D2D1_POINT_2F force;
    public:
    const static float maxSpeed;
    float mess;
    WebPoint(const D2D1_POINT_2F & position) {
        this->position = position;
        this->speed.x = 0.f;
        this->speed.y = 0.f;
        this->beforeSpeed = speed;
        force.x = 0.f;
        force.y = 0.f;
        mess = 1.f;
    }
    WebPoint(const D2D1_POINT_2F & position,const D2D1_POINT_2F & speed,float mess) {
        this->position = position;
        this->speed = speed;
        this->beforeSpeed = speed;
        force.x = 0.f;
        force.y = 0.f;
        this->mess = mess;
    }
    D2D1_POINT_2F& getPosition();
    void setSpeed(const D2D1_POINT_2F & speed);
    void addForce(const D2D1_POINT_2F & force);
    void clearForce();
    void move(float delta);
};

class SpiderWeb {
    private:
    float elaspedTime;
    float spawnSpeed;
    bool inWeb;
    int  mainIndex;
    std::vector<WebPoint> points;
    D2D1_RECT_F rect;
    D2D1_RECT_F speedArea;
    bool testPoint(const D2D1_POINT_2F & point);
    bool inNear(const D2D1_POINT_2F & a,const D2D1_POINT_2F & b,float distance = 150.f);
    D2D1_POINT_2F randomPoint(const D2D1_RECT_F & rect);
    void updateLink();
    public:
    SpiderWeb(const D2D1_RECT_F & rect):rect(rect),inWeb(false),elaspedTime(0.f){
        mainIndex = -1;
        spawnSpeed = 20.f;
        speedArea.left = -20.f;
        speedArea.right = 20.f;
        speedArea.top = -20.f;
        speedArea.bottom = 20.f;
    };
    void spawnPointInArea(const D2D1_RECT_F & area);
    void spawnPointRandom();
    void draw(ID2D1HwndRenderTarget * renderTarget,ID2D1SolidColorBrush * brush);
    void onMove(const D2D1_POINT_2F & point);
    void onTick(float delta);
    void setInWeb(bool inWeb);
    int getPointCount();
};