#ifndef J_HTTP_CLIENT_H
#define J_HTTP_CLIENT_H

#include "jObject.hpp"
#include "esp_http_client.h"

namespace jFramework
{
    class httpClient : public jObject
    {
    public:
        httpClient(const char *name);
        virtual ~httpClient() {}
        j_err get(char *responseBuffer, uint16_t responseBufferSize, const char *requestUrl);
        j_err getPrintf(char *responseBuffer, uint16_t responseBufferSize, const char *requestUrl, ...);

    protected:
    private:
        esp_http_client_config_t _config;
        esp_http_client_handle_t _client;
    };

} // namespace jFramework

#endif