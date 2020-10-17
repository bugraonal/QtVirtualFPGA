#include "fileselectdialog.h"
#include "ui_fileselectdialog.h"

FileSelectDialog::FileSelectDialog(QString copyDirPath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileSelectDialog),
    copyDir(copyDirPath)
{
    ui->setupUi(this);

    for (auto f : copyDir.entryList()) {
        if (f.compare(".") != 0 && f.compare("..") != 0)
            addTableItem(copyDir.filePath(f));
    }

    connect(ui->addModuleButton, &QPushButton::clicked, this, &FileSelectDialog::addModules);
    connect(ui->removeModuleButton, &QPushButton::clicked, this, &FileSelectDialog::removeModules);
    connect(ui->openModuleButton, &QPushButton::clicked, this, &FileSelectDialog::openModules);
    connect(ui->topWrapperBrowseButton, &QPushButton::clicked, this, &FileSelectDialog::browseTopWrapper);
    connect(ui->topWrapperCreateButton, &QPushButton::clicked, this, &FileSelectDialog::createTopWrapper);
    connect(ui->doneButton, &QPushButton::clicked, this, &QDialog::accept);

}

FileSelectDialog::~FileSelectDialog()
{
    delete ui;
}

void FileSelectDialog::addTableItem(QString path) {
    QTableWidget *table = ui->modulesTable;
    int row = table->rowCount() - 1;
    table->insertRow(1);
    auto nameItem = new QTableWidgetItem(path.section("/", -1, -1));
    table->setItem(row, 0, nameItem);
    auto pathItem = new QTableWidgetItem(path);
    table->setItem(row, 1, pathItem);
}

void FileSelectDialog::addModules() {
    auto fileDiag = new QFileDialog;
    fileDiag->setNameFilter("Verilog (*.v *.sv)");
    fileDiag->setFileMode(QFileDialog::ExistingFiles);
    if (fileDiag->exec()) {
        for (auto f : fileDiag->selectedFiles()) {
            addTableItem(f);
            QFile copyFile(f);
            copyFile.copy(copyDir.filePath(f.section("/", -1, -1)));
        }
    }
}

void FileSelectDialog::removeModules() {
    QTableWidget *table = ui->modulesTable;
    QList<QTableWidgetItem *> range = table->selectedItems();
    int row;
    QListIterator<QTableWidgetItem *> rangeIt(range);
    while(rangeIt.hasNext()) {
        QTableWidgetItem* item = rangeIt.next();
        row = item->row();
        QString filename = table->itemAt(0, row)->text();
        QFile (copyDir.filePath(filename)).remove();
        table->removeRow(row);
    }
}

void FileSelectDialog::openModules() {
    QTableWidget *table = ui->modulesTable;
    QList<QTableWidgetItem *> range = table->selectedItems();
    int row;
    QListIterator<QTableWidgetItem *> rangeIt(range);
    while(rangeIt.hasNext()) {
        QTableWidgetItem* item = rangeIt.next();
        row = item->row();
        QString filename = table->itemAt(0, row)->text();
        QDesktopServices::openUrl(QUrl(copyDir.filePath(filename)));
    }
}

void FileSelectDialog::browseTopWrapper() {
    auto fileDiag = new QFileDialog;
    fileDiag->setNameFilter("Verilog (*.v *.sv)");
    fileDiag->setFileMode(QFileDialog::ExistingFile);
    if (fileDiag->exec()) {
        QFile wrapper(fileDiag->selectedFiles()[0]);
        ui->topWrapperLineEdit->setText(fileDiag->selectedFiles()[0]);
        wrapper.copy(copyDir.filePath("top_wrapper.v"));
    }
}

void FileSelectDialog::createTopWrapper() {
    // TODO: create top_wrapper template resource
    QFile templ(":/projectFiles/projectFiles/top_wrapper_template.v");
    templ.copy(copyDir.filePath("top_wrapper.v"));
    QDesktopServices::openUrl(copyDir.filePath("top_wrapper.v"));
    ui->topWrapperLineEdit->setText(copyDir.filePath("top_wrapper.v"));
}
