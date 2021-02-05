#include "Map.h"
#include <random>
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



D2D1_POINT_2F& WebPoint::getPosition() {
    return position;
}

void WebPoint::move(float delta) {
    speed.x += force.x * delta;
    speed.y += force.y * delta;
    position.x += speed.x * delta;
    position.y += speed.y * delta;
}

void WebPoint::setSpeed(const D2D1_POINT_2F & speed) {
    this->beforeSpeed = this->speed;
    this->speed = speed;
}

void WebPoint::addForce(const D2D1_POINT_2F & force) {
    this->force.x += force.x;
    this->force.y += force.y;
}

void WebPoint::clearForce() {
    this->force.x = 0.f;
    this->force.y = 0.f;
}



bool SpiderWeb::testPoint(const D2D1_POINT_2F & point) {
    return point.x > rect.left 
    && point.x < rect.right 
    && point.y > rect.top 
    && point.y <rect.bottom;
}
bool SpiderWeb::inNear(const D2D1_POINT_2F & a,const D2D1_POINT_2F & b,float distance) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float ds = std::pow(dx*dx + dy * dy,0.5);
    return ds < distance;
}

D2D1_POINT_2F SpiderWeb::randomPoint(const D2D1_RECT_F & area) {
    D2D1_POINT_2F result;
    std::random_device rd;
    int rx = rd();
    int ry = rd();
    rx = std::abs(rx);
    ry = std::abs(ry);
    int width = static_cast<int>(area.right - area.left);
    int height = static_cast<int>(area.bottom - area.top);
    int x = rx % width;
    int y = ry % height;
    result.x = area.left + static_cast<float>(x);
    result.y = area.top + static_cast<float>(y);
    return result;
}
void SpiderWeb::spawnPointInArea(const D2D1_RECT_F & area) {
    auto position = randomPoint(area);
    auto speed = randomPoint(speedArea);
    WebPoint webPoint(position,speed);
    points.push_back(webPoint);
}

void SpiderWeb::spawnPointRandom() {
    spawnPointInArea(rect);
}



void SpiderWeb::setInWeb(bool inWeb) {
    this->inWeb = inWeb;
}

void SpiderWeb::onMove(const D2D1_POINT_2F & point) {
    if(!testPoint(point)) {
        mainIndex = -1;
        inWeb = false;
        return;
    }
    if(!inWeb) {
        WebPoint mp(point);
        points.push_back(mp);
        mainIndex = points.size() - 1;
    }
    inWeb = true;
    if(mainIndex > 0) {
        points[mainIndex].getPosition().x = point.x;
        points[mainIndex].getPosition().y = point.y;
    }
}

void SpiderWeb::updateLink() {
    float forceRate = 0.05f;
    for(auto & p : points) {
        p.clearForce();
    }
    for(int i = 0;i < points.size();i++) {
        for(int j = i + 1;j<points.size();j++) {
            if(inNear(points[i].getPosition(),points[j].getPosition())) {
                D2D1_POINT_2F a = points[i].getPosition();
                D2D1_POINT_2F b = points[j].getPosition();
                D2D1_POINT_2F aForce = D2D1::Point2F((b.x - a.x )/forceRate,(b.y - a.y)/forceRate);
                D2D1_POINT_2F bForce = D2D1::Point2F(-aForce.x,-aForce.y);
                points[i].addForce(aForce);
                points[j].addForce(bForce);
            }
        }
    }
}

void SpiderWeb::onTick(float delta) {
    elaspedTime += delta;
    float spawnTime = 1.0 / spawnSpeed;
    if(elaspedTime >= spawnTime) {
        elaspedTime = 0.0;
        spawnPointRandom();
    }
    for(int i = 0;i<points.size();i++) {
        if(i == mainIndex ){
            continue;
        }
        points[i].move(delta);
    }
	int k = 0;
	for (auto m = points.begin(); m != points.end(); m++) {
		if (!testPoint(m->getPosition())) {
			points.erase(m);
			if (k < mainIndex) {
				mainIndex--;
			}
		}
		k++;
	}
    updateLink();
}

void SpiderWeb::draw(ID2D1HwndRenderTarget * renderTarget,ID2D1SolidColorBrush * brush) {
    auto bColor = brush->GetColor();
    brush->SetColor(D2D1::ColorF(D2D1::ColorF::Green));
    for(auto & p : points) {
        D2D1_ELLIPSE de;
        de.point = p.getPosition();
        de.radiusX = 2.f;
        de.radiusY = 2.f;
        renderTarget->FillEllipse(de,brush);
    }
    for(int i = 0;i < points.size();i++) {
        for(int j = i + 1;j<points.size();j++) {
            if(inNear(points[i].getPosition(),points[j].getPosition())) {
            renderTarget->DrawLine(points[i].getPosition(),points[j].getPosition(),brush);
            }
        }
    }
    brush->SetColor(bColor);
}