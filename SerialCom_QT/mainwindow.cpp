#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QSysInfo>
#include <QTimer>
#include <cmath>
//#define SHOW_SERIALPORT_ATTRIBUTE
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      port(new QSerialPort(this)),
      scanPortTimer(new QTimer(this))
{
    setFixedSize(700,590);
    ui->setupUi(this);
    scanSerialPort();
    initialize_PortScanner();
    initialize_ComboBox();
    initialize_Button();

}
MainWindow::~MainWindow()
{
    port->close();
    delete scanPortTimer;
    delete port;
    delete ui;
}
void MainWindow::scanSerialPort()
{
    //show_Received_data("Scan list\n");
    ui->SerialPort->clear();
    foreach(const QSerialPortInfo &ports,
            QSerialPortInfo::availablePorts())
    {
        ui->SerialPort->addItem(ports.portName());
    }
    if(port->isOpen() == false){
        if(ui->SerialPort->count()>0){
            ui->OpenPort->setEnabled(true);
        }
        else{
            ui->OpenPort->setDisabled(true);
        }
    }
    else{ // if port opened, but cannot send
        if(port->isRequestToSend() == false){
            on_ClosePort_clicked();
            QMessageBox::warning(this, ProgramName, "Please check serial port!!");
        }
    }

}
// Open / Close
void MainWindow::on_OpenPort_clicked()
{
    update_Serial_port_attribute();
    port->setPortName(m_SerialPort);
    port->setBaudRate(m_Baudrate);
    port->setDataBits(m_DataBits);
    port->setStopBits(m_StopBits);
    port->setParity(m_Parity);
    if(port->open(QSerialPort::OpenModeFlag::ReadWrite)) {
        connect(port, & QSerialPort::readyRead, this, &MainWindow::on_Ready_read);

        ui->ClosePort->setEnabled(true);

        ui->OpenPort->setDisabled(true);
        ui->SerialPort->setDisabled(true);
        ui->Baudrate->setDisabled(true);
        ui->DataBits->setDisabled(true);
        ui->StopBits->setDisabled(true);
        ui->Parity->setDisabled(true);

        // Tx Section
        ui->AutoSend_1->setEnabled(true);
        ui->AutoSend_2->setEnabled(true);
        ui->AutoSend_3->setEnabled(true);
        ui->AutoSend_4->setEnabled(true);
        ui->AutoSend_5->setEnabled(true);
        ui->SendFormat_1->setEnabled(true);
        ui->SendFormat_2->setEnabled(true);
        ui->SendFormat_3->setEnabled(true);
        ui->SendFormat_4->setEnabled(true);
        ui->SendFormat_5->setEnabled(true);
        ui->Send_1->setEnabled(true);
        ui->Send_2->setEnabled(true);
        ui->Send_3->setEnabled(true);
        ui->Send_4->setEnabled(true);
        ui->Send_5->setEnabled(true);
        ui->SendRepeatly->setEnabled(true);
    }
    else {
        QMessageBox::warning(this, ProgramName, "Can't open serial port!!");
    }
}
void MainWindow::on_ClosePort_clicked()
{
    port->close();

    ui->ClosePort->setDisabled(true);

    ui->OpenPort->setEnabled(true);
    ui->SerialPort->setEnabled(true);
    ui->Baudrate->setEnabled(true);
    ui->DataBits->setEnabled(true);
    ui->StopBits->setEnabled(true);
    ui->Parity->setEnabled(true);

    // Tx Section
    ui->AutoSend_1->setDisabled(true);
    ui->AutoSend_2->setDisabled(true);
    ui->AutoSend_3->setDisabled(true);
    ui->AutoSend_4->setDisabled(true);
    ui->AutoSend_5->setDisabled(true);
    ui->SendFormat_1->setDisabled(true);
    ui->SendFormat_2->setDisabled(true);
    ui->SendFormat_3->setDisabled(true);
    ui->SendFormat_4->setDisabled(true);
    ui->SendFormat_5->setDisabled(true);
    ui->Send_1->setDisabled(true);
    ui->Send_2->setDisabled(true);
    ui->Send_3->setDisabled(true);
    ui->Send_4->setDisabled(true);
    ui->Send_5->setDisabled(true);
    ui->SendRepeatly->setDisabled(true);
}
void MainWindow::on_ClearData_clicked()
{
    QString temp;
    receiveDataBuffer.clear();
    ui->textBrowser->clear();
    temp.sprintf("Received Data : Receive %d characters",receiveDataBuffer.size());
    ui->StatusOfReceivedData->setText(temp);
}
// Combo Box
void MainWindow::on_SerialPort_activated(const QString arg)
{
    update_Serialport_from_combobox();
}
void MainWindow::on_Baudrate_activated(const QString arg)
{
    update_Baudrate_from_combobox();
}
void MainWindow::on_DataBits_activated(int index)
{
    update_DataBits_from_combobox();
}
void MainWindow::on_StopBits_activated(int index)
{
    update_StopBits_from_combobox();
}
void MainWindow::on_Parity_activated(int index)
{
    update_Parity_from_combobox();
}

