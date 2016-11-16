#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::on_serial_rcv);
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
        ui->sldrX->setEnabled(false);
        ui->sldrY->setEnabled(false);
        ui->sldrZ->setEnabled(false);
        ui->pushButton->setEnabled(false);
        ui->chbx0->setEnabled(false);
        ui->chbx1->setEnabled(false);
        ui->chbx2->setEnabled(false);
        ui->chbx3->setEnabled(false);
        ui->chbx4->setEnabled(false);
        ui->chbx5->setEnabled(false);
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
            ui->sldrX->setEnabled(true);
            ui->sldrY->setEnabled(true);
            ui->sldrZ->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->chbx0->setEnabled(true);
            ui->chbx1->setEnabled(true);
            ui->chbx2->setEnabled(true);
            ui->chbx3->setEnabled(true);
            ui->chbx4->setEnabled(true);
            ui->chbx5->setEnabled(true);
        }
        else
        {
            QMessageBox::critical(this, ui->comboBox->currentText(), serial->errorString());
        }
    }
}

void MainWindow::on_findButton_clicked()
{
    ui->comboBox->clear();
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
    ui->lblCmd->setText((std::to_string(value)+" \n").c_str());
}

void MainWindow::on_deltaBox_valueChanged(int arg1)
{
    ui->spinBox->setSingleStep(ui->deltaBox->value());
}


void MainWindow::on_spinBox_editingFinished()
{
    int value = ui->spinBox->value();
    ui->horizontalSlider->setValue(value);
    serial->write((std::to_string(value)+" \n").c_str(), (std::to_string(value)+" \n").length());
    ui->lblCmd->setText((std::to_string(value)+" \n").c_str());
}


void MainWindow::on_sldrX_sliderMoved(int position)
{
    set_legs();
}

void MainWindow::on_sldrY_sliderMoved(int position)
{
    set_legs();
}

void MainWindow::on_sldrZ_sliderMoved(int position)
{

    set_legs();
}

void MainWindow::on_pushButton_clicked()
{
    ui->sldrX->setValue(0);
    ui->sldrY->setValue(125);
    ui->sldrZ->setValue(115);
    set_legs();
}

void MainWindow::on_serial_rcv()
{
    QString serialBuffer = QString::fromStdString(serial->readAll().toStdString());
    ui->lblUART->setText(serialBuffer);
}

void MainWindow::set_leg(int i)
{
    std::string cmd = std::to_string(i) + " " + std::to_string(ui->sldrX->value()) + " " +
            std::to_string(ui->sldrY->value()) + " " +
            std::to_string(ui->sldrZ->value()) + "\n";
    ui->lblX->setText(("X: " + std::to_string(ui->sldrX->value())).c_str());
    ui->lblY->setText(("Y: " + std::to_string(ui->sldrY->value())).c_str());
    ui->lblZ->setText(("Z: " + std::to_string(ui->sldrZ->value())).c_str());
    serial->write(cmd.c_str(), cmd.length());
    ui->lblCmd->setText(cmd.c_str());
}

void MainWindow::set_legs()
{
    if (ui->chbx0->isChecked())
    {
        set_leg(0);
    }
    if (ui->chbx1->isChecked())
    {
        set_leg(1);
    }
    if (ui->chbx2->isChecked())
    {
        set_leg(2);
    }
    if (ui->chbx3->isChecked())
    {
        set_leg(3);
    }
    if (ui->chbx4->isChecked())
    {
        set_leg(4);
    }
    if (ui->chbx5->isChecked())
    {
        set_leg(5);
    }
}
