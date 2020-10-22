#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::updateValues);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::updateValues() {
    simDelay = ui->simDelaySpinBox->text();
    itPerCycle = ui->itPerCycleSpinBox->text();
}
