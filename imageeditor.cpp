#include "imageeditor.h"

ImageEditor::ImageEditor(QObject *parent) : QObject(parent) {
    // constructor if needed
}



void ImageEditor::loadImage(QString fileName) {

    filePath = fileName;
    QImage tempImage(filePath);

    image = tempImage;
}

void ImageEditor::filterNoir(){


    QImage noir = image.convertToFormat(QImage::Format_Grayscale8);
    editHist.push(image);
    image = noir;
}

void ImageEditor::undo(){

    if (editHist.isEmpty()==false){
        undoHist.push(image);
        image = editHist.top();
    }
    else
    {
        QMessageBox::information(nullptr, tr("No Undo Actions"), tr("There are no more actions to undo."));
    }
}

void ImageEditor::redo(){

    if (undoHist.isEmpty()==false){
        editHist.push(image);
        image = undoHist.top();
        undoHist.pop();
    }
    else
    {
        QMessageBox::information(nullptr, tr("No Redo Actions"), tr("There are no more actions to redo."));
    }
}
// + - + - +
// . + . + .
// . . - .

void ImageEditor::rotateClockwise() {

    QImage rotate = image.transformed(QTransform().rotate(90));
    editHist.push(image);
    image = rotate;
}

void ImageEditor::rotateCounter() {

    QImage rotate = image.transformed(QTransform().rotate(270));
    editHist.push(image);
    image = rotate;
}

void ImageEditor::filterSepia()
{

    editHist.push(image);
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QRgb pixel = image.pixel(x, y);

            int oldRed = qRed(pixel);
            int oldGreen = qGreen(pixel);
            int oldBlue = qBlue(pixel);

            int newRed = qBound(0, static_cast<int>(0.393 * oldRed + 0.769 * oldGreen + 0.189 * oldBlue), 255);
            int newGreen = qBound(0, static_cast<int>(0.349 * oldRed + 0.686 * oldGreen + 0.168 * oldBlue), 255);
            int newBlue = qBound(0, static_cast<int>(0.272 * oldRed + 0.534 * oldGreen + 0.131 * oldBlue), 255);

           image.setPixel(x, y, qRgb(newRed, newGreen, newBlue));

        }
    }
}
void ImageEditor::filterBlur()
{


    editHist.push(image);

    int kernelSize = 3;
    int kernelHalfSize = kernelSize / 2;

    for (int y = kernelHalfSize; y < image.height() - kernelHalfSize; ++y) {
        for (int x = kernelHalfSize; x < image.width() - kernelHalfSize; ++x) {
           int totalR = 0, totalG = 0, totalB = 0;

           for (int dy = -kernelHalfSize; dy <= kernelHalfSize; ++dy) {
               for (int dx = -kernelHalfSize; dx <= kernelHalfSize; ++dx) {
                   QRgb pixel = image.pixel(x + dx, y + dy);
                   totalR += qRed(pixel);
                   totalG += qGreen(pixel);
                   totalB += qBlue(pixel);
               }
           }

          int count = kernelSize * kernelSize;
          image.setPixel(x, y, qRgb(totalR / count, totalG / count, totalB / count));
        }
    }
}



