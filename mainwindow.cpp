#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "imageeditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    userImage = new ImageEditor(this);

    // Connect the button click to the ImageEditor slot
  //  connect(ui->displayButton, SIGNAL(clicked()), userImage, SLOT(addImage()));

    // Connect the updateDisplay signal to a slot that updates the displayed image
    connect(userImage, SIGNAL(updateDisplay(QImage)), this, SLOT(updateDisplayedImage(QImage)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDisplayedImage(const QImage& newImage)
{
    // Update the QLabel or any other widget that displays the image
    ui->displayLabel->setPixmap(QPixmap::fromImage(newImage));
    ui->displayLabel->setScaledContents(true);
}

void MainWindow::on_displayButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),

                                                    "/home",

                                                    tr("Images (*.jpg *.gif *.png *.bnp *.tif )"));
    ;
    userImage->loadImage(fileName);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        "/home",
                                                        QFileDialog::ShowDirsOnly
                                                            | QFileDialog::DontResolveSymlinks);
    userImage->imgExport(dirPath);
}

void MainWindow::on_noirButton_clicked()
{
    userImage->filterNoir();
}

void MainWindow::on_cwButton_clicked()
{
    userImage->rotateClockwise();
}


void MainWindow::on_ccwButton_clicked()
{
    userImage->rotateCounter();
}


void MainWindow::on_pushButton_clicked()
{
    userImage->undo();
}


void MainWindow::on_pushButton_2_clicked()
{
    userImage->redo();
}





void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    QString name = arg1;
    userImage->setName(name);
}


void MainWindow::on_comboBox_textActivated(const QString &arg1)
{
    QString type = arg1;
    userImage->setType(type);
}
void MainWindow::on_action_triggered()
{
    userImage->rotateClockwise();
}


void MainWindow::on_action_2_triggered()
{
    userImage->rotateCounter();
}


void MainWindow::on_actionBlur_triggered()
{
    userImage->filterNoir();
}


void MainWindow::on_actionImport_Image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),

                                                    "/home",

                                                    tr("Images (*.jpg *.gif *.png *.bnp *.tif )"));
    ;
    userImage->loadImage(fileName);
}


void MainWindow::on_actionUndo_triggered()
{
    userImage->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    userImage->redo();
}

