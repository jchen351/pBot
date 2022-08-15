#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <MapFileIO.h>
#include <QFileDialog>
#include <QInputDialog>
#include <QJsonDocument>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->graphicsView->setScene(&scene);
  scene.addText("Hello");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionSave_triggered() {
  QString filename = QFileDialog::getSaveFileName(
      this, tr("Save pMap"),
      QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
      tr("pMap Files (*.pmap)"));
  if (filename.isNull())
    return;
  MapFileIO::save_map_to_file(mMap,filename.toStdString());
}

void MainWindow::on_actionOpen_triggered() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open pMap"),
      QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
      tr("pMap Files (*.pmap)"));
  if (filename.isNull())
    return;
  ui->wMapSpinBox->setValue(mMap.width);
  ui->hMapSpinBox->setValue(mMap.height);
  on_newMapPushButton_clicked();
  mMap = std::move(MapFileIO::load_map_from_file(filename.toStdString()));
  DrawObstacles(ui->radBotSpinBox->value());
}

void MainWindow::on_addObstaclePushButton_clicked() {
  int x = ui->xObstacleSpinBox->value();
  int y = ui->yObstacleSpinBox->value();
  int rad = ui->radObstacleSpinBox->value();
  mMap.obstacles.emplace_back(x, y, rad);
  DrawObstacle(mMap.obstacles.back(), ui->radBotSpinBox->value());
}

void MainWindow::on_setGoalPushButton_clicked() {
  ui->startBotPushButton->setEnabled(true);
  DrawGoal(ui->xGoalSpinBox->value(), ui->yGoalSpinBox->value());
}

void MainWindow::on_startBotPushButton_clicked() {
  botUpdated = true;
  DrawBot(ui->xBotSpinBox->value(), ui->yBotSpinBox->value(),
          ui->radBotSpinBox->value());
  DrawGoal(ui->xGoalSpinBox->value(), ui->yGoalSpinBox->value());
  DrawPath();
}

void MainWindow::on_newMapPushButton_clicked() {
  scene.clear();
  ui->graphicsView->setSceneRect(0,0,ui->hMapSpinBox->value(),ui->hMapSpinBox->value());
  ui->graphicsView->fitInView(0,0,ui->hMapSpinBox->value(),ui->hMapSpinBox->value());
//  mMap = std::move(pMap(ui->wMapSpinBox->value(), ui->hMapSpinBox->value(), {}));
  ui->addObstaclePushButton->setEnabled(true);
  ui->setGoalPushButton->setEnabled(true);
  ui->actionSave->setEnabled(true);
}

void MainWindow::on_radBotSpinBox_valueChanged(int extra_rad) {
  scene.clear();
  if (ui->startBotPushButton->isEnabled()) {
    if (botUpdated)
      DrawBot(ui->xBotSpinBox->value(), ui->yBotSpinBox->value(),
              ui->radBotSpinBox->value());
    DrawGoal(ui->xGoalSpinBox->value(), ui->yGoalSpinBox->value());
  }
  DrawObstacles(extra_rad);
}

void MainWindow::DrawObstacle(const pObstacle &obstacle, int extra_rad) {
  int x = obstacle.x;
  int y = obstacle.y;
  int rad = obstacle.rad;
  int rad_plus = rad + extra_rad;
  scene.addEllipse(x - rad_plus, y - rad_plus, rad_plus * 2, rad_plus * 2,
                   QPen{QBrush{QColor{255, 0, 0}}, 1},
                   QBrush(QColor{255, 255, 0, 5}));
  scene.addEllipse(x - rad, y - rad, rad * 2, rad * 2, QPen(),
                   QBrush{QColor{0, 0, 0}});
  mMap.plot_obstacle(obstacle,extra_rad);
}

void MainWindow::DrawObstacles(int extra_rad) {
  for (const auto &obstacle: mMap.obstacles) {
    DrawObstacle(obstacle, extra_rad);
  }
}

void MainWindow::DrawBot(int x, int y, int rad) {
  scene.addEllipse(x - rad, y - rad, rad * 2, rad * 2, QPen(),
                   QBrush{QColor{255, 127, 0}});
}

void MainWindow::DrawGoal(int x, int y) {
  int rad = 5;
  scene.addEllipse(x - rad, y - rad, rad * 2, rad * 2, QPen(),
                   QBrush{QColor{0, 255, 0}});
}

void MainWindow::DrawPath() {
  pPoint start (ui->xBotSpinBox->value(),ui->yBotSpinBox->value());
  pPoint goal (ui->yGoalSpinBox->value(),ui->yGoalSpinBox->value());
  mMap.find_path(start,goal);
  for (const auto & p:mMap.path) {
      scene.addRect(p.x,p.y,1,1);
  }
}

void MainWindow::on_pix_pb_clicked()
{
  pixScene.clear();
  ui->graphicsView->setScene(&pixScene);
  DrawPixes();
}

void MainWindow::DrawPixes() {
  for (int i = 0; i <mMap.pixMap.size(); ++i) {
    for (int j = 0; j < mMap.pixMap[0].size(); ++j) {
      if(mMap.pixMap[i][j]){
        pixScene.addRect(i,j,1,1);
      }
    }
  }
}

