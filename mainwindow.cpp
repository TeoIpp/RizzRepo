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
    ui->displayLabel->setScaledContents(false);
}

void MainWindow::on_displayButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),

                                                    "/home",

                                                    tr("Images (*.jpg *.gif *.png *.bnp *.tif )"));
    ;
    userImage->loadImage(fileName);
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

void MainWindow::on_actionNoir_triggered()
{
    userImage->filterNoir();
}

void MainWindow::on_actionSepia_triggered()
{

    userImage->filterSepia();

}

void MainWindow::on_actionBlur_triggered()
{
    userImage->filterBlur();
}

void MainWindow::imgSaveToFile(QString type, QString imgDir, QString name){

    QPixmap image = ui->displayLabel->pixmap();
    if (image.save(imgDir+"\\"+name+type))
    {
        QMessageBox::information(this, tr("Success"), tr("Image saved successfully."));
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("Failed to save image."));
    }
}
void MainWindow::on_actionSave_Image_triggered()
{
    QString imgDir;
    QString name;
    QString type;

    QPixmap image = ui->displayLabel->pixmap();
    if (!image.isNull())
    {
        imgDir = QFileDialog::getExistingDirectory(this, tr("Select Directory"),
                                                   "/home",
                                                   QFileDialog::ShowDirsOnly
                                                       | QFileDialog::DontResolveSymlinks);
        bool ok;
        name = QInputDialog::getText(this, tr("Input File Name"),
                                     tr("File name:"), QLineEdit::Normal,
                                     QDir::home().dirName(), &ok);

        QStringList types;
        types << tr(".jpg") << tr(".png") << tr(".bmp") << tr(".tiff") << tr(".gif");
        type = QInputDialog::getItem(this, tr("Select File-Type"),
                                     tr("File-Type: "), types, 0, false, &ok);

        imgSaveToFile(type,imgDir,name);
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("No image to save."));
    }
}

void MainWindow::on_rotateL_triggered()
{
    userImage->rotateCounter();
}
void MainWindow::on_rotateR_triggered()
{
    userImage->rotateClockwise();
}




