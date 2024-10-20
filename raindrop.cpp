#include "raindrop.h"
#include <QPixmap>
#include <cmath>
#include <QCoreApplication>

Raindrop::Raindrop(){
    setPixmap(QPixmap(":/raindrop1.png").scaled(30, 30));
    fTanAngle=1;
    flag=0;
}

int Raindrop::getFlag(){
    return this->flag;
}

void Raindrop::moveDown(){
    setPos(x(), y()+ 5);
}

void Raindrop::moveAtAnAngle(double tanAngle){
    //5/tantheta=dx

    // Convert degrees to radians
    //double angleRadians = qDegreesToRadians(angleDegrees);

    // Calculate tangent
    //double tangentValue = tan(angleRadians);
    setPos(x()-5/tanAngle,y()+5);
}
