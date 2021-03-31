#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QBoxLayout>
#include <QLCDNumber>
#include <QFileDialog>
#include <QTemporaryDir>
#include <QFile>
#include <QProcess>
#include <QTextStream>
#include <QMouseEvent>

#include <array>
#include <string>
#include <iostream>
#include <stdint.h>
#include <unistd.h>

#include "model.h"
#include "indexedbutton.h"
#include "indexedswitch.h"
#include "fileselectdialog.h"
#include "settingsdialog.h"
#include "versionmessage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_applyConfigButton_clicked();

    void openFile();

    void compileAndRunModel();

    void parseDataReceived(QString data);

    void stopModel();

    void openSettingsWindow();

signals:
    void sendDataToSend(QString data);

//protected:
//    void mouseMoveEvent(QMouseEvent *e);
//    void mousePressEvent(QMouseEvent *e);
//    void mouseReleaseEvent(QMouseEvent *e);

private:
    Ui::MainWindow *ui;
    QBoxLayout *buttonsLayout;
    QBoxLayout *switchesLayout;
    QBoxLayout *ledsLayout;
    QBoxLayout *digitsLayout;

    Model *model;
    QTemporaryDir tempDir;

    int numButtons;
    int numSwitches;
    int numLeds;
    int numDigits;
    QStringList inputFileNames;
    bool firstModel = 1;
    QString dataToSend = "0 0";
    QString simDelay = "1";
    QString itPerCycle = "10";

    void configureGroups();
    QString createDataToSend();

    template<bool isBtn>
    void dataChanged(int k);

    int decodeDigit(quint8 byte);


};
#endif // MAINWINDOW_H
