#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFileDialog"

#include <QImage> // designed and optimized for I/O, and for direct pixel access and manipulation,
#include <QPixmap> // designed and optimized for showing images on screen.
#include <QBitmap> // convenience class that inherits QPixmap, ensuring a depth of 1.
#include <QPicture> // paint device that records and replays QPainter commands.

#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QPixmap labelImage("/Users/teoip/Desktop/kitty.jpg"); // add filepath to your own image here
    ui->label->setPixmap(labelImage);
    ui->label->setScaledContents(true);
}


void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),

                                                    "/home",

                                                    tr("Images (*.png *.xpm *.jpg)"));

    QPixmap labelTest(fileName); // add filepath to your own image here

    ui->label_2->setPixmap(labelTest);

    ui->label_2->setScaledContents(true);
}

