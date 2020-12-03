#ifndef CUSTOMCENTRALWIDGET_H
#define CUSTOMCENTRALWIDGET_H

#include <QWidget>
#include <QMouseEvent>

#include "mainwindow.h"

class CustomCentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomCentralWidget(QWidget *parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void mouseMoved(int x, int y);
    void mousePressed(int n);
    void mouseReleased(int n);

};

#endif // CUSTOMCENTRALWIDGET_H
