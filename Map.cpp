#include "Map.h"
Pawn::Pawn(PawnType pawnType,D2D1_RECT_F rect) :pawnType(pawnType),rect(rect){
}
void Pawn::draw(ID2D1HwndRenderTarget * renderTarget,ID2D1SolidColorBrush * brush) {
    renderTarget->DrawRectangle(rect,brush);
    auto backupColor = brush->GetColor();
    D2D1_ELLIPSE ell;
    ell.point = D2D1::Point2F((rect.left + rect.right)/2,(rect.bottom + rect.top)/2);
    ell.radiusX = (rect.right - rect.left)/2;
    ell.radiusY = (rect.bottom - rect.top)/2;
    if(pawnType == RED) {
        brush->SetColor(D2D1::ColorF(D2D1::ColorF::Magenta));
        renderTarget->FillEllipse(ell,brush);
    }else if(pawnType == BLACK){
        brush->SetColor(D2D1::ColorF(D2D1::ColorF::MediumBlue));
        renderTarget->FillEllipse(ell,brush);
    }
    brush->SetColor(backupColor);
}
bool Pawn::touched(D2D1_POINT_2F & point) {
    if(point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.bottom) {
        onTouch(point);
        return true;
    }
    return false;
}
void Pawn::onTouch(D2D1_POINT_2F & point) {
    if(pawnType == EMPTY) {
        pawnType = RED;
    }else if(pawnType == RED) {
        pawnType = BLACK;
    }else {
        pawnType = EMPTY;
    }
}
Map::Map(UINT width,UINT height,D2D1_RECT_F rect):width(width),height(height),rect(rect){
    float cellWidth = (rect.right - rect.left)/static_cast<float>(width);
    float cellHeight = (rect.bottom - rect.top)/static_cast<float>(height);
    float wBorder =cellWidth/20;
    float hBorder =cellHeight/20;
    float currentY = rect.top;
    for(UINT i = 0;i<height;i++) {
        float currentX = rect.left;
        for(UINT j = 0;j<width;j++) {
            pawns.push_back(Pawn(EMPTY
            ,D2D1::RectF(currentX + wBorder
            ,currentY + hBorder
            ,currentX + cellWidth - wBorder
            ,currentY + cellHeight - hBorder)));
            currentX += cellWidth;
        }
        currentY += cellHeight;
    }
}
void Map::draw(ID2D1HwndRenderTarget * renderTarget,ID2D1SolidColorBrush * brush) {
    for(Pawn & pawn:pawns) {
        pawn.draw(renderTarget,brush);
    }
}
bool Map::touched(D2D1_POINT_2F& point) {
    for(Pawn&pawn:pawns) {
        if(pawn.touched(point)) {
            onTouch(point);
            return true;
        }
    }
    return false;
}
void Map::onTouch(D2D1_POINT_2F & point) {
}