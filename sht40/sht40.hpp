#ifndef J_SHT40_H
#define J_SHT40_H

#include "humidityTemperatureSensor.hpp"
#include "i2cPort.hpp"

namespace jFramework
{
    class SHT40 : public humidityTemperatureSensor
    {
    public:
        SHT40(const char *name, i2cPort *port);
        ~SHT40();
        j_err getHumidity(int32_t &relhumidity_promill);
        j_err getTemperature(int32_t &temperature_dezideg);        

    protected:
    private:
        i2cPort *_port;
        
    };

} // namespace jFramework

#endif