#include "ClientWindow.h"
#include "ui_ClientWindow.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileDialog>
#include <QDateTime>
#include <QDebug>

ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    connect(ui->btnConnect, &QPushButton::clicked, this, &ClientWindow::doConnect);
    connect(ui->btnDisconnect, &QPushButton::clicked, this, &ClientWindow::doDisconnect);
    connect(ui->btnInsert, &QPushButton::clicked, this, &ClientWindow::insertFile);
    connect(ui->btnDelete, &QPushButton::clicked, this, &ClientWindow::deleteFile);
    connect(ui->btnDownload, &QPushButton::clicked, this, &ClientWindow::downloadFile);
    connect(ui->btnSearch, &QPushButton::clicked, this, &ClientWindow::searchFile);

    connect(&node, &ClientNode::updateLog, ui->editLog, &QTextEdit::append);
    ui->btnDisconnect->setEnabled(false);

    // 创建文件目录，避免写文件失败
    QDir dir;
    dir.mkpath(QCoreApplication::applicationDirPath() + "/Download");
}

ClientWindow::~ClientWindow()
{
    doDisconnect();
    delete ui;
}

void ClientWindow::doConnect()
{
    const QString addr = ui->editAddress->text();
    bool ok = node.doConnect(QString("%1:50001").arg(addr), QString("%1:50002").arg(addr));
    ui->btnConnect->setEnabled(!ok);
    ui->btnDisconnect->setEnabled(ok);
    ui->editLog->append(QString("connect %1").arg(ok ? "success" : "fail"));
}

void ClientWindow::doDisconnect()
{
    bool ok = node.doDisconnect();
    ui->btnConnect->setEnabled(ok);
    ui->btnDisconnect->setEnabled(!ok);
    ui->editLog->append(QString("disconnect"));
}

void ClientWindow::insertFile()
{
    const QString path = QFileDialog::getOpenFileName(this);
    if (path.isEmpty())
        return;
    MyPackage::FileInfo info;
    node.insertFile(info, path);
    ui->boxId->addItem(QString::number(info.fileid()));
}

void ClientWindow::deleteFile()
{
    QString id_str = ui->boxId->currentText();
    if (id_str.isEmpty())
        return;
    int64_t id = id_str.toLongLong();
    node.deleteFile(id);
    ui->boxId->removeItem(ui->boxId->currentIndex());
}

void ClientWindow::downloadFile()
{
    QString id_str = ui->boxId->currentText();
    if (id_str.isEmpty())
        return;
    int64_t id = id_str.toLongLong();
    MyPackage::FileInfo info;
    if (!node.selectFile(info, id))
        return;
    QString path = QString("%1/Download/%2").arg(QCoreApplication::applicationDirPath()).arg(QString::fromStdString(info.filename()));
    node.downloadFile(id, path);
}

void ClientWindow::searchFile()
{
    const QString condition = ui->editSearch->text();
    std::vector<MyPackage::FileInfo> infos;
    node.searchFile(infos, condition);
    ui->boxId->clear();
    QStringList ids;
    for (const auto &info : infos)
    {
        ids.push_back(QString::number(info.fileid()));
    }
    ui->boxId->addItems(ids);
}
