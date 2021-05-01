#ifndef SEVENSEGMENTDISPLAY_H
#define SEVENSEGMENTDISPLAY_H

#include <QWidget>

namespace Ui {
class SevenSegmentDisplay;
}

class SevenSegmentDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit SevenSegmentDisplay(QWidget *parent = nullptr);
    ~SevenSegmentDisplay();

private:
    Ui::SevenSegmentDisplay *ui;
};

#endif // SEVENSEGMENTDISPLAY_H
