//
//  MediaService.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 10/11/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#ifndef MediaService_h
#define MediaService_h

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

class Dashboard;

class MediaServiceImpl final : public MediaPlayer::Service {
public:
    MediaServiceImpl(Dashboard* dash);
private:
    Dashboard* dash_;
    
    Status PlayStatusChanged(ServerContext* context, const PlayStatus* request, StatusResponse* response);
    Status MediaChanged(ServerContext *context, const MediaItem *request, StatusResponse *response);
};

#endif /* MediaService_h */
