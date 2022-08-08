#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QInputDialog>
#include <QFile>
#include <QFileDialog>
#include <QIODevice>
#include <QJsonDocument>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    scene.addText("Hello");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSave_triggered()
{

}


void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open pMap"), "/Users/jianchen/Workspaces/pBot/maps", tr("Json Files (*.json)"));
    if(filename.isNull()) return;
    QFile file;
    file.setFileName(filename);
    file.open(QIODeviceBase::ReadWrite);
    QString fileData = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(fileData.toUtf8());
    QJsonObject json = doc.object();
    scene.addLine(0,0,json.value("width").toInt(),json.value("height").toInt());
    scene.addEllipse(0,0,35,35);

}


void MainWindow::on_actionNew_triggered()
{
    bool wOk,hOk;
    int w = QInputDialog::getInt(this, tr("New width"),
                                 tr("width:"), 20, 1, 300, 1, &wOk);
    if(wOk){
        int h = QInputDialog::getInt(this, tr("New height"),
                                         tr("height:"), 20, 1, 300, 1, &hOk);
        scene.clear();
        mMapJson = {
            {"width",w},
            {"height",h},
            {"obstacles", {}}
        };
    }

}


void MainWindow::on_pushButton_clicked()
{
    int x = ui->xObstacleSpinBox->value();
    int y = ui->yObstacleSpinBox->value();
    int rad = ui->radObstacleSpinBox->value();
    scene.addEllipse(x-rad,y-rad,rad*2,rad*2);
}

