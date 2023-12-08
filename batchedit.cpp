#include "batchedit.h"
#include "ui_batchedit.h"

batchedit::batchedit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::batchedit)
{
    ui->setupUi(this);
}

batchedit::~batchedit()
{
    delete ui;
}

void batchedit::executeBatch() {

    for (int i = 0; i < open.size(); i++) {
        batch.loadImage(open[i]); // assign QImage with file directory

        if (ui->noir->checkState()) {
            batch.filterNoir();
        }
        if (ui->sepia->checkState()) {
            batch.filterSepia();
        }
        if (ui->blur->checkState()) {
            batch.filterBlur();
        }
        if (ui->rl->checkState()) {
            batch.rotateCounter();
        }
        if (ui->rr->checkState()) {
            batch.rotateCounter();
        }
        batch.image.save(open[i]); // currently only overides previous file path
        // implement new path location functionality
    }



}

void batchedit::on_openPath_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(
        this,
        "Select one or more files to open",
        "/home",
        "Images (*.jpg *.gif *.png *.bmp *.tif )");

    open = files;
}

void batchedit::on_savePath_clicked()
{
    // implement save path to new location
}

void batchedit::on_execute_accepted()
{
    executeBatch();
}

