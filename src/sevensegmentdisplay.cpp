#include "sevensegmentdisplay.h"
#include "ui_sevensegmentdisplay.h"

SevenSegmentDisplay::SevenSegmentDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SevenSegmentDisplay)
{
    ui->setupUi(this);
}

SevenSegmentDisplay::~SevenSegmentDisplay()
{
    delete ui;
}
