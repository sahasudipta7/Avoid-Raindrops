#include "player.h"
#include <QGraphicsScene>
#include <QPixmap>

Player::Player(){
    setPixmap(QPixmap("://character.png").scaled(75, 75));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Player::keyPressEvent(QKeyEvent *event) {
    int moveAmount = 10;  // Amount to move on each key press

    if (event->key() == Qt::Key_Left) {
        if (x() > 10) {
            setPos(x() - moveAmount, y());
        }
    } else if (event->key() == Qt::Key_Right) {
        if (x() + boundingRect().width() + moveAmount < scene()->width()) {
            setPos(x() + moveAmount, y());
        }
    }
    else{
        //
    }

    setFocus();
}
