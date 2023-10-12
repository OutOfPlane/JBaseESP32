#include "esp32nvs.hpp"
#include "nvs_flash.h"

using namespace jFramework;

esp32nvs::esp32nvs(const char *name)
    : configStorage(name)
{
}

esp32nvs::~esp32nvs()
{
}

j_err jFramework::esp32nvs::openNamespace(const char *name)
{
    j_err erg = j_err_translate(nvs_open(name, NVS_READWRITE, &_handle));
    if (erg != J_OK) {
        J_ERROR_DECODE(erg);
        return erg;
    }
    _isOpen = true;
    return J_OK;
}

j_err jFramework::esp32nvs::close()
{
    if(!_isOpen)
        return J_ERR_INVALID_STATE;
    j_err erg = j_err_translate(nvs_commit(_handle));
    nvs_close(_handle);
    return erg;
}

j_err jFramework::esp32nvs::readUI8(const char *key, uint8_t &value)
{
    if(!_isOpen)
        return J_ERR_INVALID_STATE;
    j_err erg = j_err_translate(nvs_get_u8(_handle, key, &value));
    return erg;
}

j_err jFramework::esp32nvs::readStr(const char *key, char *value, size_t &length)
{
    if(!_isOpen)
        return J_ERR_INVALID_STATE;
    j_err erg = j_err_translate(nvs_get_str(_handle, key, value, &length));
    return erg;
}

j_err jFramework::esp32nvs::writeUI8(const char *key, uint8_t value)
{
    if(!_isOpen)
        return J_ERR_INVALID_STATE;
    j_err erg = j_err_translate(nvs_set_u8(_handle, key, value));
    if(erg == J_OK)
        erg = j_err_translate(nvs_commit(_handle));
    return erg;
}

j_err jFramework::esp32nvs::writeStr(const char *key, const char *value)
{
    if(!_isOpen)
        return J_ERR_INVALID_STATE;
    j_err erg = j_err_translate(nvs_set_str(_handle, key, value));
    if(erg == J_OK)
        erg = j_err_translate(nvs_commit(_handle));
    return erg;
}
