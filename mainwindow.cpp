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
   /*auto*/ my_socket = server->nextPendingConnection();
 //
   connect(my_socket,SIGNAL(disconnected()),
           my_socket,SLOT(deleteLater()));
   connect(my_socket,SIGNAL(readyRead()),
           SLOT(myReadSlot()));
}

void MainWindow::myReadSlot()
{
//=============================================================
    QByteArray data;
    // read ...
   /*auto*/ my_socket = dynamic_cast<QTcpSocket*>(sender());
    //ui->textEdit->append(QString(my_socket->readAll())+'\n');//read для файла
    data = my_socket->readAll();
    QFile file("book2.bin"); // C:/path/myimage.jpg  change path
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();
//=============================================================
//    //тот кто прислал данные, в нашем случае my_socket
//    /*auto*/ my_socket = dynamic_cast<QTcpSocket*>(sender());
//    ui->textEdit->append(QString(my_socket->readAll())+'\n');//read для файла
//=============================================================



//    QDataStream in(this);
//        in.setVersion(10);
//        if (nextBlockSize == 0) {
//            if (bytesAvailable() < sizeof(quint16))
//                return;
//            in >> nextBlockSize;
//        }
//        if (bytesAvailable() < nextBlockSize)
//            return;

//        quint8 requestType;
//        QString targetFile;
//        targetFile = "book2.bin";

//        in >> requestType;
//        if (requestType == 'S') {
//            in >> targetFile;
//            generateRandomTrip(targetFile);
//            QFile target(targetFile);
//            if(target.open(QIODevice::WriteOnly)){
//                char block[1024];

//    //самое основное - пытаюсь считать этот файл из сетевого потока

//                while(!in.atEnd()) {
//                    quint64 tofile = in.readRawData(block,sizeof(block));

//                    target.write(block,tofile);
//=============================================================


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
    server->listen(QHostAddress::Any,1212);//1212 - номер порта
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

void MainWindow::on_send_on_FTP_clicked()
{
//    QFile file("C++20.pdf");
//        QFtp *ftp = new QFtp(this);
//        if (file.open(QIODevice::WriteOnly)){
//        ftp->connectToHost("172.16.80.1");
//        ftp->login("it-academy","Jgfymrb");
//        ftp->cd("new");
//        ftp->get("file.pdf",&file);
}

void MainWindow::on_sendFile_clicked()
{
    QFile file("book.bin");//c:/mypic.jpg
    file.open(QIODevice::ReadOnly);
    QByteArray mydata=file.readAll();
    my_socket->write(mydata);
//=============================================================
//    char block[1024];
//    QFile fileopen("book.bin");
//    if (fileopen.open(QFile::ReadWrite)) {
//        QByteArray arrayBlock;
//        QDataStream vivod(&arrayBlock, QIODevice::WriteOnly);
//        vivod.setVersion(10);
//        vivod << quint16(0) << quint8('S') << "book2.bin";

//        fileopen.seek(0);
//        while(!fileopen.atEnd()) {
//             quint64 in;
//            in = fileopen.read(block, sizeof(block));
//            vivod.writeRawData(block,in);
//            }
//        vivod.device()->seek(0);
//        vivod << quint16(arrayBlock.size() - sizeof(quint16));
//        //записываем данные в сокет
//        my_socket->write(arrayBlock);
//        }
//    ui->textEdit->append("Sending File...");
//=============================================================


//    unsigned int blockSize = 1024;
//    QDataStream stream(my_socket);
//    stream.setVersion(QDataStream::Qt_4_2);
//    QFile file("book.bin");
//    file.open(QIODevice::WriteOnly);
//    if (blockSize == 0) {
//        if (my_socket->bytesAvailable() < (int)sizeof(quint16))
//            return;
//        stream >> blockSize;
//    }
//    if (my_socket->bytesAvailable() < blockSize)
//        return;
//    char a[1024];
//    while(stream.atEnd()!=true){
//        int nBlockSize=stream.device()->read(a,sizeof(a));
//        file.write(a, nBlockSize);
//    }
//    file.close();
//=============================================================



    //        QFile file("result2.png");
    //        if(file.open(QIODevice::WriteOnly))
    //        {
    //            ui->textEdit->append("File result2.png is opened");
    //            QDataStream stream(&file);
    //            stream. setVersion(QDataStream::Qt_4_2);
    //            stream << QImage("result.png");
    //            if(stream.status() != QDataStream::Ok)
    //            {
    //                qDebug() << "Ошибка записи";
    //                ui->textEdit->append("Record error!");
    //            }
    //        }
    //        file.close();
//=============================================================


//    FileData fd;
//    fd.FileSize = 1024;
//    memset( fd.FileName, 0, sizeof(fd.FileName));
//    strcpy( fd.FileName, "book.bin");
//    my_socket->write( (const char*)&fd, sizeof( fd));
//    ui->textEdit->append(QString(fd.FileName));
//    ui->textEdit->append(QString(fd.FileSize));
//    ui->textEdit->append("File \"C++20.pdf\" is successfully sended");
}
