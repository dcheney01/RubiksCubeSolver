#ifndef CUBIEVIEW_H
#define CUBIEVIEW_H

#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QColor>

class CubieView : public QGraphicsRectItem {
    public:
        CubieView(int x, int y) {
            setRect(x, y, SIDE_LENGTH, SIDE_LENGTH);
            pen.setWidth(CUBIE_OUTLINE);
            setPen(pen);
        }

        void setColor(QChar color) {
            setBrush(getColorCode(color));
        }


    private:
        const int SIDE_LENGTH=45, CUBIE_OUTLINE=5;
        QPen pen;

        QColor const getColorCode(QChar color) {
            // Magic numbers to get the RGB or Qt defined colors
            switch(color.unicode()) {
            case('G'): // green
                return QColor(25,192,49);
            case('B'): // blue
                return QColor(23,84,255);
            case('R'): // red
                return QColor(203,49,49);
            case('O'): // orange
                return QColor("orange");
            case('Y'): // yellow
                return Qt::yellow;
            case('W'): // white
                return Qt::white;
            default:
                return Qt::black; // means something went wrong
            }
        }
};

#endif // CUBIEVIEW_H
