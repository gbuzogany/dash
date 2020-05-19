// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: dash.proto

#include "dash.pb.h"
#include "dash.grpc.pb.h"

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
namespace dash {

static const char* DashService_method_names[] = {
  "/dash.DashService/UpdateDashIntData",
  "/dash.DashService/UpdateDashFloatData",
  "/dash.DashService/UpdateDashStringData",
  "/dash.DashService/UpdateDashBytesData",
};

std::unique_ptr< DashService::Stub> DashService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< DashService::Stub> stub(new DashService::Stub(channel));
  return stub;
}

DashService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_UpdateDashIntData_(DashService_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_UpdateDashFloatData_(DashService_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_UpdateDashStringData_(DashService_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_UpdateDashBytesData_(DashService_method_names[3], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status DashService::Stub::UpdateDashIntData(::grpc::ClientContext* context, const ::dash::IntValue& request, ::dash::StatusResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_UpdateDashIntData_, context, request, response);
}

void DashService::Stub::experimental_async::UpdateDashIntData(::grpc::ClientContext* context, const ::dash::IntValue* request, ::dash::StatusResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_UpdateDashIntData_, context, request, response, std::move(f));
}

void DashService::Stub::experimental_async::UpdateDashIntData(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::dash::StatusResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_UpdateDashIntData_, context, request, response, std::move(f));
}

void DashService::Stub::experimental_async::UpdateDashIntData(::grpc::ClientContext* context, const ::dash::IntValue* request, ::dash::StatusResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_UpdateDashIntData_, context, request, response, reactor);
}

void DashService::Stub::experimental_async::UpdateDashIntData(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::dash::StatusResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_UpdateDashIntData_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::dash::StatusResponse>* DashService::Stub::AsyncUpdateDashIntDataRaw(::grpc::ClientContext* context, const ::dash::IntValue& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::dash::StatusResponse>::Create(channel_.get(), cq, rpcmethod_UpdateDashIntData_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::dash::StatusResponse>* DashService::Stub::PrepareAsyncUpdateDashIntDataRaw(::grpc::ClientContext* context, const ::dash::IntValue& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::dash::StatusResponse>::Create(channel_.get(), cq, rpcmethod_UpdateDashIntData_, context, request, false);
}

::grpc::Status DashService::Stub::UpdateDashFloatData(::grpc::ClientContext* context, const ::dash::FloatValue& request, ::dash::StatusResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_UpdateDashFloatData_, context, request, response);
}

void DashService::Stub::experimental_async::UpdateDashFloatData(::grpc::ClientContext* context, const ::dash::FloatValue* request, ::dash::StatusResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_UpdateDashFloatData_, context, request, response, std::move(f));
}

void DashService::Stub::experimental_async::UpdateDashFloatData(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::dash::StatusResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_UpdateDashFloatData_, context, request, response, std::move(f));
}

void DashService::Stub::experimental_async::UpdateDashFloatData(::grpc::ClientContext* context, const ::dash::FloatValue* request, ::dash::StatusResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_UpdateDashFloatData_, context, request, response, reactor);
}

void DashService::Stub::experimental_async::UpdateDashFloatData(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::dash::StatusResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_UpdateDashFloatData_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::dash::StatusResponse>* DashService::Stub::AsyncUpdateDashFloatDataRaw(::grpc::ClientContext* context, const ::dash::FloatValue& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::dash::StatusResponse>::Create(channel_.get(), cq, rpcmethod_UpdateDashFloatData_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::dash::StatusResponse>* DashService::Stub::PrepareAsyncUpdateDashFloatDataRaw(::grpc::ClientContext* context, const ::dash::FloatValue& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::dash::StatusResponse>::Create(channel_.get(), cq, rpcmethod_UpdateDashFloatData_, context, request, false);
}

::grpc::Status DashService::Stub::UpdateDashStringData(::grpc::ClientContext* context, const ::dash::StringValue& request, ::dash::StatusResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_UpdateDashStringData_, context, request, response);
}

void DashService::Stub::experimental_async::UpdateDashStringData(::grpc::ClientContext* context, const ::dash::StringValue* request, ::dash::StatusResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_UpdateDashStringData_, context, request, response, std::move(f));
}

void DashService::Stub::experimental_async::UpdateDashStringData(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::dash::StatusResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_UpdateDashStringData_, context, request, response, std::move(f));
}

