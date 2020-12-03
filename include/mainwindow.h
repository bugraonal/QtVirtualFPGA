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
#include <io.h>

#include "model.h"
#include "indexedbutton.h"
#include "indexedswitch.h"
#include "fileselectdialog.h"
#include "settingsdialog.h"
#include "customcentralwidget.h"

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

protected:


private:
    Ui::MainWindow *ui;
    QBoxLayout *buttonsLayout;
    QBoxLayout *switchesLayout;
    QBoxLayout *ledsLayout;
    QBoxLayout *digitsLayout;

    Model *model;
    QTemporaryDir tempDir;

    enum dataID { BUTTON = 0, SWITCH = 1, MOUSEMOVE = 2, MOUSEPRESS = 3, MOUSERELEASE = 4 };
    enum mouseButton {LEFT = 1, RIGHT = 2, MIDDLE = 3 };
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

    template<int id>
    void dataChanged(int k, int n=0);

    int decodeDigit(quint8 byte);


};
#endif // MAINWINDOW_H
