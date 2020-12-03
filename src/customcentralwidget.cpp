#include "customcentralwidget.h"

CustomCentralWidget::CustomCentralWidget(QWidget *parent) : QWidget(parent) {
    this->setMouseTracking(true);
}

void CustomCentralWidget::mouseMoveEvent(QMouseEvent *e) {
    emit mouseMoved(e->globalX(), e->globalY());
}

void CustomCentralWidget::mousePressEvent(QMouseEvent *e) {
    emit mousePressed(e->button());
}

void CustomCentralWidget::mouseReleaseEvent(QMouseEvent *e) {
    emit mouseReleased(e->button());
}
