#pragma once
#include <QMainWindow>
#include "OperateService.h"
#include "FileService.h"

namespace Ui {
class ServerWindow;
}

// 服务端界面
class ServerWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

    void startServer();
    void stopServer();

private:
    Ui::ServerWindow *ui;
    // 业务服务
    OperateService opService;
    std::unique_ptr<grpc::Server> opServer;
    // 文件服务
    FileService fileService;
    std::unique_ptr<grpc::Server> fileServer;
};
