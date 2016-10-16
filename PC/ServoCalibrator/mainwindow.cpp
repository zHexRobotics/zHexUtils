#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete serial;
}


void MainWindow::on_connectButton_clicked()
{
    if (serial->isOpen())
    {
        serial->close();
        ui->connectButton->setText("Connect");
        ui->horizontalSlider->setEnabled(false);
        ui->spinBox->setEnabled(false);
        ui->deltaBox->setEnabled(false);
    }
    else
    {
        serial->setPortName(ui->comboBox->currentText());
        serial->setBaudRate(QSerialPort::Baud57600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        if (serial->open(QIODevice::ReadWrite))
        {
            ui->connectButton->setText("Disconnect");
            ui->horizontalSlider->setEnabled(true);
            ui->spinBox->setEnabled(true);
            ui->deltaBox->setEnabled(true);
        }
        else
        {
            QMessageBox::critical(this, ui->comboBox->currentText(), serial->errorString());
        }
    }
}

void MainWindow::on_findButton_clicked()
{
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        QStringList list;
        list << info.portName();
        ui->comboBox->addItem(info.portName());
    }
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->spinBox->setValue(position);
    int value = position;
    serial->write((std::to_string(value)+" \n").c_str(), 6);
}

void MainWindow::on_deltaBox_valueChanged(int arg1)
{
    ui->spinBox->setSingleStep(ui->deltaBox->value());
}


void MainWindow::on_spinBox_editingFinished()
{
    int value = ui->spinBox->value();
    ui->horizontalSlider->setValue(value);
    serial->write((std::to_string(value)+" \n").c_str(), 6);
}
