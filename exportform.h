#ifndef EXPORTFORM_H
#define EXPORTFORM_H

#include <QWidget>

namespace Ui {
class exportForm;
}

class exportForm : public QWidget
{
    Q_OBJECT

public:
    explicit exportForm(QWidget *parent = nullptr);
    ~exportForm();

private:
    Ui::exportForm *ui;
};

#endif // EXPORTFORM_H
