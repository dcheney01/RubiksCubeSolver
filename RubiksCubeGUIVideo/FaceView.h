#ifndef FACEVIEW_H
#define FACEVIEW_H

#include <QGraphicsScene>
#include <QVector>

#include "CubieView.h"


class FaceView {

public:
    FaceView(QGraphicsScene *scene, int x, int y) {
        for (int i=0; i<3; i++) {
            QVector<CubieView*> temp;
            for (int j=0; j<3; j++) {
                temp.push_back(new CubieView(x + i*SIDE_LENGTH, y + j*SIDE_LENGTH));
                scene->addItem(temp[j]);
            }
            cubies.push_back(temp);
        }
    }

    void setFace(QString input) {
        int position = 0;
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                cubies[j][i]->setColor(input.at(position));
                position++;
            }
        }
    }

private:
    const int SIDE_LENGTH=45;
    QVector<QVector<CubieView*>> cubies;

};




#endif // FACEVIEW_H
