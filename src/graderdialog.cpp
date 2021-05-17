#include "graderdialog.h"
#include "./ui_graderdialog.h"

GraderDialog::GraderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraderDialog)
{
    ui->setupUi(this);

    connect(ui->fileAddButton, &QPushButton::pressed, this, &GraderDialog::addFile);
    connect(ui->fileRemoveButton, &QPushButton::pressed, this, &GraderDialog::removeFiles);
    connect(ui->folderBrowseButton, &QPushButton::pressed, this, &GraderDialog::browseFolder);
    connect(ui->findFilesButton, &QPushButton::pressed, this, &GraderDialog::findFiles);
}

GraderDialog::~GraderDialog()
{
    delete ui;
}

QStringList GraderDialog::nextFiles()
{
    if (index < fileList.size())
        return fileList[index++];
    return QStringList();
}

QStringList GraderDialog::previousFiles()
{
    if (index > 0)
        return fileList[--index];
    return QStringList();
}

void GraderDialog::addItem(QString fileName)
{
    QTableWidget *table = ui->filesTableWidget;
    int row = table->rowCount() - 1;
    table->insertRow(row);
    auto nameItem = new QTableWidgetItem(fileName);
    table->setItem(row, 0, nameItem);
}

void GraderDialog::addFile()
{
    addItem(ui->fileLineEdit->text());
    fileNameList.append(ui->fileLineEdit->text());
}

void GraderDialog::removeFiles()
{
    QTableWidget *table = ui->filesTableWidget;
    QList<QTableWidgetItem *> range = table->selectedItems();
    int row;
    QListIterator<QTableWidgetItem *> rangeIt(range);
    while(rangeIt.hasNext()) {
        QTableWidgetItem* item = rangeIt.next();
        row = item->row();
        table->removeRow(row);
    }
}

void GraderDialog::browseFolder()
{
    auto fileDiag = new QFileDialog;
    fileDiag->setFileMode(QFileDialog::Directory);
    if (fileDiag->exec()) {
        submissionFolder = new QDir(fileDiag->selectedFiles()[0]);
        ui->folderLineEdit->setText(submissionFolder->path());
    }
}

void GraderDialog::findFiles()
{
    QString folderPattern = ui->folderPatternLineEdit->text();
    QDir path = *submissionFolder;
    auto patterns = folderPattern.split('/');
    QStringList filters;
    QStringList dirs, dirsPrev;
    filters.append(patterns[0]);
    path.setNameFilters(filters);
    dirsPrev = path.entryList();
    patterns.removeFirst();
    patterns.removeLast();
    for (auto pattern : patterns) {
        filters.clear();
        filters.append(pattern);
        path.setNameFilters(filters);
        dirs.clear();
        for (auto d : dirsPrev) {
            path.cd(d);
            auto matching = path.entryList();
            for (auto m : matching)
                dirs.append(d + "/" + m);
            path.cdUp();
        }
        dirsPrev = dirs;
    }
    fileList.clear();
    filters.clear();
    filters.append(fileNameList);
    path.setNameFilters(filters);
    for (auto d : dirsPrev) {
        path.cd(d);
        auto matching = path.entryList();
        for (auto &m : matching)
            m = submissionFolder->path() +  "/" + d + '/' + m;
        fileList.append(matching);
        path.cdUp();
    }
    QString msg;
    msg.append("Found ");
    msg.append(QString::number(fileList.size()));
    msg.append(" files");
    ui->fileStatusLabel->setText(msg);
}
