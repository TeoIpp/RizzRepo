#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "imageeditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->imgL->setVisible(false);
    ui->imgR->setVisible(false);

    ui->verticalSlider->setVisible(false);
    ui->horizontalSlider->setVisible(false);
    //userImage = new ImageEditor(this);
  // Connect the button click to the ImageEditor slot
  //  connect(ui->displayButton, SIGNAL(clicked()), userImage, SLOT(addImage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDisplayedImage()
{
    // Update the QLabel or any other widget that displays the image
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    QPixmap pixMap = QPixmap::fromImage(userImage->image[userImage->displayedImage]);
    int width = pixMap.width();
    int height = pixMap.height();
    float ratio = float(width) / float(height);
    if(height > screenGeometry.height() - 100)
    {
        height = screenGeometry.height() - 100;
        width = int(height * ratio);
    }
    else if(width > screenGeometry.width() - 100)
    {
        width = screenGeometry.width() - 100;
        height = int(width / ratio);
    }

    ui->displayLabel->setPixmap(pixMap);
    ui->displayLabel->setMinimumSize(width, height);
    ui->displayLabel->setMaximumSize(width, height);
    ui->displayLabel->setScaledContents(true);
}

void MainWindow::on_actionImport_Image_triggered()
{
    userImage = new ImageEditor(this);
    QStringList fileName = QFileDialog::getOpenFileNames(this, tr("Open File"),

                                                    "/home",

                                                    tr("Images (*.jpg *.gif *.png *.bmp *.tif )"));
    userImage->loadImage(fileName);
    if (fileName.size() > 1) {
        ui->imgL->setVisible(true);
        ui->imgR->setVisible(true);
    } else {
        ui->imgL->setVisible(false);
        ui->imgR->setVisible(false);
    }
    ui->verticalSlider->setVisible(true);
    ui->horizontalSlider->setVisible(true);
    updateDisplayedImage();
}


void MainWindow::on_actionUndo_triggered()
{
    userImage->undo();
    updateDisplayedImage();
}


void MainWindow::on_actionRedo_triggered()
{
    userImage->redo();
    updateDisplayedImage();
}

void MainWindow::on_actionNoir_triggered()
{
    userImage->filterNoir();
    updateDisplayedImage();
}

void MainWindow::on_actionSepia_triggered()
{
    userImage->filterSepia();
    updateDisplayedImage();
}

void MainWindow::on_actionBlur_triggered()
{
    userImage->filterBlur();
    updateDisplayedImage();
}

void MainWindow::imgSaveToFile(QString type, QString imgDir, QString name){
    for (int i = 0; i < userImage->imgSize; i++) {
        if (!userImage->image[i].save(imgDir+"\\"+name+QString::number(i)+type)) {
            QMessageBox::warning(this, tr("Error"), tr("Failed to save image."));
        }
    }
    QMessageBox::information(this, tr("Success"), tr("Image saved successfully."));
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
    updateDisplayedImage();
}
void MainWindow::on_rotateR_triggered()
{
    userImage->rotateClockwise();
    updateDisplayedImage();
}

void MainWindow::on_imgL_clicked()
{
    if (userImage->displayedImage == 0) {
        userImage->displayedImage = (userImage->imgSize)-1;
    } else {
        userImage->displayedImage -= 1;
    }
    updateDisplayedImage();
}

void MainWindow::on_imgR_clicked()
{
    if (userImage->displayedImage == (userImage->imgSize)-1) {
        userImage->displayedImage = 0;
    } else {
        userImage->displayedImage += 1;
    }
    updateDisplayedImage();
}

void MainWindow::on_actionCrop_triggered()
{
    int x = 0;
    int y = 0;
    int w = 500;
    int h = 750;

    userImage->crop(x, y, w, h);
    updateDisplayedImage();
}

//ADDED THIS FOR SLIDER
void MainWindow::on_verticalSlider_sliderReleased()
{
    int sliderValue = ui->verticalSlider->value();
    qreal brightnessValue = static_cast<qreal>(sliderValue) / 100.0;

    userImage->setBrightness(brightnessValue);
    updateDisplayedImage();
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    int sliderValue = ui->horizontalSlider->value();
    qreal saturation = static_cast<qreal>(sliderValue) / 100.0;

    userImage->setSaturation(saturation);
    updateDisplayedImage();
}

