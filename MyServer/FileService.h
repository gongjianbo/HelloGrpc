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

// 文件服务
class FileService : public QObject, public MyPackage::MyFileService::Service
{
    Q_OBJECT
public:
    using QObject::QObject;

    // 上传文件
    ::grpc::Status uploadFile(::grpc::ServerContext *context, ::grpc::ServerReader<::MyPackage::FileUploadRequest> *reader, ::MyPackage::FileUploadResponse *response) override;
    // 下载文件
    ::grpc::Status downloadFile(::grpc::ServerContext *context, const ::MyPackage::FileDownloadRequest *request, ::grpc::ServerWriter<::MyPackage::FileDownloadResponse> *writer) override;

signals:
    void updateLog(const QString &log);

private:
    // 缓存文件id从1开始自增
    std::atomic_int64_t cacheId{1};
};
