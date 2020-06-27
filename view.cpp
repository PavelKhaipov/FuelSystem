#include "view.h"
#include <QPainter>

View::View(QWidget *parent) : QWidget(parent)
{
    QPalette Pal(palette());

    // цвет фона
    Pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(Pal);
}

void View::set(double _v1, double _v2)
{
    // установить новые значения
    v1 = _v1;
    v2 = _v2;
    repaint();
}

void View::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::darkGreen);
    painter.setFont(QFont("Arial", 24));

    int w = rect().width();                         // ширина области схемы
    int h = rect().height();                        // высота области схемы

    QRect rect1(w*0.2,h*0.3,w*0.2,h*0.4);           // область левого бака
    QRect rect2(w*0.6,h*0.3,w*0.2,h*0.4);           // область правого бака

    // линии схемы
    painter.drawLine(w*0.9, h*0.2,rect1.center().x(), h*0.2);
    painter.drawLine(rect1.center().x(), h*0.2, rect1.center().x(), rect1.y());
    painter.drawLine(rect2.center().x(), h*0.2, rect2.center().x(), rect2.y());
    painter.drawLine(w*0.9, h*0.8,rect1.center().x(), h*0.8);
    painter.drawLine(rect1.center().x(), h*0.8, rect1.center().x(), rect1.bottom()+1);
    painter.drawLine(rect2.center().x(), h*0.8, rect2.center().x(), rect2.bottom()+1);

    // нарисовать вход и выход системы
    int d = w*0.02;
    QPoint points1[3] = {QPoint(w*0.9, h*0.2), QPoint(w*0.9+d, h*0.2+d*0.5), QPoint(w*0.9+d, h*0.2-d*0.5) };
    painter.drawPolygon(points1, 3);
    QPoint points2[3] = {QPoint(w*0.9+d, h*0.8), QPoint(w*0.9, h*0.8+d*0.5), QPoint(w*0.9, h*0.8-d*0.5) };
    painter.drawPolygon(points2, 3);

    paintRect(painter, rect1, v1, v1>v2);           // нарисовать левый бак и клапан
    paintRect(painter, rect2, v2, v2>v1);           // нарисовать правый бак и клапан

    event->accept();
}

// Нарисовать один бак и клапан
void View::paintRect(QPainter &painter, QRect rect, double v, bool highlight)
{
    painter.drawRect(rect);                         // нарисовать контур бака

    int d=rect.height()*(1.-(double)v/MAX_VALUE);   // расстояние от верней стороны, которое не нужно закрашивать
    painter.fillRect(rect.adjusted(0,d,0,0), Qt::darkGreen);    // условное изображение объема топлива

    // Прямоугольник с текстом
    QRect textRect(0,0,70,30);
    textRect.moveCenter(rect.center());
    painter.fillRect(textRect, Qt::black);
    painter.drawRect(textRect);
    painter.drawText(textRect, Qt::AlignCenter, QString::number(v));

    // нарисовать клапан
    QPainterPath path;

    int dx = rect.width()*0.1;
    int dy = rect.height()*0.1;
    int px = rect.center().x();
    int py = rect.y() - dy*0.5;

    path.moveTo(px, py);
    path.lineTo(px-dx, py-dy);
    path.lineTo(px+dx, py-dy);
    path.lineTo(px, py);

    painter.fillPath(path, highlight? Qt::red: Qt::darkGreen);
}
