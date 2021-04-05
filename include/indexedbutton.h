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
        //this->setFixedWidth(20);
        connect(this, &QPushButton::pressed, this, &IndexedButton::handleClick);
        connect(this, &QPushButton::released, this, &IndexedButton::handleClick);
        setStyleSheet("QPushButton {"
                      "    min-width: 30px;"
                      "    max-width: 30px;"
                      "    height: 50px;"
                      "}"
                      "QPushButton {border-image: url(:/images/images/button_unpressed.png);}"
                      "QPushButton:pressed {border-image: url(:/images/images/button_pressed.png);}");
    };
;

signals:
    void indexClicked(int index);

private slots:
    void handleClick() {emit indexClicked(index);};

private:
    int index;
};

#endif // INDEXEDBUTTON_H
