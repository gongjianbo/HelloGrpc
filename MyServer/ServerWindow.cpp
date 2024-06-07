#include "ServerWindow.h"
#include "ui_ServerWindow.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

ServerWindow::ServerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    connect(ui->btnStart, &QPushButton::clicked, this, &ServerWindow::startServer);
    connect(ui->btnStop, &QPushButton::clicked, this, &ServerWindow::stopServer);

    connect(&opService, &OperateService::updateLog, ui->editLog, &QTextEdit::append);
    connect(&fileService, &FileService::updateLog, ui->editLog, &QTextEdit::append);
    ui->btnStop->setEnabled(false);

    // 创建文件目录，避免写文件失败
    QDir dir;
    dir.mkpath(QCoreApplication::applicationDirPath() + "/Cache");
    dir.mkpath(QCoreApplication::applicationDirPath() + "/File");
}

ServerWindow::~ServerWindow()
{
    stopServer();
    delete ui;
}

void ServerWindow::startServer()
{
    ui->editLog->append("start server");
    const QString addr = ui->editAddress->text();
    std::thread th_op([=]{
        grpc::EnableDefaultHealthCheckService(true);
        grpc::ServerBuilder builder;
        builder.AddListeningPort((QString("%1:50001").arg(addr)).toStdString(), grpc::InsecureServerCredentials());
        // 消息默认限制 4M
        builder.SetMaxReceiveMessageSize(-1);
        builder.SetMaxSendMessageSize(-1);
        // builder.SetSyncServerOption(grpc::ServerBuilder::MIN_POLLERS, 2);
        builder.RegisterService(&opService);
        opServer = std::unique_ptr<grpc::Server>(builder.BuildAndStart());

        qDebug()<<"operate server start";
        opServer->Wait();
        qDebug()<<"operate server quit";
    });
    th_op.detach();
    std::thread th_file([=]{
        grpc::EnableDefaultHealthCheckService(true);
        grpc::ServerBuilder builder;
        builder.AddListeningPort((QString("%1:50002").arg(addr)).toStdString(), grpc::InsecureServerCredentials());
        // 消息默认限制 4M
        builder.SetMaxReceiveMessageSize(-1);
        builder.SetMaxSendMessageSize(-1);
        // builder.SetSyncServerOption(grpc::ServerBuilder::MIN_POLLERS, 2);
        builder.RegisterService(&fileService);
        fileServer = std::unique_ptr<grpc::Server>(builder.BuildAndStart());

        qDebug()<<"file server start";
        fileServer->Wait();
        qDebug()<<"file server quit";
    });
    th_file.detach();
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
}

void ServerWindow::stopServer()
{
    ui->editLog->append("stop server");
    if (opServer) {
        opServer->Shutdown(std::chrono::system_clock::now() + std::chrono::seconds(1));
        opServer.reset();
    }
    if (fileServer) {
        fileServer->Shutdown(std::chrono::system_clock::now() + std::chrono::seconds(1));
        fileServer.reset();
    }
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
}
