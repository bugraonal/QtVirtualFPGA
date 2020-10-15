#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , numButtons(0)
    , numSwitches(0)
    , numLeds(0)
    , numDigits(0)
{
    ui->setupUi(this);
    buttonsLayout = new QBoxLayout(QBoxLayout::RightToLeft);
    switchesLayout = new QBoxLayout(QBoxLayout::RightToLeft);
    ledsLayout = new QBoxLayout(QBoxLayout::RightToLeft);
    digitsLayout = new QBoxLayout(QBoxLayout::RightToLeft);

    ui->buttonGroup->setLayout(buttonsLayout);
    ui->switchGroup->setLayout(switchesLayout);
    ui->ledGroup->setLayout(ledsLayout);
    ui->digitGroup->setLayout(digitsLayout);


    configureGroups();

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configureGroups() {
    // This function will add or remove I/O elements (buttons, leds etc.)
    // based on the spinboxes
    int newButtons = ui->ButtonSpinBox->text().toInt();
    int newSwitches = ui->SwitchSpinBox->text().toInt();
    int newLeds = ui->ledSpinBox->text().toInt();
    int newDigits = ui->DigitSpinBox->text().toInt();

    if (newButtons > numButtons) {
        for (int i = numButtons; i < newButtons; ++i) {
            IndexedButton* b = new IndexedButton(i);
            buttonsLayout->addWidget(b);
            connect(b, &IndexedButton::indexClicked, this, &MainWindow::dataChanged<1>);
        }
    }
    else {
        for (int i = numButtons - 1; i >= newButtons; --i) {
            QWidget *w = buttonsLayout->takeAt(i)->widget();
            buttonsLayout->removeItem(buttonsLayout->takeAt(i));
            delete w;
        }
    }

    if (newSwitches > numSwitches) {
        for (int i = numSwitches; i < newSwitches; ++i) {
            IndexedSwitch *s = new IndexedSwitch(i);
            switchesLayout->addWidget(s);
            connect(s, &IndexedSwitch::indexClicked, this, &MainWindow::dataChanged<0>);
        }
        numSwitches = newSwitches;

    }
    else {
        for (int i = 0; i < numSwitches - newSwitches; ++i) {
            QWidget *w = switchesLayout->takeAt(numSwitches - i - 1)->widget();
            switchesLayout->removeItem(switchesLayout->takeAt(numSwitches - i - 1));
            delete w;
        }
    }

    if (newLeds > numLeds) {
        for (int i = 0; i < newLeds - numLeds; ++i) {
            auto l = new QLabel;
            l->setFrameStyle(QFrame::Panel);
            ledsLayout->addWidget(l);

        }
    }
    else {
        for (int i = 0; i < numLeds - newLeds; ++i) {
            QWidget *w = ledsLayout->takeAt(numLeds - i - 1)->widget();
            ledsLayout->removeItem(ledsLayout->takeAt(numLeds - i - 1));
            delete w;
        }
    }

    if (newDigits > numDigits) {
        for (int i = 0; i < newDigits - numDigits; ++i) {
            auto d = new QLCDNumber;
            d->setFrameStyle(QFrame::NoFrame);
            d->setSegmentStyle(QLCDNumber::Outline);
            d->setHexMode();
            d->setDigitCount(1);
            digitsLayout->addWidget(d);

        }
    }
    else {
        for (int i = 0; i < numDigits - newDigits; ++i) {
            QWidget *w = digitsLayout->takeAt(numDigits - i - 1)->widget();
            digitsLayout->removeItem(digitsLayout->takeAt(numDigits - i - 1));
            delete w;
        }
    }
    numButtons = newButtons;
    numSwitches = newSwitches;
    numLeds = newLeds;
    numDigits = newDigits;
}

template<bool isBtn>
void MainWindow::dataChanged(int k){
    // This slot is triggered when a button is pressed
    // or a switch is toggled
    // The button an switch values are calculated and
    // a sendDataToSend signal is sent to the model thread
    QTextStream stream(&dataToSend);
    int buttonData;
    int switchData;

    stream >> buttonData >> switchData;

    if constexpr (isBtn) {
        //buttonData += (1 << k);
        // negate bit
        int bit = buttonData & (1 << k);
        if (bit)
            buttonData &= ~(1 << k);
        else
            buttonData |= (1 << k);
    }
    else {
        // negate bit
        int bit = switchData & (1 << k);
        if (bit)
            switchData &= ~(1 << k);
        else
            switchData |= (1 << k);
    }
    dataToSend.clear();
    stream << buttonData << " " << switchData;

    //emit the new data by copy (NOT BY REFERENCE)
    emit sendDataToSend(dataToSend);

}


void MainWindow::on_applyConfigButton_clicked() { configureGroups(); }

void MainWindow::openFile()
{
    // TODO: The user will need to select the Verilog files and the
    // top wrapper. Currently they can select only 1 file.
    // Consider selecting multiple files or auto generating top wrapper
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    if (dialog.exec()) {
        inputFileName = dialog.selectedFiles()[0];
    }
}

void MainWindow::on_StartButton_clicked()
{
    // This slot will copy the files in the project folder
    // to a temporary folder.
    // It will start the CMake and then Make proceses as
    // QProcesses. Their error messages are forwareded to the
    // console
    if (inputFileName.isEmpty()) {
        //TODO: add "Select file" error dialog
        return;
    }
    ui->configFrame->setDisabled(true);

    QDir projectFolder("/home/bugra/Ozu/Projects/VirtualFPGA/resources/projectFiles");

    for (auto f : projectFolder.entryList()) {
        QFile file(projectFolder.filePath(f));
        file.copy(tempDir.filePath(f));
    }
    QFile in(inputFileName);
    in.copy(tempDir.filePath(inputFileName.section("/", -1, -1)));

    QString command = "cmake";
    QStringList args;
    args << ".";
//    args << tempDir.filePath("CMakeLists.txt");
    QProcess cmake;
    cmake.setProcessChannelMode(QProcess::ForwardedErrorChannel);
    cmake.setWorkingDirectory(tempDir.path());
    cmake.start(command, args);
    while(cmake.state() == QProcess::Running);
    cmake.waitForFinished();
    if (cmake.exitStatus() != QProcess::NormalExit || cmake.exitCode() != 0) {
        std::cerr << "CMake error" << std::endl;
        return;
    }
    //cmake.close();
    command = "make";
    args.clear();
    QProcess make;


    make.setProcessChannelMode(QProcess::ForwardedErrorChannel);
    make.setWorkingDirectory(tempDir.path());
    make.start(command, args);
    while(make.state() == QProcess::Running);
    make.waitForFinished();
    if (make.exitStatus() != QProcess::NormalExit || make.exitCode() != 0) {
        std::cerr << "Make error" << std::endl;
        return;
    }
    //make.terminate();
    runModel();
    cmake.close();
    make.close();

}

void MainWindow::runModel() {
    // This function will start the model thread
    connect(&controller, &ModelController::sendDataReceived, this, &MainWindow::parseDataReceived);
    connect(this, &MainWindow::sendDataToSend, &controller, &ModelController::handleDataToSend);
    connect(ui->StopButton, &QPushButton::clicked, &controller, &ModelController::handleStopModel);
    emit controller.operate(tempDir.path());

}

void MainWindow::parseDataReceived(QString data) {
    // Data that came from the model thread will be parsed and be displayed on
    // the digits and the leds
    QTextStream stream(&data);
    int led, digit, anode;

    stream >> led >> digit >> anode;
    for (int ii = 0; ii < numLeds; ++ii) {
        if (led & 0x01)
            ledsLayout->itemAt(ii)->widget()->setStyleSheet("background-color: rgb(0, 255, 0)");
        else
            ledsLayout->itemAt(ii)->widget()->setStyleSheet("");
        led = led >> 1;
    }
    int num = decodeDigit(digit);
    for (int ii = 0; ii < numDigits; ++ii){
        if (!(anode & 0x01)) {
            ((QLCDNumber*)(digitsLayout->itemAt(ii)->widget()))->setSegmentStyle(QLCDNumber::Filled);
            ((QLCDNumber*)(digitsLayout->itemAt(ii)->widget()))->display(num);
        }
        else {
            ((QLCDNumber*)(digitsLayout->itemAt(ii)->widget()))->setSegmentStyle(QLCDNumber::Outline);
            ((QLCDNumber*)(digitsLayout->itemAt(ii)->widget()))->display(8);
        }
        anode = anode >> 1;
    }


}

int MainWindow::decodeDigit(quint8 byte) {
    // 7-seg digit decoder
    int num;
    switch (byte) {
    case 0xC0:
        num = 0;
        break;
    case 0xF9:
        num = 1;
        break;
    case 0xA4:
        num = 2;
        break;
    case 0xB0:
        num = 3;
        break;
     case 0x99:
        num = 4;
        break;
     case 0x92:
        num = 5;
        break;
     case 0x82:
        num = 6;
        break;
     case 0xF8:
        num = 7;
        break;
     case 0x80:
        num = 8;
        break;
     case 0x90:
        num = 9;
        break;
     case 0x88:
        num = 10;
        break;
     case 0x83:
        num = 11;
        break;
     case 0xC6:
        num = 12;
        break;
     case 0xA1:
        num = 13;
        break;
     case 0x86:
        num = 14;
        break;
     case 0x8D:
        num = 15;
        break;
     default:
        num = -1;
        break;
    }
    return num;
}
