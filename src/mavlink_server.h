/*
 * This file is part of the Camera Streaming Daemon
 *
 * Copyright (C) 2017  Intel Corporation. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <map>
#include <mavlink.h>
#include <memory>
#include <vector>

#include "socket.h"
#include "stream.h"

class MavlinkServer {
public:
    MavlinkServer(std::vector<std::unique_ptr<Stream>> &streams);
    ~MavlinkServer();
    void start();
    void stop();

private:
    const std::vector<std::unique_ptr<Stream>> &_streams;
    bool _is_running;
    unsigned int _timeout_handler;
    UDPSocket _udp;

    void _message_received(const struct buffer &buf);
    void _handle_mavlink_message(mavlink_message_t *msg);
    void _handle_camera_info_request(unsigned int camera_id);
    int _get_system_id();
    friend bool _heartbeat_cb(void *data);
};