void MainWindow::initialize_ComboBox()
{
    QString temp;
    temp.sprintf("Size of Items : %d\n",ui->SerialPort->count());
    receiveDataBuffer.append(temp);
    if(ui->SerialPort->count()>0)
    {
        ui->SerialPort->setCurrentIndex(0);
        update_Serialport_from_combobox();
    }
    ui->Baudrate->setCurrentIndex(8);
    ui->DataBits->setCurrentIndex(3);
    ui->StopBits->setCurrentIndex(0);
    ui->Parity->setCurrentIndex(0);

    update_Baudrate_from_combobox();
    update_DataBits_from_combobox();
    update_StopBits_from_combobox();
    update_Parity_from_combobox();
}
void MainWindow::initialize_Button()
{
    ui->ClosePort->setDisabled(true);

    // Tx Section
    ui->AutoSend_1->setChecked(true);
    ui->AutoSend_1->setDisabled(true);
    ui->AutoSend_2->setDisabled(true);
    ui->AutoSend_3->setDisabled(true);
    ui->AutoSend_4->setDisabled(true);
    ui->AutoSend_5->setDisabled(true);
    ui->SendFormat_1->setDisabled(true);
    ui->SendFormat_2->setDisabled(true);
    ui->SendFormat_3->setDisabled(true);
    ui->SendFormat_4->setDisabled(true);
    ui->SendFormat_5->setDisabled(true);
    ui->Send_1->setDisabled(true);
    ui->Send_2->setDisabled(true);
    ui->Send_3->setDisabled(true);
    ui->Send_4->setDisabled(true);
    ui->Send_5->setDisabled(true);
    ui->SendRepeatly->setDisabled(true);
}
void MainWindow::initialize_PortScanner()
{
    scanPortTimer->setInterval(1000);
    scanPortTimer->start();
    connect(scanPortTimer, SIGNAL(timeout()),this, SLOT(scanSerialPort()));
}
void MainWindow::initialize_Variables()
{
    ProgramName = "QSerialCom";
    sentmsglen = 0;
}
//void MainWindow::initialize_Actions()
//{
//    QAction* qAction_exit = new QAction(tr("actionExit"), this);
//    connect(qAction_exit, SIGNAL(triggered()), this, SLOT(action_exit));


//}

void MainWindow::update_Serial_port_attribute()
{
    update_Serialport_from_combobox();
    update_Baudrate_from_combobox();
    update_DataBits_from_combobox();
    update_Serialport_from_combobox();
    update_Parity_from_combobox();
}
void MainWindow::update_Serialport_from_combobox()
{
    QString temp = ui->SerialPort->currentText();
#ifdef Q_OS_LINUX
    m_SerialPort = "/dev/" + temp;  // linux
#elif Q_OS_WIN32
    m_SerialPort = temp;  // linux
#endif
#ifdef SHOW_SERIALPORT_ATTRIBUTE
    show_Received_data(m_SerialPort + "\n");
#endif

}
void MainWindow::update_Baudrate_from_combobox()
{
    QString temp = ui->Baudrate->currentText();
    m_Baudrate = QSerialPort::BaudRate(temp.toLong());
#ifdef SHOW_SERIALPORT_ATTRIBUTE
    temp.sprintf("m_Baudrate : %d",m_Baudrate);
    show_Received_data(temp + "\n");
#endif

}
void MainWindow::update_DataBits_from_combobox()
{
    int index = ui->DataBits->currentIndex();
    switch(index) {
    case 0: m_DataBits = QSerialPort::Data5; break;
    case 1: m_DataBits = QSerialPort::Data6; break;
    case 2: m_DataBits = QSerialPort::Data7; break;
    case 3: m_DataBits = QSerialPort::Data8; break;
    }
#ifdef SHOW_SERIALPORT_ATTRIBUTE
    QString temp;
    temp.sprintf("DataBits : %d",m_DataBits);
    show_Received_data(temp + "\n");
#endif

}
void MainWindow::update_StopBits_from_combobox()
{
    int index = ui->StopBits->currentIndex();
    switch (index) {
    case 0: m_StopBits = QSerialPort::StopBits::OneStop; break;
    case 1: m_StopBits = QSerialPort::StopBits::TwoStop; break;
    }

#ifdef SHOW_SERIALPORT_ATTRIBUTE
    QString temp;
    temp.sprintf("m_StopBits : %d",m_StopBits);
    show_Received_data(temp + "\n");
#endif
}
void MainWindow::update_Parity_from_combobox()
{
    int index = ui->Parity->currentIndex();
    switch (index) {
    case 0: m_Parity = QSerialPort::Parity::NoParity; break;
    case 1: m_Parity = QSerialPort::Parity::OddParity; break;
    case 2: m_Parity = QSerialPort::Parity::EvenParity; break;
    }
#ifdef SHOW_SERIALPORT_ATTRIBUTE
    QString temp;
    temp.sprintf("m_Parity : %d",m_Parity);
    show_Received_data(temp + "\n");
#endif
}

