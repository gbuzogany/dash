//
//  MediaService.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 10/11/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include "MediaService.hpp"
#include "media.grpc.pb.h"
#include "Dashboard.hpp"

MediaServiceImpl::MediaServiceImpl(Dashboard* dash) {
    dash_ = dash;
}

Status MediaServiceImpl::PlayStatusChanged(ServerContext* context, const PlayStatus* request, StatusResponse* response) {
    (void) context;
    (void) request;
    (void) response;
    printf("%s\n", request->playstatus().c_str());
    
    dash_->setPlayStatus(request->playstatus());
    
    response->set_status(200);
    return Status::OK;
}

Status MediaServiceImpl::MediaChanged(ServerContext *context, const MediaItem *request, StatusResponse *response) {
    
    DashMediaItem dmi;
    dmi.title = request->title();
    dmi.artist = request->artist();
    dmi.album = request->album();
    
    dash_->setNowPlaying(dmi);
    
    printf("%s\n", request->title().c_str());
    printf("%s\n", request->artist().c_str());
    printf("%s\n", request->album().c_str());
    
    response->set_status(200);
    return Status::OK;
}
