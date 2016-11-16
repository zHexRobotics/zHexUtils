#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();

    void on_findButton_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_deltaBox_valueChanged(int arg1);

    void on_spinBox_editingFinished();


    void on_sldrX_sliderMoved(int position);

    void on_sldrY_sliderMoved(int position);

    void on_sldrZ_sliderMoved(int position);

    void on_pushButton_clicked();

    void on_serial_rcv();

    void set_leg(int i);
    void set_legs();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
};

#endif // MAINWINDOW_H
