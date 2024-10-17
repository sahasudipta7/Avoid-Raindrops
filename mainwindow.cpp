#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
{
    ui->setupUi(this);

    // Set up the scene
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, 650, 550); // Adjust as needed

    QPixmap background(":/Background1.svg");
    background = background.scaled(scene->sceneRect().size().toSize(),
                                   Qt::IgnoreAspectRatio,
                                   Qt::SmoothTransformation);
    QGraphicsPixmapItem *backgroundItem = new QGraphicsPixmapItem(background);
    backgroundItem->setPos(0, 0);  // Position at the top-left
    backgroundItem->setZValue(-1);  // Ensure it stays behind other items
    scene->addItem(backgroundItem);  // Add to scene

    controller = new GameController(scene, this);

    // Connect signals to update UI labels
    connect(controller, &GameController::livesChanged, this, [=](int lives){
        ui->lives->display(lives);
    });

    connect(controller, &GameController::scoreChanged, this, [=](int score){
        ui->score->display(score);
    });

    connect(controller, &GameController::bestScoreChanged, this,  [=](int bestScore){
        ui->bestScore->display(bestScore);
    });

    // // Initialize labels
    // ui->livesLabel->setText(QString("Lives: %1").arg(controller->getLives()));
    // ui->scoreLabel->setText(QString("Score: %1").arg(controller->getScore()));


    // ui->graphicsView->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// void MainWindow::keyPressEvent(QKeyEvent *event) {
//     controller->keyPressEvent(event);
// }
