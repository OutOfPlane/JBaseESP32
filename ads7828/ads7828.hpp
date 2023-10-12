#ifndef J_ADS7828_H
#define J_ADS7828_H

#include "adc.hpp"
#include "i2cPort.hpp"

namespace jFramework
{
    class ads7828 : public ADC
    {
    public:
        ads7828(const char *name, i2cPort *port);
        j_err selectChannel(uint16_t channel);
        j_err read(int32_t &value_mV);

    protected:
    private:
        i2cPort *_port;
    };

} // namespace jFramework

#endif