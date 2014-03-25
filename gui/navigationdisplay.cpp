#include "navigationdisplay.h"

NavigationDisplay::NavigationDisplay(QObject *parent) : QObject(parent) {
    images = new QHash<bool, QList<QPixmap> >;

    /* preload images to memory */
    this->loadImages();

    dir << "up" << "nw" << "n" << "ne" << "out" << "w" << "ap" << "e" << "down" << "sw" << "s" << "se";
    state << false << false << false << false << false << false << false << false << false << false << false << false;
}

void NavigationDisplay::updateState(QList<QString> directions) {
    for(int i = 0; i < state.size(); i++) {
        /* dont update auto pilot (mid circle) */
        if(i != 6) {
            if(directions.contains(dir[i])){
                state[i] = true;
            } else {
                state[i] = false;
            }
        }
    }
}

void NavigationDisplay::setAutoPilot(bool enable) {
    state[6] = enable;
}

void NavigationDisplay::loadImages() {
    active << QPixmap(A_UP) << QPixmap(A_NW) << QPixmap(A_N) << QPixmap(A_NE)
           << QPixmap(A_OUT) << QPixmap(A_W) << QPixmap(A_C) << QPixmap(A_E)
           << QPixmap(A_DOWN) << QPixmap(A_SW) << QPixmap(A_S) << QPixmap(A_SE);

    images->insert(true, active);

    inactive << QPixmap(I_UP) << QPixmap(I_NW) << QPixmap(I_N) << QPixmap(I_NE)
             << QPixmap(I_OUT) << QPixmap(I_W) << QPixmap(I_C) << QPixmap(I_E)
             << QPixmap(I_DOWN) << QPixmap(I_SW) << QPixmap(I_S) << QPixmap(I_SE);

    images->insert(false, inactive);
}

QPixmap NavigationDisplay::paint() {
    QPixmap collage(94, 69);
    collage.fill(Qt::transparent);

    QPainter painter(&collage);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    int x = 0, y = 0, z = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            QPixmap image = images->value(state.at(z)).at(z);
            painter.drawPixmap(x, y, image);

            x += image.width();
            z++;
       }
       x = 0, y += 20;
    }
    painter.end();

    return collage;
}

NavigationDisplay::~NavigationDisplay(){
    delete images;
}
