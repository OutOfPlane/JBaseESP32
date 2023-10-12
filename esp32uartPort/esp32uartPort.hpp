#ifndef J_ESP32_UART_PORT_H
#define J_ESP32_UART_PORT_H

#include "uartPort.hpp"

namespace jFramework
{
    class esp32uartPort : public uartPort
    {
    public:
        esp32uartPort(const char *name, uartPortNumber portNumber, uint32_t baud, uint8_t TX_PIN, uint8_t RX_PIN);

        // writing
        j_err w(uint8_t *data, uint16_t len);
        // reading
        j_err r(uint8_t *data, uint16_t &len, uint32_t timeout_ms);

        //status
        j_err present(bool &isPresent);

    protected:
    private:
    };

} // namespace jFramework

#endif