#pragma once
#include <QObject>
#include <memory>
#include <thread>
#include <map>
#include <mutex>
#include <atomic>
#include <map>
#include <grpcpp/grpcpp.h>
#include "MyProto.grpc.pb.h"

// 业务服务
class OperateService : public QObject, public MyPackage::MyOperateService::Service
{
    Q_OBJECT
public:
    using QObject::QObject;

    // 新增文件
    grpc::Status insertFile(grpc::ServerContext *context,
                            const MyPackage::FileOperateRequest *request,
                            MyPackage::FileOperateResponse *response) override;
    // 删除文件
    grpc::Status deleteFile(grpc::ServerContext *context,
                            const MyPackage::FileOperateRequest *request,
                            MyPackage::FileOperateResponse *response) override;
    // 修改文件
    grpc::Status updateFile(grpc::ServerContext *context,
                            const MyPackage::FileOperateRequest *request,
                            MyPackage::FileOperateResponse *response) override;
    // 查询文件
    grpc::Status selectFile(grpc::ServerContext *context,
                            const MyPackage::FileOperateRequest *request,
                            MyPackage::FileOperateResponse *response) override;
    // 搜索文件
    grpc::Status searchFile(grpc::ServerContext *context,
                            const MyPackage::FileSearchRequest *request,
                            MyPackage::FileSearchResponse *response) override;

signals:
    void updateLog(const QString &log);

private:
    std::mutex infoMutex;
    std::map<int64_t, MyPackage::FileInfo> infoMap;
};
