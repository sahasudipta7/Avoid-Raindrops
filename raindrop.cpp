#include "raindrop.h"
#include <QPixmap>

Raindrop::Raindrop(){
    setPixmap(QPixmap(":/raindrop1.png").scaled(30, 30));
}

void Raindrop::moveDown(){
    setPos(x(), y()+ 5);
}
