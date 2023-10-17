#ifndef J_WIFI_H
#define J_WIFI_H

#include "networkAdapter.hpp"
#include <lwip/netif.h>
#include <lwip/tcpip.h>


namespace jFramework
{

    class w5500Adapter : public networkAdapter
    {
    public:
        w5500Adapter(const char *name, bool dhcp, IPAddress local_ip , IPAddress subnet , IPAddress gateway , IPAddress dns_server);
        virtual ~w5500Adapter() {}
        

    protected:
        j_err _start();
        j_err createNetif();

    private:
        esp_netif_t *_ap_netif;
        
    };

} // namespace jFramework

#endif