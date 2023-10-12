#ifndef J_WIFI_H
#define J_WIFI_H

#include "networkAdapter.hpp"
#include "freertos/event_groups.h"

namespace jFramework
{

    class wifiAdapter : public networkAdapter
    {
    public:
        wifiAdapter(const char *name, int maxRetries);
        virtual ~wifiAdapter() {}
        j_err setSSID(const char *SSID);
        j_err getSSID(char *SSID);
        j_err setPWD(const char *PWD);
        j_err startConnect();
        j_err waitConnected();
        j_err startSTA(const char *SSID, const char *PWD);
        esp_netif_t *getNetIFAP();

    protected:
        j_err _start();
        j_err createNetif();
        static void _eventHandler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

    private:
        int _retryNum = 0;
        int _maxRetries = 5;
        bool _wifiInitDone = false;
        bool _wifiStarted = false;
        EventGroupHandle_t _event_group;
        wifi_config_t _config;
        esp_netif_t *_ap_netif;
        
    };

} // namespace jFramework

#endif