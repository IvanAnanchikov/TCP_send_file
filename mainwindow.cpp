#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit,SIGNAL(returnPressed()),
            SLOT(on_sendButton_clicked()));
//    server = new QTcpServer(this);
//    server->listen(QHostAddress::Any,1212);
//    connect(server,SIGNAL(newConnection()),SLOT(mySlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mySlot()
{//создание сокета этого соединения метод nextPendingConnection
   /*auto*/ my_socket = server->nextPendingConnection();//
   connect(my_socket,SIGNAL(disconnected()),
           my_socket,SLOT(deleteLater()));
   connect(my_socket,SIGNAL(readyRead()),
           SLOT(myReadSlot()));
}

void MainWindow::myReadSlot()
{
    //тот кто прислал данные, в нашем случае my_socket
    /*auto*/ my_socket = dynamic_cast<QTcpSocket*>(sender());
    ui->textEdit->append(QString(my_socket->readAll())+'\n');//read для файла

}

void MainWindow::on_sendButton_clicked()
{
   my_socket->write(ui->lineEdit->text().toLocal8Bit());
   ui->lineEdit->clear();
}

void MainWindow::on_ListenButton_clicked()
{
    ui->textEdit->setText("server");
    server = new QTcpServer (this);
    server->listen(QHostAddress::Any,1212);
    connect(server,SIGNAL(newConnection()),SLOT(mySlot()));
    ui->textEdit->append(
                //QString::number(server->serverAddress().toIPv4Address())
                (server->serverAddress().toString())
                //QString::number(server->serverPort())
                );


}

void MainWindow::on_ConnectButton_clicked()
{
    my_socket = new QTcpSocket(this);
    my_socket->connectToHost("localhost",1212);
    //my_socket->connectToHost("172.16.80.1",1212);
    connect(my_socket,SIGNAL(connected()),
            SLOT(myConnected()));
    connect(my_socket,SIGNAL(readyRead()),
            SLOT(myReadSlot()));
}

void MainWindow::myConnected()
{
  ui->textEdit->setText("Connected");
}
