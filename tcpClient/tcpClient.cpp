#include "tcpClient.hpp"
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h> // struct addrinfo
#include <arpa/inet.h>
#include "esp_netif.h"
#include "esp_log.h"

using namespace jFramework;

tcpClient::tcpClient(const char *name, const char *IP, uint16_t port, int addr_family)
    : jObject(name), _addr_family(addr_family)
{
    inet_pton(AF_INET, IP, &_dest_addr.sin_addr);
    _dest_addr.sin_family = AF_INET;
    _dest_addr.sin_port = htons(port);
    _IP = strdup(IP);
    _sock = -1;
}

tcpClient::~tcpClient()
{
    free(_IP);
}

j_err tcpClient::openSocket()
{
    _sock = socket(_addr_family, SOCK_STREAM, IPPROTO_IP);
    if (_sock < 0)
    {
        J_LOGD("Unable to create socket: errno %d", errno);
        return J_ERR_INTERNAL;
    }
    J_LOGI("Socket created, connecting to %s:%d", _IP, _dest_addr.sin_port);

    int err = connect(_sock, (struct sockaddr *)&_dest_addr, sizeof(_dest_addr));
    if (err != 0)
    {
        J_LOGD("Socket unable to connect: errno %d", errno);
        return J_ERR_INTERNAL;
    }
    J_LOGI("Successfully connected");
    return J_OK;
}

void tcpClient::closeSocket()
{
    if (_sock != -1)
    {
        J_LOGI("Shutting down socket");
        shutdown(_sock, 0);
        close(_sock);
    }
}

j_err tcpClient::write(const char *data)
{
    int err = send(_sock, data, strlen(data), 0);
    if (err < 0)
    {
        J_LOGD("Error occurred during sending: errno %d", errno);
        return J_ERR_INTERNAL;
    }
    return J_OK;
}

// TODO: receiving
/*

int len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);
        // Error occurred during receiving
        if (len < 0)
        {
            ESP_LOGE(TAG, "recv failed: errno %d", errno);
            break;
        }
        // Data received
        else
        {
            rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string
            ESP_LOGI(TAG, "Received %d bytes from %s:", len, host_ip);
            ESP_LOGI(TAG, "%s", rx_buffer);
        }

*/