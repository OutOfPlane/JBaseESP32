#ifndef J_ESP32_IO_PIN_H
#define J_ESP32_IO_PIN_H

#include "ioPin.hpp"

namespace jFramework
{
    class esp32ioPin : public ioPin
    {
    public:
        esp32ioPin(const char *name, uint8_t pinNumber);
        ~esp32ioPin();
        j_err mode(pinDirection dir);
        j_err set(uint8_t value);
        j_err get(uint8_t &value);
        bool canSet();
        bool canGet();
        j_err setVoltage(int32_t voltage_mV);
        j_err getVoltage(int32_t &voltage_mV);

    private:
        int32_t _level = 0;
        uint8_t _this_ledc_channel;
        pinDirection _dir = PIN_UNSET;
        static uint8_t _ledc_channel;
        static uint8_t _ledc_timer_config_done;
    };

} // namespace jFramework

#endif