#ifndef INDEXEDBUTTON_H
#define INDEXEDBUTTON_H

#include <QWidget>
#include <QPushButton>

class IndexedButton : public QPushButton
{
    Q_OBJECT
public:
    explicit IndexedButton(int index, QWidget *parent = nullptr)
        : QPushButton(parent)
        , index(index)
    {
        connect(this, &QPushButton::pressed, this, &IndexedButton::handleClick);
        connect(this, &QPushButton::released, this, &IndexedButton::handleClick);
    };
;

signals:
    void indexClicked(int index,int unused);

private slots:
    void handleClick() {emit indexClicked(index,0);};

private:
    int index;
};

#endif // INDEXEDBUTTON_H
