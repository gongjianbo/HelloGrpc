#include "FileService.h"
#include <QCoreApplication>
#include <QThread>
#include <QFile>
#include <QUrl>
#include <QDebug>

grpc::Status FileService::uploadFile(grpc::ServerContext *context, ::grpc::ServerReader<MyPackage::FileUploadRequest> *reader, MyPackage::FileUploadResponse *response)
{
    QString peer = QUrl::fromPercentEncoding(QByteArray::fromStdString(context->peer()));
    int64_t cache_id = cacheId.fetch_add(1);
    // 上传的文件写到缓存目录，数据库操作完成后再move到数据目录
    QString cache_path = QString("%1/Cache/%2").arg(QCoreApplication::applicationDirPath()).arg(QString::number(cache_id));
    bool ok = false;
    QFile file(cache_path);
    do {
        file.remove();
        if (!file.open(QIODevice::WriteOnly))
            break;
        MyPackage::FileUploadRequest request;
        if (!reader->Read(&request))
            break;
        int64_t file_size = request.filesize();
        if (file_size <= 0)
            break;
        int64_t read_count = 0;
        while (reader->Read(&request))
        {
            int64_t chunk_size = request.chunksize();
            if (chunk_size != request.chunk().size())
                break;
            int64_t len = file.write(request.chunk().data(), chunk_size);
            if (len != chunk_size)
                break;
            read_count += chunk_size;
            if (read_count >= file_size)
                break;
        }
        file.close();
        ok = (read_count == file_size && read_count > 0);
    } while(false);
    if (file.isOpen())
        file.close();
    // 返回缓存文件id，为0表示失败
    response->set_cacheid(ok ? cache_id : 0);
    QString log = QString("[%1][%2] upload file [%3] %4.")
                      .arg(peer)
                      .arg(quintptr(QThread::currentThreadId()))
                      .arg(QString::number(cache_id))
                      .arg(ok ? "success" : "fail");
    emit updateLog(log);
    return ok ? grpc::Status::OK : grpc::Status::CANCELLED;
}

grpc::Status FileService::downloadFile(grpc::ServerContext *context, const MyPackage::FileDownloadRequest *request, ::grpc::ServerWriter<MyPackage::FileDownloadResponse> *writer)
{
    QString peer = QUrl::fromPercentEncoding(QByteArray::fromStdString(context->peer()));
    int64_t file_id = request->fileid();
    QString file_path = QString("%1/File/%2").arg(QCoreApplication::applicationDirPath()).arg(QString::number(file_id));
    int64_t chunk_size = 10 * 1024 * 1024;
    std::string buffer((std::size_t)chunk_size, (char)'\0');
    bool ok = false;
    QFile file(file_path);
    do {
        if (!file.open(QIODevice::ReadOnly))
            break;
        int64_t file_size = file.size();
        int64_t write_count = 0;
        MyPackage::FileDownloadResponse response;
        response.set_filesize(file_size);
        if (!writer->Write(response))
            break;
        response.clear_filesize();
        while (write_count < file_size)
        {
            int64_t len = file.read(buffer.data(), chunk_size);
            if (len <= 0)
                break;
            buffer.resize(len);
            response.set_allocated_chunk(&buffer);
            response.set_chunksize(len);
            bool w_ok = writer->Write(response);
            (void)response.release_chunk();
            if (!w_ok)
                break;
            write_count += len;
        }
        file.close();
        ok = (write_count == file_size && write_count > 0);
    } while(false);
    if (file.isOpen())
        file.close();
    QString log = QString("[%1][%2] download file [%3] %4.")
                      .arg(peer)
                      .arg(quintptr(QThread::currentThreadId()))
                      .arg(QString::number(file_id))
                      .arg(ok ? "success" : "fail");
    emit updateLog(log);
    return ok ? grpc::Status::OK : grpc::Status::CANCELLED;
}
