#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>
#include "imageeditor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateDisplayedImage();

//public slots:
    //void updateDisplayedImage(const QImage& newImage);

private slots:
    // add buttons/actions here

    void on_actionUndo_triggered();
    void on_actionRedo_triggered();

    void on_rotateR_triggered();
    void on_rotateL_triggered();

    void on_actionImport_Image_triggered();
    void on_actionSave_Image_triggered();
    void imgSaveToFile(QString type, QString imgDir, QString name);

    void on_actionSepia_triggered();
    void on_actionBlur_triggered();
    void on_actionNoir_triggered();

    void on_actionBatch_Test_triggered();
private:
    Ui::MainWindow *ui;
    ImageEditor *userImage;
};
#endif // MAINWINDOW_H
