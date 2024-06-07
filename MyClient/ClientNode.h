#pragma once
#include <QObject>
#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <grpcpp/grpcpp.h>
#include "MyProto.grpc.pb.h"

// 服务接口调用
class ClientNode : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;

    // 连接
    bool doConnect(const QString &opAddress, const QString &fileAddress);
    // 断开
    bool doDisconnect();
    // 连接状态
    bool isConnected() const;
    // 检测服务器是否可连接
    bool addressValid(const QString &address);

    // 新增文件
    bool insertFile(MyPackage::FileInfo &info, const QString &path);
    // 删除文件
    bool deleteFile(int64_t id);
    // 修改文件
    bool updateFile(MyPackage::FileInfo &info, const QString &path);
    // 查询文件
    bool selectFile(MyPackage::FileInfo &info, int64_t id);
    // 搜索文件
    bool searchFile(std::vector<MyPackage::FileInfo> &infos, const QString &condition);

    // 上传文件，返回缓存id
    int64_t uploadFile(const QString &path);
    // 下载文件
    bool downloadFile(int64_t id, const QString &path);

signals:
    void updateLog(const QString &log);

private:
    // channel 提供了 tcp 层的连接，而 stub 则提供了应用层的连接
    // 所以单个客户端只需要一个 channel，而每个封装的类可以有自己的 stub
    // 业务
    std::shared_ptr<grpc::Channel> opChannel;
    std::unique_ptr<MyPackage::MyOperateService::Stub> opStub;
    // 文件管理
    std::shared_ptr<grpc::Channel> fileChannel;
    std::unique_ptr<MyPackage::MyFileService::Stub> fileStub;
};
