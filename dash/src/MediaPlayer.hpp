//
//  MediaPlayer.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 02/04/2020.
//  Copyright © 2020 gbuzogany.com. All rights reserved.
//

#ifndef MediaPlayer_hpp
#define MediaPlayer_hpp

#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include "dash.grpc.pb.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;

using dash::StatusResponse;
using dash::PlayStatus;
using dash::MediaItem;
using dash::MediaPlayer;

class Dashboard;

class MediaPlayerImpl final : public MediaPlayer::Service {
public:
    MediaPlayerImpl(Dashboard* dash);
private:
    Dashboard* dash_;

    Status PlayStatusChanged(ServerContext* context, const PlayStatus* request, StatusResponse* response);
    Status MediaChanged(ServerContext *context, const MediaItem *request, StatusResponse *response);
};

#endif /* MediaPlayer_hpp */
