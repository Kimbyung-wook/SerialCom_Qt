#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>
#include <QAction>

#include <cstring>

#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString m_SerialPort;
    QSerialPort::BaudRate m_Baudrate;
    QSerialPort::DataBits m_DataBits;
    QSerialPort::StopBits m_StopBits;
    QSerialPort::Parity m_Parity;

    QPushButton *openButton;
    QPushButton *closeButton;

    QLineEdit *SendLine1;
    QLineEdit *SendLine2;
    QLineEdit *SendLine3;
    QLineEdit *SendLine4;
    QLineEdit *SendLine5;

private slots:
    void scanSerialPort();
    // Open / Close
    void on_OpenPort_clicked();
    void on_ClosePort_clicked();
    void on_ClearData_clicked();
    // Combo Box
    void on_SerialPort_activated(const QString arg);
    void on_Baudrate_activated(const QString arg);
    void on_DataBits_activated(int index);
    void on_StopBits_activated(int index);
    void on_Parity_activated(int index);
    // Tx Section
    void on_Send_1_clicked();
    void on_Send_2_clicked();
    void on_Send_3_clicked();
    void on_Send_4_clicked();
    void on_Send_5_clicked();
    void on_SendFormat_1_clicked();
    void on_SendFormat_2_clicked();
    void on_SendFormat_3_clicked();
    void on_SendFormat_4_clicked();
    void on_SendFormat_5_clicked();

    void action_connect();
    void action_disconnect();
    void action_exit();


private:
    QString ProgramName;
    Ui::MainWindow *ui;
    QSerialPort *port;
    QTimer *scanPortTimer;
    QByteArray receiveDataBuffer;

    // Initialize
    void initialize_ComboBox();
    void initialize_Button();
    void initialize_PortScanner();
    void initialize_Variables();
    void initialize_Actions();

    // Rx Section
    void update_Serial_port_attribute();
    void update_Serialport_from_combobox();
    void update_Baudrate_from_combobox();
    void update_DataBits_from_combobox();
    void update_StopBits_from_combobox();
    void update_Parity_from_combobox();

    void on_Ready_read();
    void send_message(const QString &arg);

    void show_Received_data(const QString arg);
    quint64 sentmsglen;
    void show_Sent_data(std::string msg);

    // Tx Section
    QString SendFormat_1;
    QString SendFormat_2;
    QString SendFormat_3;
    QString SendFormat_4;
    QString SendFormat_5;
    void initializeSendFormat();
    QString change_SendFormat(QString prev_SendFormat);

};
#endif // MAINWINDOW_H
