#ifndef VERSIONMESSAGE_H
#define VERSIONMESSAGE_H

#include <QWidget>
#include <QMessageBox>
#include "version.h"

class VersionMessage : public QMessageBox
{
    Q_OBJECT
public:
    explicit VersionMessage(QWidget *parent = nullptr) {
        this->setText(VERSION);
    }

signals:

};

#endif // VERSIONMESSAGE_H
