#include "fileselectdialog.h"
#include "ui_fileselectdialog.h"

FileSelectDialog::FileSelectDialog(QString copyDirPath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileSelectDialog),
    copyDir(copyDirPath)
{
    ui->setupUi(this);


    // if a project has already been set up, show the modules
    for (auto f : copyDir.entryList()) {
        if (f.compare(".") != 0 && f.compare("..") != 0 && f.contains(".v"))
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
    // sub function for inserting a row element to the
    // table

    QTableWidget *table = ui->modulesTable;
    int row = table->rowCount() - 1;
    table->insertRow(row);
    auto nameItem = new QTableWidgetItem(path.section("/", -1, -1));
    table->setItem(row, 0, nameItem);
    auto pathItem = new QTableWidgetItem(path);
    table->setItem(row, 1, pathItem);
}

void FileSelectDialog::addModules() {
    // add existing module
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
    // remove added modules

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
    // open any of the added modules with system defualt text
    // editor

    // TODO: When multiple files are opened, the first(?) one
    // is opened multiple times, instead of the other ones

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
    // Open a file dialog and browse for top_wrapper

    // Remove the old wrapper
    if (QDir(copyDir.path()).entryList().contains("top_wrapper.v")) {
        QFile (copyDir.filePath("top_wrapper.v")).remove();
    }

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
    // Create a new wrapper. The template wrapper will be copied to
    // the project directory and will be opened for editing

    // Remove the old wrapper
    if (QDir(copyDir.path()).entryList().contains("top_wrapper.v")) {
        QFile (copyDir.filePath("top_wrapper.v")).remove();
    }
    QFile templ(":/projectFiles/projectFiles/top_wrapper_template.v");
    templ.copy(copyDir.filePath("top_wrapper.v"));
    QDesktopServices::openUrl(copyDir.filePath("top_wrapper.v"));
    ui->topWrapperLineEdit->setText(copyDir.filePath("top_wrapper.v"));
}
