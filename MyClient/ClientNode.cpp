#include "ClientNode.h"
#include <QThread>
#include <QRandomGenerator>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QDebug>

bool ClientNode::doConnect(const QString &opAddress, const QString &fileAddress)
{
    if (isConnected()) {
        doDisconnect();
    }
    grpc::ChannelArguments args;
    // 消息默认限制 4M
    args.SetMaxReceiveMessageSize(-1);
    args.SetMaxSendMessageSize(-1);
    opChannel = grpc::CreateCustomChannel(opAddress.toStdString(), grpc::InsecureChannelCredentials(), args);
    bool ret = opChannel->WaitForConnected(std::chrono::system_clock::now() + std::chrono::seconds(2));
    auto &&state = opChannel->GetState(true);
    if (!ret && state >= GRPC_CHANNEL_TRANSIENT_FAILURE) {
        opChannel.reset();
        return false;
    }
    if (opChannel) {
        opStub = MyPackage::MyOperateService::NewStub(opChannel);
    }
    fileChannel = grpc::CreateCustomChannel(fileAddress.toStdString(), grpc::InsecureChannelCredentials(), args);
    if (fileChannel) {
        fileStub = MyPackage::MyFileService::NewStub(fileChannel);
    }
    if (!opStub || !fileStub) {
        doDisconnect();
        return false;
    }
    return true;
}

bool ClientNode::doDisconnect()
{
    opStub.reset();
    opChannel.reset();
    fileStub.reset();
    fileChannel.reset();
    return true;
}

bool ClientNode::isConnected() const
{
    return (opStub && fileStub);
}

bool ClientNode::addressValid(const QString &address)
{
    return false;
}

bool ClientNode::insertFile(MyPackage::FileInfo &info, const QString &path)
{
    int64_t cache_id = 0;
    bool ok = false;
    do {
        if (!isConnected())
            break;
        cache_id = uploadFile(path);
        if (cache_id == 0)
            break;
        // 远程调用
        grpc::ClientContext context;
        MyPackage::FileOperateRequest request;
        QFileInfo f_info(path);
        info.set_filename(f_info.fileName().toStdString());
        info.set_filesize(f_info.size());
        request.mutable_info()->CopyFrom(info);
        request.set_cacheid(cache_id);
        MyPackage::FileOperateResponse response;
        grpc::Status status = opStub->insertFile(&context, request, &response);
        if (status.ok()) {
            info = response.info();
            ok = response.ok();
        }
    } while(false);
    QString log = QString("[this] insert file [%1:%2] %3.")
                      .arg(QString::number(cache_id))
                      .arg(QFileInfo(path).fileName())
                      .arg(ok ? "success" : "fail");
    emit updateLog(log);
    return ok;
}

bool ClientNode::deleteFile(int64_t id)
{
    bool ok = false;
    do {
        if (!isConnected())
            break;
        if (id == 0)
            break;
        // 远程调用
        grpc::ClientContext context;
        MyPackage::FileOperateRequest request;
        request.mutable_info()->set_fileid(id);
        MyPackage::FileOperateResponse response;
        grpc::Status status = opStub->deleteFile(&context, request, &response);
        if (status.ok()) {
            ok = response.ok();
        }
    } while(false);
    QString log = QString("[this] delete file [%1] %2.")
                      .arg(QString::number(id))
                      .arg(ok ? "success" : "fail");
    emit updateLog(log);
    return ok;
}

bool ClientNode::updateFile(MyPackage::FileInfo &info, const QString &path)
{
    int64_t cache_id = 0;
    bool ok = false;
    do {
        if (!isConnected())
            break;
        cache_id = uploadFile(path);
        if (cache_id == 0 && !path.isEmpty())
            break;
        // 远程调用
        grpc::ClientContext context;
        MyPackage::FileOperateRequest request;
        QFileInfo f_info(path);
        info.set_filename(f_info.fileName().toStdString());
        info.set_filesize(f_info.size());
        request.mutable_info()->CopyFrom(info);
        request.set_cacheid(cache_id);
        MyPackage::FileOperateResponse response;
        grpc::Status status = opStub->updateFile(&context, request, &response);
        if (status.ok()) {
            info = response.info();
            ok = response.ok();
        }
    } while(false);
    QString log = QString("[this] update file [%1:%2] %3.")
                      .arg(QString::number(cache_id))
                      .arg(QFileInfo(path).fileName())
                      .arg(ok ? "success" : "fail");
    emit updateLog(log);
    return ok;
}

bool ClientNode::selectFile(MyPackage::FileInfo &info, int64_t id)
{
    bool ok = false;
    do {
        if (!isConnected())
            break;
        if (id == 0)
            break;
        // 远程调用
        grpc::ClientContext context;
        MyPackage::FileOperateRequest request;
        request.mutable_info()->set_fileid(id);
        MyPackage::FileOperateResponse response;
        grpc::Status status = opStub->selectFile(&context, request, &response);
        if (status.ok()) {
            info = response.info();
            ok = response.ok();
        }
    } while(false);
    QString log = QString("[this] select file [%1:%2] %3.")
                      .arg(QString::number(id))
                      .arg(QString::fromStdString(info.filename()))
                      .arg(ok ? "success" : "fail");
    emit updateLog(log);
    return ok;
}

