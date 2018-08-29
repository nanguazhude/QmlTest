#include "MyRectangle.hpp"
#include <QtGui/qpainter.h>

void MyRectangle::paint(QPainter *painter) {
    auto varWidth = this->width();
    auto varHeight = this->height();
    auto varFillColor = this->fillColor();
    painter->fillRect(QRectF{ 0,0,varWidth,varHeight }, varFillColor);
}

MyRectangle::MyRectangle(QQuickItem *parent) :Super(parent) {}

MyRectangle::~MyRectangle() {}

