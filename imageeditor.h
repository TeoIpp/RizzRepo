#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include "qobject.h"
#include <QDebug>
#include <QImage> // designed and optimized for I/O, and for direct pixel access and manipulation,
#include <QPixmap> // designed and optimized for showing images on screen.
#include <QBitmap> // convenience class that inherits QPixmap, ensuring a depth of 1.
#include <QPicture> // paint device that records and replays QPainter commands.
#include <QStack>
#include <QMenu>

#include <QFileDialog>
#include <QTransform>

#include <string>

// TESTING if SSH key will push -Michael
// Pushing

class ImageEditor : public QObject {
    Q_OBJECT

public:
    explicit ImageEditor(QObject *parent = nullptr);
public slots:
    void loadImage(QString fileName);
    void filterNoir();
    void rotateClockwise();
    void rotateCounter();
    void undo();
    void redo();
    void imgExport(QString dirPath);
    void setName(QString name);
    void setType(QString type);
    // add functions here , also add button in mainwindow.h
signals:
    void updateDisplay(const QImage& newImage);
private:
    QStack<QImage> editHist;
    QStack<QImage> undoHist;
    QString filePath;
    QString newName;
    QString fileType;
    QImage image;
};



#endif // IMAGEEDITOR_H
