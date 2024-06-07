#include "OperateService.h"
#include <QCoreApplication>
#include <QFile>
#include <QThread>
#include <QDateTime>
#include <QUrl>
#include <QDebug>

grpc::Status OperateService::insertFile(grpc::ServerContext *context, const MyPackage::FileOperateRequest *request, MyPackage::FileOperateResponse *response)
{
    QString peer = QUrl::fromPercentEncoding(QByteArray::fromStdString(context->peer()));
    // 临时文件缓存id
    int64_t cache_id = request->cacheid();
    auto info = request->info();
    QString file_name = QString::fromStdString(info.filename());
    QString cache_path = QString("%1/Cache/%2").arg(QCoreApplication::applicationDirPath()).arg(QString::number(cache_id));
    int64_t file_time = QDateTime::currentDateTime().toMSecsSinceEpoch();
    // 文件id
    int64_t file_id = file_time;
    QString file_path = QString("%1/File/%2").arg(QCoreApplication::applicationDirPath()).arg(QString::number(file_id));
    bool ok = false;
    if (cache_id != 0) {
        QFile file(cache_path);
        if (file.exists()) {
            QFile::remove(file_path);
            file.copy(file_path);
            file.remove();
            file.setFileName(file_path);
            ok = file.exists();
        }
        info.set_filesize(file.size());
        info.set_fileid(file_id);
    }
    if (ok) {
        info.set_updatetime(file_time);
        std::lock_guard<std::mutex> lock(infoMutex); (void)lock;
        infoMap.insert({file_id, info});
    }
    response->mutable_info()->CopyFrom(info);
    response->set_ok(ok);
    QString log = QString("[%1][%2] insert file [%3:%4] %5.")
                      .arg(peer)
                      .arg(quintptr(QThread::currentThreadId()))
                      .arg(QString::number(file_id))
                      .arg(file_name)
                      .arg(ok ? "success" : "fail");
    emit updateLog(log);
    return grpc::Status::OK;
}

grpc::Status OperateService::deleteFile(grpc::ServerContext *context, const MyPackage::FileOperateRequest *request, MyPackage::FileOperateResponse *response)
{
    QString peer = QUrl::fromPercentEncoding(QByteArray::fromStdString(context->peer()));
    auto &&info = request->info();
    int64_t file_id = info.fileid();
    QString file_path = QString("%1/File/%2").arg(QCoreApplication::applicationDirPath()).arg(QString::number(file_id));
    QFile file(file_path);
    if (file_id != 0 && file.exists()) {
        file.remove();
    }
    bool ok = !file.exists();
    if (ok) {
        std::lock_guard<std::mutex> lock(infoMutex); (void)lock;
        infoMap.erase(file_id);
    }
    response->set_ok(ok);
    QString log = QString("[%1][%2] delete file [%3] %4.")
                      .arg(peer)
                      .arg(quintptr(QThread::currentThreadId()))
                      .arg(QString::number(file_id))
                      .arg(ok ? "success" : "fail");
    emit updateLog(log);
    return grpc::Status::OK;
}

grpc::Status OperateService::updateFile(grpc::ServerContext *context, const MyPackage::FileOperateRequest *request, MyPackage::FileOperateResponse *response)
{
    QString peer = QUrl::fromPercentEncoding(QByteArray::fromStdString(context->peer()));
    // 临时文件缓存id
    int64_t cache_id = request->cacheid();
    auto info = request->info();
    // 文件id
    int64_t file_id = info.fileid();
    QString file_name = QString::fromStdString(info.filename());
    QString cache_path = QString("%1/Cache/%2").arg(QCoreApplication::applicationDirPath()).arg(QString::number(cache_id));
    int64_t file_time = QDateTime::currentDateTime().toMSecsSinceEpoch();
    QString file_path = QString("%1/File/%2").arg(QCoreApplication::applicationDirPath()).arg(QString::number(file_id));
    bool ok = cache_id != 0;
    if (cache_id != 0) {
        QFile file(cache_path);
        if (file.exists()) {
            QFile::remove(file_path);
            file.copy(file_path);
            file.remove();
            file.setFileName(file_path);
            ok = file.exists();
        }
        info.set_filesize(file.size());
    }
    if (ok) {
        info.set_updatetime(file_time);
        std::lock_guard<std::mutex> lock(infoMutex); (void)lock;
        ok = (infoMap.find(file_id) != infoMap.end());
        if (ok) {
            infoMap[file_id] = info;
        }
    }
    response->mutable_info()->CopyFrom(info);
    response->set_ok(ok);
    QString log = QString("[%1][%2] update file [%3:%4] %5.")
                      .arg(peer)
                      .arg(quintptr(QThread::currentThreadId()))
                      .arg(QString::number(file_id))
                      .arg(file_name)
                      .arg(ok ? "success" : "fail");
    emit updateLog(log);
    return grpc::Status::OK;
}

grpc::Status OperateService::selectFile(grpc::ServerContext *context, const MyPackage::FileOperateRequest *request, MyPackage::FileOperateResponse *response)
{
    QString peer = QUrl::fromPercentEncoding(QByteArray::fromStdString(context->peer()));
    auto info = request->info();
    int64_t file_id = info.fileid();
    bool ok = false;
    if (file_id != 0) {
        std::lock_guard<std::mutex> lock(infoMutex); (void)lock;
        ok = (infoMap.find(file_id) != infoMap.end());
        if (ok) {
            info = infoMap.at(file_id);
        }
    }
    QString file_name = QString::fromStdString(info.filename());
    response->mutable_info()->CopyFrom(info);
    response->set_ok(ok);
    QString log = QString("[%1][%2] select file [%3:%4] %5.")
                      .arg(peer)
                      .arg(quintptr(QThread::currentThreadId()))
                      .arg(QString::number(file_id))
                      .arg(file_name)
                      .arg(ok ? "success" : "fail");
    emit updateLog(log);
    return grpc::Status::OK;
}

grpc::Status OperateService::searchFile(grpc::ServerContext *context, const MyPackage::FileSearchRequest *request, MyPackage::FileSearchResponse *response)
{
    QString peer = QUrl::fromPercentEncoding(QByteArray::fromStdString(context->peer()));
    QString condition = QString::fromStdString(request->condition());
    {
        std::lock_guard<std::mutex> lock(infoMutex); (void)lock;
        for (const auto &iter : infoMap) {
            QString file_name = QString::fromStdString(iter.second.filename());
            if (file_name.contains(condition)) {
                response->add_infos()->CopyFrom(iter.second);
            }
        }
    }
    bool ok = true;
    response->set_ok(ok);
    QString log = QString("[%1][%2] search file count [%3] %4.")
                      .arg(peer)
                      .arg(quintptr(QThread::currentThreadId()))
                      .arg(QString::number(response->infos_size()))
                      .arg(ok ? "success" : "fail");
    emit updateLog(log);
    return grpc::Status::OK;
}