void MainWindow::on_Ready_read()
{
    if(port->isOpen()) {
        QByteArray msg = port->readAll();
        QString RxFormat = ui->RxFormat->currentText();
        if(RxFormat.compare("HEX") == 0)
        {
            msg = msg.toHex();
        }
        show_Received_data(msg);
    }
    else {
        QMessageBox::warning(this, ProgramName, "Please open serial port!!");
    }
}
void MainWindow::send_message(const QString &arg)
{
    std::string temp = arg.toStdString();
    if(port->isOpen()) {
        port->write(temp.c_str(),temp.length());
        show_Sent_data(temp);
    }
    else {
        QMessageBox::warning(this, ProgramName, "Please open serial port!!");
    }
}
void MainWindow::show_Received_data(const QString arg)
{
    QString temp;
    receiveDataBuffer.append(arg);
    ui->textBrowser->setText(receiveDataBuffer);
    temp.sprintf("Received Data : Receive %d characters",receiveDataBuffer.size());
    ui->StatusOfReceivedData->setText(temp);
}
void MainWindow::show_Sent_data(std::string msg)
{
    QString temp;
    sentmsglen = sentmsglen + quint64(msg.length());
    temp.sprintf("Send Data : Send %d characters",sentmsglen);
    ui->StatusOfSentData->setText(temp);
}

/********************************************
**  TX Section
**
********************************************/
void MainWindow::on_Send_1_clicked()
{
    QByteArray msg = ui->lineEdit_1->text().toUtf8();
    if(SendFormat_1.compare("HEX") == 0)
    {
        msg = QByteArray::fromHex(msg);
    }
    send_message(msg);
}
void MainWindow::on_Send_2_clicked()
{
    QByteArray msg = ui->lineEdit_2->text().toUtf8();
    if(SendFormat_2.compare("HEX") == 0)
    {
        msg = QByteArray::fromHex(msg);
    }
    send_message(msg);
}
void MainWindow::on_Send_3_clicked()
{
    QByteArray msg = ui->lineEdit_3->text().toUtf8();
    if(SendFormat_3.compare("HEX") == 0)
    {
        msg = QByteArray::fromHex(msg);
    }
    send_message(msg);
}
void MainWindow::on_Send_4_clicked()
{
    QByteArray msg = ui->lineEdit_4->text().toUtf8();
    if(SendFormat_4.compare("HEX") == 0)
    {
        msg = QByteArray::fromHex(msg);
    }
    send_message(msg);
}
void MainWindow::on_Send_5_clicked()
{
    QByteArray msg = ui->lineEdit_5->text().toUtf8();
    if(SendFormat_5.compare("HEX") == 0)
    {
        msg = QByteArray::fromHex(msg);
    }
    send_message(msg);
}

void MainWindow::on_SendFormat_1_clicked()
{
    SendFormat_1 = change_SendFormat(ui->SendFormat_1->text());
    ui->SendFormat_1->setText(SendFormat_1);
}
void MainWindow::on_SendFormat_2_clicked()
{
    SendFormat_2 = change_SendFormat(ui->SendFormat_2->text());
    ui->SendFormat_1->setText(SendFormat_1);
}
void MainWindow::on_SendFormat_3_clicked()
{
    SendFormat_3 = change_SendFormat(ui->SendFormat_3->text());
    ui->SendFormat_1->setText(SendFormat_1);
}
void MainWindow::on_SendFormat_4_clicked()
{
    SendFormat_4 = change_SendFormat(ui->SendFormat_4->text());
    ui->SendFormat_1->setText(SendFormat_1);
}
void MainWindow::on_SendFormat_5_clicked()
{
    SendFormat_5 = change_SendFormat(ui->SendFormat_5->text());
    ui->SendFormat_1->setText(SendFormat_1);
}

void MainWindow::initializeSendFormat()
{
    SendFormat_1 = "ASCII"; ui->SendFormat_1->setText(SendFormat_1);
    SendFormat_2 = "ASCII"; ui->SendFormat_2->setText(SendFormat_2);
    SendFormat_3 = "ASCII"; ui->SendFormat_3->setText(SendFormat_3);
    SendFormat_4 = "ASCII"; ui->SendFormat_4->setText(SendFormat_4);
    SendFormat_5 = "ASCII"; ui->SendFormat_5->setText(SendFormat_5);
}
QString MainWindow::change_SendFormat(QString prev_SendFormat)
{
    QString now_SendFormat;
    if(prev_SendFormat.compare("ASCII") == 0)
    {
        now_SendFormat = "HEX";
    }
    if(prev_SendFormat.compare("HEX") == 0)
    {
        now_SendFormat = "ASCII";
    }
    return now_SendFormat;
}

//

void MainWindow::action_connect()
{

}
void MainWindow::action_disconnect()
{

}
void MainWindow::action_exit()
{
    QMessageBox::information(this, ProgramName,"exit");
}
