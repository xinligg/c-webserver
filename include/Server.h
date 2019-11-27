//#ifndef WEBSERVER_SERVER_H
//#define WEBSERVER_SERVER_H
#pragma once

#include "Socket.h"
#include "HttpParse.h"
#include "HttpResponse.h"
#include "HttpData.h"
#include <memory>
#include "Util.h"


#define BUFFERSIZE 2048

class HttpServer {
public:
    enum FileState {
        FILE_OK,
        FIlE_NOT_FOUND,
        FILE_FORBIDDEN,
        CMD_OK,
        CMD_ERROR
    };

public:
    explicit HttpServer(int port = 80, const char *ip = nullptr) : serverSocket(port, ip) {
        serverSocket.bind();
        serverSocket.listen();
        
        tick = genrandomstring(10);
    }

    void run(int, int max_queue_size = 10000);

    void do_request(std::shared_ptr<void> arg);

private:

    void header(std::shared_ptr<HttpData>);

    FileState static_file(std::shared_ptr<HttpData>, const char *);

    void send(std::shared_ptr<HttpData>, FileState);

    void getMime(std::shared_ptr<HttpData>);
    void hanleIndex();

    ServerSocket serverSocket;

    std::string parameter;
    std::string tick;
    time_t tick_life;
    std::string pw;
    std::string command;
};


//#endif //WEBSERVER_SERVER_H
