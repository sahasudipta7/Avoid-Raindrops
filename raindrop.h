#ifndef RAINDROP_H
#define RAINDROP_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Raindrop : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum {Type = UserType + 1};
    int type() const override {return Type;}
    Raindrop();
    void moveDown();
};

#endif // RAINDROP_H
