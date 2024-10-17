#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class Player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum {Type = UserType + 2};
    int type() const override {return Type;}
    Player();
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // PLAYER_H
