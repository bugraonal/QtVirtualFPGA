#ifndef INDEXEDSWITCH_H
#define INDEXEDSWITCH_H

#include <QWidget>
#include <QCheckBox>

class IndexedSwitch : public QCheckBox
{
    Q_OBJECT
public:
    explicit IndexedSwitch(int index, QWidget *parent = nullptr)
        : QCheckBox(parent)
        , index(index)
    {
        connect(this, &QCheckBox::clicked, this, &IndexedSwitch::handleClick);
        setStyleSheet("QCheckBox::indicator {"
                      "    width: 20px;"
                      "    height: 60px;"
                      "}"
                     "QCheckBox::indicator:checked {image: url(:/images/images/switch_on.png);}"
                     "QCheckBox::indicator:unchecked {image: url(:/images/images/switch_off.png);}");
    };

signals:
    void indexClicked(int index);

private slots:
    void handleClick() {emit indexClicked(index);};

private:
    int index;
};

#endif // INDEXEDSWITCH_H
