// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: ImageStream.proto

#include "ImageStream.pb.h"
#include "ImageStream.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace CVImageService {

static const char* CVServer_method_names[] = {
  "/CVImageService.CVServer/CVMatImageStream",
  "/CVImageService.CVServer/CVImageProcessFunction",
};

std::unique_ptr< CVServer::Stub> CVServer::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< CVServer::Stub> stub(new CVServer::Stub(channel, options));
  return stub;
}

CVServer::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_CVMatImageStream_(CVServer_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  , rpcmethod_CVImageProcessFunction_(CVServer_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  {}

::grpc::ClientReaderWriter< ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>* CVServer::Stub::CVMatImageStreamRaw(::grpc::ClientContext* context) {
  return ::grpc::internal::ClientReaderWriterFactory< ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>::Create(channel_.get(), rpcmethod_CVMatImageStream_, context);
}

void CVServer::Stub::async::CVMatImageStream(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::CVImageService::ImageMessage,::CVImageService::ImageMessage>* reactor) {
  ::grpc::internal::ClientCallbackReaderWriterFactory< ::CVImageService::ImageMessage,::CVImageService::ImageMessage>::Create(stub_->channel_.get(), stub_->rpcmethod_CVMatImageStream_, context, reactor);
}

::grpc::ClientAsyncReaderWriter< ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>* CVServer::Stub::AsyncCVMatImageStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>::Create(channel_.get(), cq, rpcmethod_CVMatImageStream_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>* CVServer::Stub::PrepareAsyncCVMatImageStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>::Create(channel_.get(), cq, rpcmethod_CVMatImageStream_, context, false, nullptr);
}

::grpc::ClientReaderWriter< ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>* CVServer::Stub::CVImageProcessFunctionRaw(::grpc::ClientContext* context) {
  return ::grpc::internal::ClientReaderWriterFactory< ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>::Create(channel_.get(), rpcmethod_CVImageProcessFunction_, context);
}

void CVServer::Stub::async::CVImageProcessFunction(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::CVImageService::ImageMessage,::CVImageService::ImageMessage>* reactor) {
  ::grpc::internal::ClientCallbackReaderWriterFactory< ::CVImageService::ImageMessage,::CVImageService::ImageMessage>::Create(stub_->channel_.get(), stub_->rpcmethod_CVImageProcessFunction_, context, reactor);
}

::grpc::ClientAsyncReaderWriter< ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>* CVServer::Stub::AsyncCVImageProcessFunctionRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>::Create(channel_.get(), cq, rpcmethod_CVImageProcessFunction_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>* CVServer::Stub::PrepareAsyncCVImageProcessFunctionRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>::Create(channel_.get(), cq, rpcmethod_CVImageProcessFunction_, context, false, nullptr);
}

CVServer::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      CVServer_method_names[0],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< CVServer::Service, ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>(
          [](CVServer::Service* service,
             ::grpc::ServerContext* ctx,
             ::grpc::ServerReaderWriter<::CVImageService::ImageMessage,
             ::CVImageService::ImageMessage>* stream) {
               return service->CVMatImageStream(ctx, stream);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      CVServer_method_names[1],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< CVServer::Service, ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>(
          [](CVServer::Service* service,
             ::grpc::ServerContext* ctx,
             ::grpc::ServerReaderWriter<::CVImageService::ImageMessage,
             ::CVImageService::ImageMessage>* stream) {
               return service->CVImageProcessFunction(ctx, stream);
             }, this)));
}

CVServer::Service::~Service() {
}

::grpc::Status CVServer::Service::CVMatImageStream(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status CVServer::Service::CVImageProcessFunction(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::CVImageService::ImageMessage, ::CVImageService::ImageMessage>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace CVImageService