void DashService::Stub::experimental_async::UpdateDashStringData(::grpc::ClientContext* context, const ::dash::StringValue* request, ::dash::StatusResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_UpdateDashStringData_, context, request, response, reactor);
}

void DashService::Stub::experimental_async::UpdateDashStringData(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::dash::StatusResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_UpdateDashStringData_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::dash::StatusResponse>* DashService::Stub::AsyncUpdateDashStringDataRaw(::grpc::ClientContext* context, const ::dash::StringValue& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::dash::StatusResponse>::Create(channel_.get(), cq, rpcmethod_UpdateDashStringData_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::dash::StatusResponse>* DashService::Stub::PrepareAsyncUpdateDashStringDataRaw(::grpc::ClientContext* context, const ::dash::StringValue& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::dash::StatusResponse>::Create(channel_.get(), cq, rpcmethod_UpdateDashStringData_, context, request, false);
}

::grpc::Status DashService::Stub::UpdateDashBytesData(::grpc::ClientContext* context, const ::dash::BytesValue& request, ::dash::StatusResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_UpdateDashBytesData_, context, request, response);
}

void DashService::Stub::experimental_async::UpdateDashBytesData(::grpc::ClientContext* context, const ::dash::BytesValue* request, ::dash::StatusResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_UpdateDashBytesData_, context, request, response, std::move(f));
}

void DashService::Stub::experimental_async::UpdateDashBytesData(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::dash::StatusResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_UpdateDashBytesData_, context, request, response, std::move(f));
}

void DashService::Stub::experimental_async::UpdateDashBytesData(::grpc::ClientContext* context, const ::dash::BytesValue* request, ::dash::StatusResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_UpdateDashBytesData_, context, request, response, reactor);
}

void DashService::Stub::experimental_async::UpdateDashBytesData(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::dash::StatusResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_UpdateDashBytesData_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::dash::StatusResponse>* DashService::Stub::AsyncUpdateDashBytesDataRaw(::grpc::ClientContext* context, const ::dash::BytesValue& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::dash::StatusResponse>::Create(channel_.get(), cq, rpcmethod_UpdateDashBytesData_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::dash::StatusResponse>* DashService::Stub::PrepareAsyncUpdateDashBytesDataRaw(::grpc::ClientContext* context, const ::dash::BytesValue& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::dash::StatusResponse>::Create(channel_.get(), cq, rpcmethod_UpdateDashBytesData_, context, request, false);
}

DashService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DashService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DashService::Service, ::dash::IntValue, ::dash::StatusResponse>(
          std::mem_fn(&DashService::Service::UpdateDashIntData), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DashService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DashService::Service, ::dash::FloatValue, ::dash::StatusResponse>(
          std::mem_fn(&DashService::Service::UpdateDashFloatData), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DashService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DashService::Service, ::dash::StringValue, ::dash::StatusResponse>(
          std::mem_fn(&DashService::Service::UpdateDashStringData), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DashService_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DashService::Service, ::dash::BytesValue, ::dash::StatusResponse>(
          std::mem_fn(&DashService::Service::UpdateDashBytesData), this)));
}

DashService::Service::~Service() {
}

::grpc::Status DashService::Service::UpdateDashIntData(::grpc::ServerContext* context, const ::dash::IntValue* request, ::dash::StatusResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DashService::Service::UpdateDashFloatData(::grpc::ServerContext* context, const ::dash::FloatValue* request, ::dash::StatusResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DashService::Service::UpdateDashStringData(::grpc::ServerContext* context, const ::dash::StringValue* request, ::dash::StatusResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DashService::Service::UpdateDashBytesData(::grpc::ServerContext* context, const ::dash::BytesValue* request, ::dash::StatusResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace dash

