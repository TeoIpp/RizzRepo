#include "imageeditor.h"

ImageEditor::ImageEditor(QObject *parent) : QObject(parent) {
    // constructor if needed
}

void ImageEditor::loadImage(QStringList files) {

    imgSize = files.size();
    displayedImage = 0;

    for (int i = 0; i < imgSize; i++) {
        QImage tempImage(files[i]);
        QStack<QImage> tempEditHist;
        QStack<QImage> tempUndoHist;
        image.push_back(tempImage);
        editHist.push_back(tempEditHist);
        undoHist.push_back(tempUndoHist);
    }
}

void ImageEditor::filterNoir(){

    for (int i = 0; i < imgSize; i++) {
        QImage noir = image[i].convertToFormat(QImage::Format_Grayscale8);
        editHist[i].push(image[i]);
        image[i] = noir;
    }
}

void ImageEditor::undo(){

        if (editHist[displayedImage].isEmpty()==false){
            for (int i = 0; i < imgSize; i++) {
                undoHist[i].push(image[i]);
                image[i] = editHist[i].top();
                editHist[i].pop();
            }
        }
        else
        {
            QMessageBox::information(nullptr, tr("No Undo Actions"), tr("There are no more actions to undo."));
        }        
}

void ImageEditor::redo(){

        if (undoHist[displayedImage].isEmpty()==false){
            for (int i = 0; i < imgSize; i++) {
            editHist[i].push(image[i]);
            image[i] = undoHist[i].top();
            undoHist[i].pop();
            }
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

    for (int i = 0; i < imgSize; i++) {
        QImage rotate = image[i].transformed(QTransform().rotate(90));
        editHist[i].push(image[i]);
        image[i] = rotate;
    }
}

void ImageEditor::rotateCounter() {

    for (int i = 0; i < imgSize; i++) {
        QImage rotate = image[i].transformed(QTransform().rotate(270));
        editHist[i].push(image[i]);
        image[i] = rotate;
    }
}

void ImageEditor::filterSepia()
{


    for (int i = 0; i < imgSize; i++) {
        editHist[i].push(image[i]);
        for (int y = 0; y < image[i].height(); ++y) {
            for (int x = 0; x < image[i].width(); ++x) {
                QRgb pixel = image[i].pixel(x, y);
                int oldRed = qRed(pixel);
                int oldGreen = qGreen(pixel);
                int oldBlue = qBlue(pixel);
                int newRed = qBound(0, static_cast<int>(0.393 * oldRed + 0.769 * oldGreen + 0.189 * oldBlue), 255);
                int newGreen = qBound(0, static_cast<int>(0.349 * oldRed + 0.686 * oldGreen + 0.168 * oldBlue), 255);
                int newBlue = qBound(0, static_cast<int>(0.272 * oldRed + 0.534 * oldGreen + 0.131 * oldBlue), 255);
                image[i].setPixel(x, y, qRgb(newRed, newGreen, newBlue));
            }
        }
    }
}

void ImageEditor::filterBlur()
{
    int kernelSize = 3;
    int kernelHalfSize = kernelSize / 2;
    for (int i = 0; i < imgSize; i++) {
        editHist[i].push(image[i]);
        for (int y = kernelHalfSize; y < image[i].height() - kernelHalfSize; ++y) {
            for (int x = kernelHalfSize; x < image[i].width() - kernelHalfSize; ++x) {
               int totalR = 0, totalG = 0, totalB = 0;

               for (int dy = -kernelHalfSize; dy <= kernelHalfSize; ++dy) {
                   for (int dx = -kernelHalfSize; dx <= kernelHalfSize; ++dx) {
                       QRgb pixel = image[i].pixel(x + dx, y + dy);
                       totalR += qRed(pixel);
                       totalG += qGreen(pixel);
                       totalB += qBlue(pixel);
                   }
               }

              int count = kernelSize * kernelSize;
              image[i].setPixel(x, y, qRgb(totalR / count, totalG / count, totalB / count));
            }
        }
    }
}

void ImageEditor::crop(int x, int y, int w, int h) {
    for (int i = 0; i < imgSize; i++) {
        editHist[i].push(image[i]);
        image[i] = image[i].copy(x, y, w, h);
    }
}


