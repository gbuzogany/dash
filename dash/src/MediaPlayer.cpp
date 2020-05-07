//
//  MediaPlayer.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 02/04/2020.
//  Copyright © 2020 gbuzogany.com. All rights reserved.
//

#include "MediaPlayer.hpp"
#include "Dashboard.hpp"

MediaPlayerImpl::MediaPlayerImpl(Dashboard* dash) {
    dash_ = dash;
}

Status MediaPlayerImpl::PlayStatusChanged(ServerContext* context, const PlayStatus* request, StatusResponse* response) {
    printf("%s\n", request->playstatus().c_str());
    
    dash_->setPlayStatus(request->playstatus());
    
    response->set_status(200);
    return Status::OK;
}

Status MediaPlayerImpl::MediaChanged(ServerContext *context, const MediaItem *request, StatusResponse *response) {
    
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
