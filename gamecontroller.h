#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsScene>
#include "player.h"

class GameController : public QObject {
    Q_OBJECT;
public:
    explicit GameController(QGraphicsScene *scene, QObject *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    int getLives() const;
    int getScore() const;
    int getBestScore() const;

signals:
    void livesChanged(int lives);
    void scoreChanged(int score);
    void bestScoreChanged(int score);

private slots:
    void spawnRainDrop();
    void updateGame();
    void updateGameAngle();

private:
    QGraphicsScene *scene;
    Player *player;
    QTimer *raindropTimer;
    QTimer *gameTimer;
    int lives;
    int score;
    int bestScore;
    void checkCollisions();
    void endGame();
    void resetGame();
};

#endif // GAMECONTROLLER_H
