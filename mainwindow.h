#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

public slots:
    void updateDisplayedImage(const QImage& newImage);


private slots:
    void on_displayButton_clicked();
    void on_noirButton_clicked();
    void on_cwButton_clicked();
    void on_ccwButton_clicked();
    // add buttons here

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

    void on_actionBlur_triggered();

    void on_actionImport_Image_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();



    void on_actionSave_as_jpg_triggered();

    void on_actionSave_as_png_triggered();

private:
    Ui::MainWindow *ui;
    ImageEditor *userImage;
};
#endif // MAINWINDOW_H
