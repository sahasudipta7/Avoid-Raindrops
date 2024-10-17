#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "gamecontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // void keyPressEvent(QKeyEvent* keyEvent) override;

private:
    Ui::MainWindow *ui;
    // QGraphicsView *view;
    QGraphicsScene *scene;
    GameController *controller;

};

#endif // MAINWINDOW_H
