#include "gamecontroller.h"
#include "raindrop.h"
#include "player.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QApplication>

GameController::GameController(QGraphicsScene *scene, QObject *parent)
    : QObject(parent), scene(scene), lives(3), score(0) {
    player = new Player();
    scene->addItem(player);
    player->setPos(150, 400);

    raindropTimer = new QTimer(this);
    connect(raindropTimer, &QTimer::timeout, this, &GameController::spawnRainDrop);
    raindropTimer->start(QRandomGenerator::global()->bounded(500, 1500)); // Random spawn interval

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &GameController::updateGame);
    gameTimer->start(33); // 30 FPS Refresh Rate, i.e., 1/0.033

    emit livesChanged(lives);
    emit scoreChanged(score);
}

void GameController::spawnRainDrop(){
    int rainX = QRandomGenerator::global()->bounded(30, static_cast<int>(scene->width()) - 30);
    Raindrop *raindrop = new Raindrop();
    scene->addItem(raindrop);
    raindrop->setPos(rainX, -10);

    int interval = QRandomGenerator::global()->bounded(500, 1500);
    raindropTimer->start(interval);
}

void GameController::updateGame(){
    QList<QGraphicsItem *> items = scene->items();
    for(QGraphicsItem *item : items){
        if (item->type() == Raindrop::Type) {
            Raindrop *raindrop = static_cast<Raindrop *>(item);
            raindrop->moveDown();
            if(raindrop->y() > scene->height()) {
                scene->removeItem(raindrop);
                delete raindrop;
                score++;
                if(score > bestScore){
                    bestScore = score;
                }
                emit scoreChanged(score);
                emit bestScoreChanged(bestScore);
            }
        }
    }
    checkCollisions();
}

void GameController::checkCollisions(){
    QList<QGraphicsItem *> collisions = player->collidingItems();
    for (QGraphicsItem *item: collisions){
        if(item->type() == Raindrop::Type){
            Raindrop *raindrop = static_cast<Raindrop *>(item);
            scene->removeItem(raindrop);
            delete raindrop;
            lives--;
            emit livesChanged(lives);
            if(lives == 0) {
                endGame();
                return;
            }
        }
    }
}

void GameController::endGame(){
    raindropTimer->stop();
    gameTimer->stop();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Game Over",
                                  QString("Game Over!\nYour score: %1\nDo you want to restart?").arg(score),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        resetGame();
    } else {
        QApplication::quit();
    }
}

void GameController::resetGame(){

    lives = 3;
    score = 0;
    bestScore = GameController::getBestScore();
    emit livesChanged(lives);
    emit scoreChanged(score);
    emit bestScoreChanged(bestScore);

    player->setPos(150, 400);


    QList<QGraphicsItem *> items = scene->items();
    for(QGraphicsItem *item : items){
        if (item->type() == Raindrop::Type) {
            scene->removeItem(item);
            delete item;
        }
    }

    raindropTimer->start(QRandomGenerator::global()->bounded(500, 1500));
    gameTimer->start(33);
}


void GameController::keyPressEvent(QKeyEvent *event){
    player->keyPressEvent(event);
}

int GameController::getLives() const{
    return lives;
}

int GameController::getScore() const{
    return score;
}

int GameController::getBestScore() const{
    return bestScore;
}
