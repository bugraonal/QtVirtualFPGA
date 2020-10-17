#ifndef FILESELECTDIALOG_H
#define FILESELECTDIALOG_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QList>

namespace Ui {
class FileSelectDialog;
}

class FileSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileSelectDialog(QString copyDirPath, QWidget *parent = nullptr);
    ~FileSelectDialog();

private:
    Ui::FileSelectDialog *ui;
    QStringList modulesList;
    QString topWrapper;
    QDir copyDir;

    void addTableItem(QString path);

private slots:
    void addModules();
    void removeModules();
    void openModules();
    void browseTopWrapper();
    void createTopWrapper();
};

#endif // FILESELECTDIALOG_H