bool ClientNode::searchFile(std::vector<MyPackage::FileInfo> &infos, const QString &condition)
{
    bool ok = false;
    do {
        if (!isConnected())
            break;
        // 远程调用
        grpc::ClientContext context;
        MyPackage::FileSearchRequest request;
        request.set_condition(condition.toStdString());
        MyPackage::FileSearchResponse response;
        grpc::Status status = opStub->searchFile(&context, request, &response);
        if (status.ok()) {
            for (int i = 0; i < response.infos_size(); i++)
            {
                auto &&image = response.infos(i);
                infos.push_back(image);
            }
            ok = response.ok();
        }
    } while(false);
    QString log = QString("[this] search file count [%1] %2.")
                      .arg(QString::number(infos.size()))
                      .arg(ok ? "success" : "fail");
    emit updateLog(log);
    for (size_t i = 0; i < infos.size(); i++)
    {
        auto &&info = infos.at(i);
        QString log = QString("[%1] [id:%2] [name:%3].")
                          .arg(QString::number(i))
                          .arg(QString::number(info.fileid()))
                          .arg(QString::fromStdString(info.filename()));
        emit updateLog(log);
    }
    return ok;
}

int64_t ClientNode::uploadFile(const QString &path)
{
    int64_t id = 0;
    QFile file(path);
    do {
        if (!isConnected())
            break;
        if (path.isEmpty())
            break;;
        qint64 file_size = file.size();
        if (file_size <= 0)
            return 0;
        grpc::ClientContext context;
        MyPackage::FileUploadRequest request;
        MyPackage::FileUploadResponse response;
        auto &&writer = fileStub->uploadFile(&context, &response);
        if (!writer)
            break;
        request.set_filesize(file_size);
        if (!writer->Write(request))
            break;
        request.clear_filesize();
        if (!file.open(QIODevice::ReadOnly))
            return 0;
        qint64 chunk_size = 10 * 1024 * 1024;
        std::string buffer((std::size_t)chunk_size, (char)'\0');
        qint64 write_count = 0;
        while (write_count < file_size)
        {
            int64_t len = file.read(buffer.data(), chunk_size);
            if (len <= 0)
                break;
            buffer.resize(len);
            request.set_allocated_chunk(&buffer);
            request.set_chunksize(len);
            bool w_ok = writer->Write(request);
            (void)request.release_chunk();
            if (!w_ok)
                break;
            write_count += len;
        }
        file.close();
        writer->WritesDone();
        grpc::Status status = writer->Finish();
        if (write_count == file_size && status.ok()) {
            id = response.cacheid();
        }
    } while(false);
    if (file.isOpen())
        file.close();
    bool ok = id != 0;
    QString log = QString("[this] upload file [%1:%2] %3.")
                      .arg(QString::number(id))
                      .arg(QFileInfo(path).fileName())
                      .arg(ok ? "success" : "fail");
    emit updateLog(log);
    return id;
}

bool ClientNode::downloadFile(int64_t id, const QString &path)
{
    bool ok = false;
    QFile file(path);
    do {
        if (!isConnected())
            break;
        file.remove();
        QFileInfo f_info(path);
        QDir f_dir(f_info.absolutePath());
        if (!f_dir.exists() && !f_dir.mkpath(f_info.absolutePath())) {
            break;
        }
        if (!file.open(QIODevice::WriteOnly)) {
            break;
        }
        grpc::ClientContext context;
        MyPackage::FileDownloadRequest request;
        request.set_fileid(id);
        auto &&reader = fileStub->downloadFile(&context, request);
        if (!reader) {
            break;
        }
        MyPackage::FileDownloadResponse response;
        if (!reader->Read(&response))
            break;
        int64_t file_size = response.filesize();
        if (file_size <= 0)
            break;
        qint64 read_count = 0;
        while (reader->Read(&response)) {
            qint64 chunk_size = response.chunksize();
            if (chunk_size != response.chunk().size())
                break;
            qint64 len = file.write(response.chunk().data(), chunk_size);
            if (len != chunk_size)
                break;
            read_count += chunk_size;
            if (read_count >= file_size)
                break;
        }
        file.close();
        ok = (read_count == file_size && read_count > 0);
        grpc::Status status = reader->Finish();
        if (!status.ok()) {
            ok = false;
        }
    } while(false);
    if (file.isOpen())
        file.close();
    QString log = QString("[this] download file [%1] %2.")
                      .arg(QString::number(id))
                      .arg(ok ? "success" : "fail");
    emit updateLog(log);
    return ok;
}
