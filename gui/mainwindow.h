#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pMap.h"
#include <QGraphicsScene>
#include <QJsonObject>
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_actionSave_triggered();

  void on_actionOpen_triggered();

  void on_addObstaclePushButton_clicked();

  void on_setGoalPushButton_clicked();

  void on_startBotPushButton_clicked();

  void on_newMapPushButton_clicked();

  void on_radBotSpinBox_valueChanged(int);

private:
  Ui::MainWindow *ui;
  QGraphicsScene scene;
  pMap mMap;
  bool botUpdated = false;

  void DrawObstacle(const pObstacle &obstacle, int extra_rad);
  void DrawObstacles(int extra_rad);
  void DrawBot(int x, int y, int rad);
  void DrawGoal(int x, int y);
  void DrawPath();
};
#endif // MAINWINDOW_H
