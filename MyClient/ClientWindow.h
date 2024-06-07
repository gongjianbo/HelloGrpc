#pragma once
#include <QMainWindow>
#include "ClientNode.h"

namespace Ui {
class ClientWindow;
}

// 客户端界面
class ClientWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

    void doConnect();
    void doDisconnect();
    void insertFile();
    void deleteFile();
    void downloadFile();
    void searchFile();

private:
    Ui::ClientWindow *ui;
    ClientNode node;
};
