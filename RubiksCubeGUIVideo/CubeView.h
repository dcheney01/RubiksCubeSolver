#ifndef CUBEVIEW_H
#define CUBEVIEW_H

#include "FaceView.h"

class CubeView {
public:
    CubeView(QGraphicsScene *scene, QString cube) {
        L = new FaceView(scene, 0, 135);
        U = new FaceView(scene, 135, 0);
        F = new FaceView(scene, 135, 135);
        D = new FaceView(scene, 135, 270);
        R = new FaceView(scene, 270, 135);
        B = new FaceView(scene, 405, 135);

        setCube(cube);
    }

    void setCube(QString input) {
        U->setFace(input.left(9));
        L->setFace(input.mid(9,17));
        F->setFace(input.mid(18,26));
        R->setFace(input.mid(27,35));
        B->setFace(input.mid(36,44));
        D->setFace(input.right(9));
    }

private:
    FaceView *L;
    FaceView *R;
    FaceView *U;
    FaceView *D;
    FaceView *F;
    FaceView *B;

};





#endif // CUBEVIEW_H
