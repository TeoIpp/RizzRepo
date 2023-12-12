//hello
#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include "qobject.h"
#include <QImage> // designed and optimized for I/O, and for direct pixel access and manipulation,
#include <QPixmap> // designed and optimized for showing images on screen.
#include <QBitmap> // convenience class that inherits QPixmap, ensuring a depth of 1.
#include <QPicture> // paint device that records and replays QPainter commands.
#include <QStack>
#include <QVector>
#include <QInputDialog>

#include <QFileDialog>
#include <QTransform>

#include <QStringList> // for batch edit testing/implementation
#include <string>

#include <QMessageBox>

class ImageEditor : public QObject {
    Q_OBJECT

public:
    explicit ImageEditor(QObject *parent = nullptr);
    QList<QImage> image;
    int imgSize;
    int displayedImage = 0;
public slots:
    void loadImage(QStringList fileName);
    void filterNoir();
    void rotateClockwise();
    void rotateCounter();
    void undo();
    void redo();
    void filterSepia();
    void filterBlur();
    // add functions here , also add button in mainwindow.h

private:
    QList<QStack<QImage>> editHist;
    QList<QStack<QImage>> undoHist;
    QString filePath;
};



#endif // IMAGEEDITOR_H
