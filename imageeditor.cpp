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

void ImageEditor::imgExport(QString dirPath) {

    filePath = dirPath;

    image.save(filePath+"\\"+newName+fileType);
}

void ImageEditor::filterNoir(){


    QImage noir = image.convertToFormat(QImage::Format_Grayscale8);
    editHist.push(image);
    image = noir;
    emit updateDisplay(image);
}

void ImageEditor::undo(){

    if (editHist.isEmpty()==false){
        undoHist.push(image);
        image = editHist.top();
        emit updateDisplay(editHist.pop());
    }
}

void ImageEditor::redo(){

    if (undoHist.isEmpty()==false){
        editHist.push(image);
        image = undoHist.top();
        emit updateDisplay(undoHist.pop());
    }
}
// + - + - +
// . + . + .
// . . - .

void ImageEditor::rotateClockwise() {

    QImage rotate = image.transformed(QTransform().rotate(90));
    editHist.push(image);
    image = rotate;

    emit updateDisplay(image);
}

void ImageEditor::rotateCounter() {

    QImage rotate = image.transformed(QTransform().rotate(270));
    editHist.push(image);
    image = rotate;

    emit updateDisplay(image);
}

void ImageEditor::setName(QString name){
    newName = name;
}
void ImageEditor::setType(QString type){
    fileType = type;
}
