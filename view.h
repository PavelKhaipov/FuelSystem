#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QPaintEvent>

#define MAX_VALUE 15

class View : public QWidget
{
    Q_OBJECT
public:
    explicit    View(QWidget *parent = nullptr);
    void        set(double _v1, double _v2);

protected:
    void        paintEvent(QPaintEvent *event);
    void        paintRect(QPainter &painter, QRect rect, double v, bool highlight);

    double      v1=0, v2=0;
};

#endif // VIEW_H
