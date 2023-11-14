#include "imageeditor.h"

ImageEditor::ImageEditor(QObject *parent) : QObject(parent) {
    // constructor if needed
}

void ImageEditor::loadImage(QString fileName) {

    filePath = fileName;
    QImage tempImage(filePath);

    image = tempImage;

    emit updateDisplay(image); // updates image viewer
}

void ImageEditor::filterNoir(){

    QImage noir = image.convertToFormat(QImage::Format_Grayscale8);
    image = noir;

    emit updateDisplay(image);
}

void ImageEditor::rotateClockwise() {

    QImage rotate = image.transformed(QTransform().rotate(90));
    image = rotate;

    emit updateDisplay(image);
}

void ImageEditor::rotateCounter() {

    QImage rotate = image.transformed(QTransform().rotate(270));
    image = rotate;

    emit updateDisplay(image);
}
