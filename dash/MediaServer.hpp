//
//  MediaServer.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 10/11/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#ifndef MediaServer_h
#define MediaServer_h

#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include "media.grpc.pb.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;
using mediaplayer::StatusResponse;
using mediaplayer::PlayStatus;
using mediaplayer::MediaItem;
using mediaplayer::MediaPlayer;

class MediaServiceImpl final {
public:
    ~MediaServiceImpl();
    void Run();

private:
    // Class encompasing the state and logic needed to serve a request.
    class CallData {
    public:
        // Take in the "service" instance (in this case representing an asynchronous
        // server) and the completion queue "cq" used for asynchronous communication
        // with the gRPC runtime.
        CallData(MediaPlayer::AsyncService* service, ServerCompletionQueue* cq);
        void Proceed();
        
    private:
        // The means of communication with the gRPC runtime for an asynchronous
        // server.
        MediaPlayer::AsyncService* service_;
        // The producer-consumer queue where for asynchronous server notifications.
        ServerCompletionQueue* cq_;
        // Context for the rpc, allowing to tweak aspects of it such as the use
        // of compression, authentication, as well as to send metadata back to the
        // client.
        ServerContext ctx_;
        
        // What we get from the client.
        PlayStatus playStatusRequest_;
        mediaplayer::MediaItem mediaChangedRequest_;
        // What we send back to the client.
        StatusResponse reply_;
        
        // The means to get back to the client.
        ServerAsyncResponseWriter<StatusResponse> responder_;
        
        // Let's implement a tiny state machine with the following states.
        enum CallStatus { CREATE, PROCESS, FINISH };
        CallStatus status_;  // The current serving state.
    };
    
    // This can be run in multiple threads if needed.
    void HandleRpcs();
    
    std::unique_ptr<ServerCompletionQueue> cq_;
    MediaPlayer::AsyncService service_;
    std::unique_ptr<Server> server_;
};

#endif /* MediaServer_h */
