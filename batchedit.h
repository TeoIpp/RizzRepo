#ifndef BATCHEDIT_H
#define BATCHEDIT_H

#include <QDialog>
#include "imageeditor.h"

namespace Ui {
class batchedit;
}

class batchedit : public QDialog
{
    Q_OBJECT

public:
    explicit batchedit(QWidget *parent = nullptr);
    ~batchedit();
    ImageEditor batch;

    QStringList open;
    std::string save;

private slots:
    void executeBatch();

    void on_openPath_clicked();

    void on_savePath_clicked();

    void on_execute_accepted();

private:
    Ui::batchedit *ui;
};

#endif // BATCHEDIT_H
