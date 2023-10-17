#ifndef J_I2C_PORT_H
#define J_I2C_PORT_H

#include "jObject.hpp"

namespace jFramework
{
    enum i2cPortNumber
    {
        i2c0 = 0,
        i2c1 = 1
    };

    class i2cPort : public jObject
    {
    public:
        i2cPort(const char *name, i2cPortNumber portNumber, uint8_t SCL_PIN, uint8_t SDA_PIN);

        // writing
        j_err w(uint8_t device, uint8_t *data, uint16_t len);
        j_err w8(uint8_t device, uint8_t data);
        j_err w8r8(uint8_t device, uint8_t address, uint8_t data);
        j_err w8r16(uint8_t device, uint16_t address, uint8_t data);
        j_err w8r32(uint8_t device, uint32_t address, uint8_t data);
        j_err w16r8(uint8_t device, uint8_t address, uint16_t data);
        j_err w16r16(uint8_t device, uint16_t address, uint16_t data);
        j_err w16r32(uint8_t device, uint32_t address, uint16_t data);
        j_err w32r8(uint8_t device, uint8_t address, uint32_t data);
        j_err w32r16(uint8_t device, uint16_t address, uint32_t data);
        j_err w32r32(uint8_t device, uint32_t address, uint32_t data);

        // reading
        j_err r(uint8_t device, uint8_t *data, uint16_t len);
        j_err r8(uint8_t device, uint8_t &data);
        j_err r8r8(uint8_t device, uint8_t address, uint8_t &data);
        j_err r8r16(uint8_t device, uint16_t address, uint8_t &data);
        j_err r8r32(uint8_t device, uint32_t address, uint8_t &data);
        j_err r16r8(uint8_t device, uint8_t address, uint16_t &data);
        j_err r16r16(uint8_t device, uint16_t address, uint16_t &data);
        j_err r16r32(uint8_t device, uint32_t address, uint16_t &data);
        j_err r32r8(uint8_t device, uint8_t address, uint32_t &data);
        j_err r32r16(uint8_t device, uint16_t address, uint32_t &data);
        j_err r32r32(uint8_t device, uint32_t address, uint32_t &data);

        j_err present(uint8_t device, bool &isPresent);

    protected:
    private:
        i2cPortNumber _port;
        uint8_t buf[8];
    };

} // namespace jFramework

#endif