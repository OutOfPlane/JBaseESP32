#ifndef J_SPI_PORT_H
#define J_SPI_PORT_H

#include "jObject.hpp"
#include "ioPin.hpp"
#include "driver/spi_master.h"

namespace jFramework
{
    enum spiPortNumber
    {
        spi0 = 0,
        spi1 = 1
    };

    class spiPort;

    class spiInterface
    {
    public:
        j_err select();
        j_err deselect();

        // writing
        j_err w(uint8_t *data, uint16_t len);

        // reading
        j_err r(uint8_t *data, uint16_t len);

        // simultaneous
        j_err rw(uint8_t *txdata, uint8_t *rxdata, uint16_t len);

    private:
        spiInterface(spi_device_interface_config_t *interfaceCfg, spiPort *port);
        spiPort *_port;
        uint8_t buf[8];
        spi_device_interface_config_t _interfaceCfg;
        spi_device_handle_t _spi;
        ioPin *_ss_pin;

        friend class spiPort;
    };

    class spiPort : public jObject
    {
    public:
        spiPort(const char *name, spiPortNumber portNumber, uint8_t MISO_PIN, uint8_t MOSI_PIN, uint8_t SCK_PIN);

        // slave adressing
        j_err makeDevice(ioPin *SS_Pin, uint32_t clkSpeedHz, spiInterface **deviceInterface);

    protected:
    private:
        spiPortNumber _port;

        ioPin *_lastSelected;

        

        j_err select(ioPin *SS_Pin);
        j_err deselect();

        friend class spiInterface;
    };

} // namespace jFramework

#endif