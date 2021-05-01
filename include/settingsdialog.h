#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    QString getSimDelay() { return simDelay; };
    QString getItPerCycle() { return itPerCycle; };
    bool getEnableCmakeOut() { return enableCmakeOut; };

private:
    Ui::SettingsDialog *ui;

    QString simDelay = "1";
    QString itPerCycle = "10";
    bool enableCmakeOut = false;

private slots:
    void updateValues();
};

#endif // SETTINGSDIALOG_H
