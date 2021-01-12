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