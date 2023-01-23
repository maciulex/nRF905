#ifndef NRF905_CONFIG_SETTERS
#define NRF905_CONFIG_SETTERS
#include "nRF905_defines.cpp"
#include "nRF905.cpp"

#include <stdio.h>

namespace nRF905 {
    void getAllData();
    void commandStart();
    void commandEnd();
    void getConfig();
    void setConfig();

    void getTX_Address();
    void setTX_Address(uint8_t *address, uint8_t len);
    void getRX_Address();
    void setRX_Address(uint8_t *address, uint8_t len);
    void setTXPayload(uint8_t *payload, uint8_t size);
    void getTxPayload();
    void getRxPayload();


    void getAllData() {
        getConfig();
        getTX_Address();
        getTxPayload();
        getRxPayload();
    }

    void getConfig() {
        CONFIG[0] = COMMAND_R_CONFIG;
        commandStart();
        spi_write_read_blocking(SPI_INTERFACE, &CONFIG[0], &CONFIG[0], 11);
        commandEnd();
        for (int i = 6; i < 10; i++) ADDRESS_RX[i-5] = CONFIG[i];
    }

    void setConfig() {
        CONFIG[0] = COMMAND_W_CONFIG;
        commandStart();
        spi_write_read_blocking(SPI_INTERFACE, &CONFIG[0], &CONFIG[0], 11);
        commandEnd();
    }

    void getTX_Address() {
        ADDRESS_TX[0] = COMMAND_R_TX_ADDRESS;
        commandStart();
        spi_write_read_blocking(SPI_INTERFACE, &ADDRESS_TX[0], &ADDRESS_TX[0], 5);
        commandEnd();
    }

    void setTX_Address(uint8_t *address, uint8_t len) {
        for (int i = 1; i <= len; i++) ADDRESS_TX[i] = address[i-1];
        ADDRESS_TX[0] = COMMAND_W_TX_ADDRESS;
        commandStart();
        spi_write_read_blocking(SPI_INTERFACE, &ADDRESS_TX[0], &ADDRESS_TX[0], 5);
        commandEnd();
    }

    void getRX_Address() {
        getConfig();
    }

    void setRX_Address(uint8_t *address, uint8_t len) {
        getConfig();
        for (int i = 1; i <= ((len > 4) ? 4 : len); i++) {
            ADDRESS_RX[i] = address[i-1];
            CONFIG[i+5] = ADDRESS_RX[i];
        }
        setConfig();
    }

    void setTXPayload(uint8_t *payload, uint8_t size) {
        for (int i = 1; i <= ((size > 32) ? 32 : size+1); i++) TX_PAYLOAD[i] = payload[i-1];
        TX_PAYLOAD[0] = COMMAND_W_TX_PAYLOAD;

        commandStart();
        spi_write_read_blocking(SPI_INTERFACE, &TX_PAYLOAD[0], &TX_PAYLOAD[0], 33);
        commandEnd();
    }

    void getTxPayload() {
        TX_PAYLOAD[0] = COMMAND_R_TX_PAYLOAD;
        commandStart();
        spi_write_read_blocking(SPI_INTERFACE, &TX_PAYLOAD[0], &TX_PAYLOAD[0], 33);
        commandEnd();
    }

    void getRxPayload() {
        RX_PAYLOAD[0] = COMMAND_R_RX_PAYLOAD;
        commandStart();
        spi_write_read_blocking(SPI_INTERFACE, &RX_PAYLOAD[0], &RX_PAYLOAD[0], 33);
        commandEnd();
    }
}

#endif