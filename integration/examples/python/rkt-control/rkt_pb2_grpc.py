# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
import grpc

import rkt_pb2 as rkt__pb2


class RocketteServiceStub(object):
    """Missing associated documentation comment in .proto file"""

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.UpdateIntData = channel.unary_unary(
                '/rkt.RocketteService/UpdateIntData',
                request_serializer=rkt__pb2.IntValue.SerializeToString,
                response_deserializer=rkt__pb2.StatusResponse.FromString,
                )
        self.UpdateFloatData = channel.unary_unary(
                '/rkt.RocketteService/UpdateFloatData',
                request_serializer=rkt__pb2.FloatValue.SerializeToString,
                response_deserializer=rkt__pb2.StatusResponse.FromString,
                )
        self.UpdateStringData = channel.unary_unary(
                '/rkt.RocketteService/UpdateStringData',
                request_serializer=rkt__pb2.StringValue.SerializeToString,
                response_deserializer=rkt__pb2.StatusResponse.FromString,
                )
        self.UpdateBytesData = channel.unary_unary(
                '/rkt.RocketteService/UpdateBytesData',
                request_serializer=rkt__pb2.BytesValue.SerializeToString,
                response_deserializer=rkt__pb2.StatusResponse.FromString,
                )


class RocketteServiceServicer(object):
    """Missing associated documentation comment in .proto file"""

    def UpdateIntData(self, request, context):
        """Missing associated documentation comment in .proto file"""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def UpdateFloatData(self, request, context):
        """Missing associated documentation comment in .proto file"""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def UpdateStringData(self, request, context):
        """Missing associated documentation comment in .proto file"""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def UpdateBytesData(self, request, context):
        """Missing associated documentation comment in .proto file"""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_RocketteServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'UpdateIntData': grpc.unary_unary_rpc_method_handler(
                    servicer.UpdateIntData,
                    request_deserializer=rkt__pb2.IntValue.FromString,
                    response_serializer=rkt__pb2.StatusResponse.SerializeToString,
            ),
            'UpdateFloatData': grpc.unary_unary_rpc_method_handler(
                    servicer.UpdateFloatData,
                    request_deserializer=rkt__pb2.FloatValue.FromString,
                    response_serializer=rkt__pb2.StatusResponse.SerializeToString,
            ),
            'UpdateStringData': grpc.unary_unary_rpc_method_handler(
                    servicer.UpdateStringData,
                    request_deserializer=rkt__pb2.StringValue.FromString,
                    response_serializer=rkt__pb2.StatusResponse.SerializeToString,
            ),
            'UpdateBytesData': grpc.unary_unary_rpc_method_handler(
                    servicer.UpdateBytesData,
                    request_deserializer=rkt__pb2.BytesValue.FromString,
                    response_serializer=rkt__pb2.StatusResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'rkt.RocketteService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))


 # This class is part of an EXPERIMENTAL API.
class RocketteService(object):
    """Missing associated documentation comment in .proto file"""

    @staticmethod
    def UpdateIntData(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/rkt.RocketteService/UpdateIntData',
            rkt__pb2.IntValue.SerializeToString,
            rkt__pb2.StatusResponse.FromString,
            options, channel_credentials,
            call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def UpdateFloatData(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/rkt.RocketteService/UpdateFloatData',
            rkt__pb2.FloatValue.SerializeToString,
            rkt__pb2.StatusResponse.FromString,
            options, channel_credentials,
            call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def UpdateStringData(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/rkt.RocketteService/UpdateStringData',
            rkt__pb2.StringValue.SerializeToString,
            rkt__pb2.StatusResponse.FromString,
            options, channel_credentials,
            call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def UpdateBytesData(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/rkt.RocketteService/UpdateBytesData',
            rkt__pb2.BytesValue.SerializeToString,
            rkt__pb2.StatusResponse.FromString,
            options, channel_credentials,
            call_credentials, compression, wait_for_ready, timeout, metadata)
