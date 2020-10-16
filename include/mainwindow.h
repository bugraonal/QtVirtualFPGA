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

#include <array>
#include <string>
#include <iostream>
#include <stdint.h>
#include <unistd.h>

//#include "modelthread.h"
#include "model.h"
#include "indexedbutton.h"
#include "indexedswitch.h"

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

    void on_StartButton_clicked();

    void parseDataReceived(QString data);

    void on_StopButton_clicked();

signals:
    void sendDataToSend(QString data);

private:
    Ui::MainWindow *ui;
    QBoxLayout *buttonsLayout;
    QBoxLayout *switchesLayout;
    QBoxLayout *ledsLayout;
    QBoxLayout *digitsLayout;

    //ModelController controller;
    Model model;
    QTemporaryDir tempDir;

    int numButtons;
    int numSwitches;
    int numLeds;
    int numDigits;
    QString inputFileName;
    bool modelRunning = 0;
    QString dataToSend = "0 0";

    void configureGroups();
    void runModel();
    QString createDataToSend();
    //void parseDataReceived(QByteArray &data);

    template<bool isBtn>
    void dataChanged(int k);

    int decodeDigit(quint8 byte);


};
#endif // MAINWINDOW_H
