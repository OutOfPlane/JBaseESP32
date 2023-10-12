#ifndef J_ESP32_NVS_H
#define J_ESP32_NVS_H

#include "configStorage.hpp"
#include "nvs.h"

namespace jFramework
{

    class esp32nvs : public configStorage
    {
    public:
        esp32nvs(const char *name);
        ~esp32nvs();
        j_err openNamespace(const char *name);
        j_err close();
        j_err readUI8(const char *key, uint8_t &value);
        j_err readUI16(const char *key, uint16_t &value);
        j_err readUI32(const char *key, uint32_t &value);
        j_err readUI64(const char *key, uint64_t &value);
        j_err readI8(const char *key, int8_t &value);
        j_err readI16(const char *key, int16_t &value);
        j_err readI32(const char *key, int32_t &value);
        j_err readI64(const char *key, int64_t &value);
        j_err readStr(const char *key, char *value, size_t &length);

        j_err writeUI8(const char *key, uint8_t value);
        j_err writeUI16(const char *key, uint16_t value);
        j_err writeUI32(const char *key, uint32_t value);
        j_err writeUI64(const char *key, uint64_t value);
        j_err writeI8(const char *key, int8_t value);
        j_err writeI16(const char *key, int16_t value);
        j_err writeI32(const char *key, int32_t value);
        j_err writeI64(const char *key, int64_t value);
        j_err writeStr(const char *key, const char *value);

    protected:
    private:
        nvs_handle_t _handle;
        bool _isOpen = false;
    };
} // namespace jFramework

#endif