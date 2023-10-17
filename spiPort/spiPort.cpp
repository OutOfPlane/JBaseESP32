#include "spiPort.hpp"
#include <cstring>

using namespace jFramework;

spiPort::spiPort(const char *name, spiPortNumber portNumber, uint8_t MISO_PIN, uint8_t MOSI_PIN, uint8_t SCK_PIN)
    : jObject(name), _lastSelected(nullptr)
{
    _port = portNumber;

    spi_bus_config_t buscfg;
    memset(&buscfg, 0, sizeof(buscfg));

    buscfg.mosi_io_num = MOSI_PIN;
    buscfg.miso_io_num = MISO_PIN;
    buscfg.sclk_io_num = SCK_PIN;
    buscfg.quadwp_io_num = -1;
    buscfg.quadhd_io_num = -1;
    buscfg.max_transfer_sz = 0;

    // Initialize the SPI bus
    spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
}

j_err jFramework::spiPort::makeDevice(ioPin *SS_Pin, uint32_t clkSpeedHz, spiInterface **deviceInterface)
{
    *deviceInterface = nullptr;
    spi_device_interface_config_t devcfg;
    memset(&devcfg, 0, sizeof(devcfg));

    devcfg.mode = 0;                    // SPI mode 0
    devcfg.clock_speed_hz = clkSpeedHz; // Clock out at 10 MHz
    devcfg.spics_io_num = -1;           // CS pin
    devcfg.queue_size = 2;              // We want to be able to queue 7 transactions at a time
    devcfg.pre_cb = nullptr;            // Specify pre-transfer callback to handle D/C line

    *deviceInterface = new spiInterface(&devcfg, this);
    (*deviceInterface)->_ss_pin = SS_Pin;

    return j_err_translate(spi_bus_add_device(SPI2_HOST, &devcfg, &(*deviceInterface)->_spi));
}

j_err jFramework::spiPort::select(ioPin *SS_Pin)
{
    if(_lastSelected)
    {
        _lastSelected->set(0);
    }
    _lastSelected = SS_Pin;
    return SS_Pin->set(1);    
}

j_err jFramework::spiPort::deselect()
{
    if(_lastSelected)
    {
        _lastSelected->set(0);
    }
    _lastSelected = nullptr;
    return J_OK;
}

spiInterface::spiInterface(spi_device_interface_config_t *interfaceCfg, spiPort *port)
    : _port(port)
{
    memcpy(&_interfaceCfg, interfaceCfg, sizeof(_interfaceCfg));
}

j_err jFramework::spiInterface::select()
{
    return _port->select(_ss_pin);
}

j_err jFramework::spiInterface::deselect()
{
    return _port->deselect();
}

j_err jFramework::spiInterface::w(uint8_t *data, uint16_t len)
{
    return rw(nullptr, data, len);
}

j_err jFramework::spiInterface::r(uint8_t *data, uint16_t len)
{
    return rw(data, nullptr, len);
}

j_err jFramework::spiInterface::rw(uint8_t *txdata, uint8_t *rxdata, uint16_t len)
{
    esp_err_t ret;
    spi_transaction_t t;
    if (len == 0)
    {
        return J_OK; // no need to send anything
    }
    memset(&t, 0, sizeof(t)); // Zero out the transaction
    if (rxdata)
    {
        t.rxlength = len * 8; // Len is in bytes, transaction length is in bits.
        t.rx_buffer = rxdata; // Data
    }

    if (txdata)
    {
        t.length = len * 8;   // Len is in bytes, transaction length is in bits.
        t.tx_buffer = txdata; // Data
    }

    ret = spi_device_polling_transmit(_spi, &t); // Transmit!
    return j_err_translate(ret);
}
