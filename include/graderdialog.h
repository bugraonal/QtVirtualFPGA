#ifndef GRADERDIALOG_H
#define GRADERDIALOG_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QUrl>
#include <QList>
#include <QRegExp>
#include <QTableWidget>

#include <stdlib.h>

namespace Ui {
class GraderDialog;
}

class GraderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GraderDialog(QWidget *parent = nullptr);
    ~GraderDialog();

    QStringList nextFiles();
    QStringList previousFiles();
    int getFileListSize();

private:
    Ui::GraderDialog *ui;
    QStringList fileNameList;
    QList<QStringList> fileList;
    int index = 0;
    QDir *submissionFolder;

    void addItem(QString fileName);


private slots:
    void addFile();
    void removeFiles();
    void browseFolder();
    void findFiles();
};

#endif // GRADERDIALOG_H
