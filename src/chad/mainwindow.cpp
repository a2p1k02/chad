#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    port = 2222;

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, port);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readingData()));


    ui->label_2->setText("Адресат: \t\t\t\t\t\t IP: 127.0.0.1 Port: " + QString::number(port));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readingData()
{
    QHostAddress sender;
    quint16 senderPort;

    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        ui->textEdit_2->append("<font color=blue>" + QString(datagram) + "</font>");
    }

}

void MainWindow::sendMessage()
{
    udpSocket->writeDatagram(ui->lineEdit->text().toUtf8(), QHostAddress::LocalHost, 1111);
    ui->textEdit_2->append("Вы: <font color=green>" + ui->lineEdit->text() + "<font>");
    ui->lineEdit->clear();
}

void MainWindow::on_pushButton_clicked()
{
    sendMessage();
}

void MainWindow::on_lineEdit_editingFinished()
{
    sendMessage();
}

