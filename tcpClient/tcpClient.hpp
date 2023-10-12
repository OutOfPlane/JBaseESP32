#ifndef J_TCP_CLIENT_H
#define J_TCP_CLIENT_H

#include <jObject.hpp>
#include <sys/socket.h>

namespace jFramework
{
    class tcpClient : public jObject
    {
    public:
        tcpClient(const char *name, const char *IP, uint16_t port, int addr_family = AF_INET);
        ~tcpClient();
        j_err openSocket();
        void closeSocket();
        j_err write(const char *data);

    protected:
    private:
        int _addr_family;
        char *_IP;
        struct sockaddr_in _dest_addr;
        int _sock;
    };

} // namespace jFramework

#endif