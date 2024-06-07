// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: MyProto.proto

#include "MyProto.pb.h"
#include "MyProto.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace MyPackage {

static const char* MyFileService_method_names[] = {
  "/MyPackage.MyFileService/uploadFile",
  "/MyPackage.MyFileService/downloadFile",
};

std::unique_ptr< MyFileService::Stub> MyFileService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< MyFileService::Stub> stub(new MyFileService::Stub(channel, options));
  return stub;
}

MyFileService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_uploadFile_(MyFileService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::CLIENT_STREAMING, channel)
  , rpcmethod_downloadFile_(MyFileService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  {}

::grpc::ClientWriter< ::MyPackage::FileUploadRequest>* MyFileService::Stub::uploadFileRaw(::grpc::ClientContext* context, ::MyPackage::FileUploadResponse* response) {
  return ::grpc::internal::ClientWriterFactory< ::MyPackage::FileUploadRequest>::Create(channel_.get(), rpcmethod_uploadFile_, context, response);
}

void MyFileService::Stub::async::uploadFile(::grpc::ClientContext* context, ::MyPackage::FileUploadResponse* response, ::grpc::ClientWriteReactor< ::MyPackage::FileUploadRequest>* reactor) {
  ::grpc::internal::ClientCallbackWriterFactory< ::MyPackage::FileUploadRequest>::Create(stub_->channel_.get(), stub_->rpcmethod_uploadFile_, context, response, reactor);
}

::grpc::ClientAsyncWriter< ::MyPackage::FileUploadRequest>* MyFileService::Stub::AsyncuploadFileRaw(::grpc::ClientContext* context, ::MyPackage::FileUploadResponse* response, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::MyPackage::FileUploadRequest>::Create(channel_.get(), cq, rpcmethod_uploadFile_, context, response, true, tag);
}

::grpc::ClientAsyncWriter< ::MyPackage::FileUploadRequest>* MyFileService::Stub::PrepareAsyncuploadFileRaw(::grpc::ClientContext* context, ::MyPackage::FileUploadResponse* response, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::MyPackage::FileUploadRequest>::Create(channel_.get(), cq, rpcmethod_uploadFile_, context, response, false, nullptr);
}

::grpc::ClientReader< ::MyPackage::FileDownloadResponse>* MyFileService::Stub::downloadFileRaw(::grpc::ClientContext* context, const ::MyPackage::FileDownloadRequest& request) {
  return ::grpc::internal::ClientReaderFactory< ::MyPackage::FileDownloadResponse>::Create(channel_.get(), rpcmethod_downloadFile_, context, request);
}

void MyFileService::Stub::async::downloadFile(::grpc::ClientContext* context, const ::MyPackage::FileDownloadRequest* request, ::grpc::ClientReadReactor< ::MyPackage::FileDownloadResponse>* reactor) {
  ::grpc::internal::ClientCallbackReaderFactory< ::MyPackage::FileDownloadResponse>::Create(stub_->channel_.get(), stub_->rpcmethod_downloadFile_, context, request, reactor);
}

::grpc::ClientAsyncReader< ::MyPackage::FileDownloadResponse>* MyFileService::Stub::AsyncdownloadFileRaw(::grpc::ClientContext* context, const ::MyPackage::FileDownloadRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::MyPackage::FileDownloadResponse>::Create(channel_.get(), cq, rpcmethod_downloadFile_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::MyPackage::FileDownloadResponse>* MyFileService::Stub::PrepareAsyncdownloadFileRaw(::grpc::ClientContext* context, const ::MyPackage::FileDownloadRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::MyPackage::FileDownloadResponse>::Create(channel_.get(), cq, rpcmethod_downloadFile_, context, request, false, nullptr);
}

MyFileService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MyFileService_method_names[0],
      ::grpc::internal::RpcMethod::CLIENT_STREAMING,
      new ::grpc::internal::ClientStreamingHandler< MyFileService::Service, ::MyPackage::FileUploadRequest, ::MyPackage::FileUploadResponse>(
          [](MyFileService::Service* service,
             ::grpc::ServerContext* ctx,
             ::grpc::ServerReader<::MyPackage::FileUploadRequest>* reader,
             ::MyPackage::FileUploadResponse* resp) {
               return service->uploadFile(ctx, reader, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MyFileService_method_names[1],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< MyFileService::Service, ::MyPackage::FileDownloadRequest, ::MyPackage::FileDownloadResponse>(
          [](MyFileService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::MyPackage::FileDownloadRequest* req,
             ::grpc::ServerWriter<::MyPackage::FileDownloadResponse>* writer) {
               return service->downloadFile(ctx, req, writer);
             }, this)));
}

MyFileService::Service::~Service() {
}

::grpc::Status MyFileService::Service::uploadFile(::grpc::ServerContext* context, ::grpc::ServerReader< ::MyPackage::FileUploadRequest>* reader, ::MyPackage::FileUploadResponse* response) {
  (void) context;
  (void) reader;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status MyFileService::Service::downloadFile(::grpc::ServerContext* context, const ::MyPackage::FileDownloadRequest* request, ::grpc::ServerWriter< ::MyPackage::FileDownloadResponse>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


static const char* MyOperateService_method_names[] = {
  "/MyPackage.MyOperateService/insertFile",
  "/MyPackage.MyOperateService/deleteFile",
  "/MyPackage.MyOperateService/updateFile",
  "/MyPackage.MyOperateService/selectFile",
  "/MyPackage.MyOperateService/searchFile",
};

std::unique_ptr< MyOperateService::Stub> MyOperateService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< MyOperateService::Stub> stub(new MyOperateService::Stub(channel, options));
  return stub;
}

MyOperateService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_insertFile_(MyOperateService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_deleteFile_(MyOperateService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_updateFile_(MyOperateService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_selectFile_(MyOperateService_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_searchFile_(MyOperateService_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status MyOperateService::Stub::insertFile(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest& request, ::MyPackage::FileOperateResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::MyPackage::FileOperateRequest, ::MyPackage::FileOperateResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_insertFile_, context, request, response);
}

void MyOperateService::Stub::async::insertFile(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest* request, ::MyPackage::FileOperateResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::MyPackage::FileOperateRequest, ::MyPackage::FileOperateResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_insertFile_, context, request, response, std::move(f));
}

void MyOperateService::Stub::async::insertFile(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest* request, ::MyPackage::FileOperateResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_insertFile_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::MyPackage::FileOperateResponse>* MyOperateService::Stub::PrepareAsyncinsertFileRaw(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::MyPackage::FileOperateResponse, ::MyPackage::FileOperateRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_insertFile_, context, request);
}

::grpc::ClientAsyncResponseReader< ::MyPackage::FileOperateResponse>* MyOperateService::Stub::AsyncinsertFileRaw(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncinsertFileRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status MyOperateService::Stub::deleteFile(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest& request, ::MyPackage::FileOperateResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::MyPackage::FileOperateRequest, ::MyPackage::FileOperateResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_deleteFile_, context, request, response);
}

void MyOperateService::Stub::async::deleteFile(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest* request, ::MyPackage::FileOperateResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::MyPackage::FileOperateRequest, ::MyPackage::FileOperateResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_deleteFile_, context, request, response, std::move(f));
}

void MyOperateService::Stub::async::deleteFile(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest* request, ::MyPackage::FileOperateResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_deleteFile_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::MyPackage::FileOperateResponse>* MyOperateService::Stub::PrepareAsyncdeleteFileRaw(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::MyPackage::FileOperateResponse, ::MyPackage::FileOperateRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_deleteFile_, context, request);
}

::grpc::ClientAsyncResponseReader< ::MyPackage::FileOperateResponse>* MyOperateService::Stub::AsyncdeleteFileRaw(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncdeleteFileRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status MyOperateService::Stub::updateFile(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest& request, ::MyPackage::FileOperateResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::MyPackage::FileOperateRequest, ::MyPackage::FileOperateResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_updateFile_, context, request, response);
}

void MyOperateService::Stub::async::updateFile(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest* request, ::MyPackage::FileOperateResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::MyPackage::FileOperateRequest, ::MyPackage::FileOperateResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_updateFile_, context, request, response, std::move(f));
}

void MyOperateService::Stub::async::updateFile(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest* request, ::MyPackage::FileOperateResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_updateFile_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::MyPackage::FileOperateResponse>* MyOperateService::Stub::PrepareAsyncupdateFileRaw(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::MyPackage::FileOperateResponse, ::MyPackage::FileOperateRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_updateFile_, context, request);
}

::grpc::ClientAsyncResponseReader< ::MyPackage::FileOperateResponse>* MyOperateService::Stub::AsyncupdateFileRaw(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncupdateFileRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status MyOperateService::Stub::selectFile(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest& request, ::MyPackage::FileOperateResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::MyPackage::FileOperateRequest, ::MyPackage::FileOperateResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_selectFile_, context, request, response);
}

void MyOperateService::Stub::async::selectFile(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest* request, ::MyPackage::FileOperateResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::MyPackage::FileOperateRequest, ::MyPackage::FileOperateResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_selectFile_, context, request, response, std::move(f));
}

void MyOperateService::Stub::async::selectFile(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest* request, ::MyPackage::FileOperateResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_selectFile_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::MyPackage::FileOperateResponse>* MyOperateService::Stub::PrepareAsyncselectFileRaw(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::MyPackage::FileOperateResponse, ::MyPackage::FileOperateRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_selectFile_, context, request);
}

::grpc::ClientAsyncResponseReader< ::MyPackage::FileOperateResponse>* MyOperateService::Stub::AsyncselectFileRaw(::grpc::ClientContext* context, const ::MyPackage::FileOperateRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncselectFileRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status MyOperateService::Stub::searchFile(::grpc::ClientContext* context, const ::MyPackage::FileSearchRequest& request, ::MyPackage::FileSearchResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::MyPackage::FileSearchRequest, ::MyPackage::FileSearchResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_searchFile_, context, request, response);
}

void MyOperateService::Stub::async::searchFile(::grpc::ClientContext* context, const ::MyPackage::FileSearchRequest* request, ::MyPackage::FileSearchResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::MyPackage::FileSearchRequest, ::MyPackage::FileSearchResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_searchFile_, context, request, response, std::move(f));
}

void MyOperateService::Stub::async::searchFile(::grpc::ClientContext* context, const ::MyPackage::FileSearchRequest* request, ::MyPackage::FileSearchResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_searchFile_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::MyPackage::FileSearchResponse>* MyOperateService::Stub::PrepareAsyncsearchFileRaw(::grpc::ClientContext* context, const ::MyPackage::FileSearchRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::MyPackage::FileSearchResponse, ::MyPackage::FileSearchRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_searchFile_, context, request);
}

::grpc::ClientAsyncResponseReader< ::MyPackage::FileSearchResponse>* MyOperateService::Stub::AsyncsearchFileRaw(::grpc::ClientContext* context, const ::MyPackage::FileSearchRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncsearchFileRaw(context, request, cq);
  result->StartCall();
  return result;
}

MyOperateService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MyOperateService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MyOperateService::Service, ::MyPackage::FileOperateRequest, ::MyPackage::FileOperateResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MyOperateService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::MyPackage::FileOperateRequest* req,
             ::MyPackage::FileOperateResponse* resp) {
               return service->insertFile(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MyOperateService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MyOperateService::Service, ::MyPackage::FileOperateRequest, ::MyPackage::FileOperateResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MyOperateService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::MyPackage::FileOperateRequest* req,
             ::MyPackage::FileOperateResponse* resp) {
               return service->deleteFile(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MyOperateService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MyOperateService::Service, ::MyPackage::FileOperateRequest, ::MyPackage::FileOperateResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MyOperateService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::MyPackage::FileOperateRequest* req,
             ::MyPackage::FileOperateResponse* resp) {
               return service->updateFile(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MyOperateService_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MyOperateService::Service, ::MyPackage::FileOperateRequest, ::MyPackage::FileOperateResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MyOperateService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::MyPackage::FileOperateRequest* req,
             ::MyPackage::FileOperateResponse* resp) {
               return service->selectFile(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MyOperateService_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MyOperateService::Service, ::MyPackage::FileSearchRequest, ::MyPackage::FileSearchResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MyOperateService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::MyPackage::FileSearchRequest* req,
             ::MyPackage::FileSearchResponse* resp) {
               return service->searchFile(ctx, req, resp);
             }, this)));
}

MyOperateService::Service::~Service() {
}

::grpc::Status MyOperateService::Service::insertFile(::grpc::ServerContext* context, const ::MyPackage::FileOperateRequest* request, ::MyPackage::FileOperateResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status MyOperateService::Service::deleteFile(::grpc::ServerContext* context, const ::MyPackage::FileOperateRequest* request, ::MyPackage::FileOperateResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status MyOperateService::Service::updateFile(::grpc::ServerContext* context, const ::MyPackage::FileOperateRequest* request, ::MyPackage::FileOperateResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status MyOperateService::Service::selectFile(::grpc::ServerContext* context, const ::MyPackage::FileOperateRequest* request, ::MyPackage::FileOperateResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status MyOperateService::Service::searchFile(::grpc::ServerContext* context, const ::MyPackage::FileSearchRequest* request, ::MyPackage::FileSearchResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace MyPackage

