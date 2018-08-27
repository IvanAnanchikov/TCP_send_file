#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTcpServer * server;
    QTcpSocket * my_socket;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void mySlot();
    void myReadSlot();
    void on_sendButton_clicked();
    void on_ListenButton_clicked();
    void on_ConnectButton_clicked();
    void myConnected();
};

#endif // MAINWINDOW_H
