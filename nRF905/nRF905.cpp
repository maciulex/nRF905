#ifndef NRF905
#define NRF905

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "nRF905_defines.cpp"
#include "nRF905_ConfigRegisters.cpp"

extern const uint8_t INPUT_BUTTON_THREE;

namespace nRF905 {
    //tx this device, rx device to send
    uint8_t CONFIG[11];
    uint8_t ADDRESS_TX[5]; //one more [0] is for command, [1-4] is actuall adress
    uint8_t ADDRESS_RX[5]; // as above but [0] is unused 
    uint8_t RX_PAYLOAD[33];
    uint8_t TX_PAYLOAD[33];

    bool powerUp_PinState = false; // false for powerdown, true for power up
    bool standBy_PinState = true; // true for standby and programing, false for tx/rx, this is invertion of actual signal send by gpio
    bool TRX_CE_PinState  = false; // false for reciving, true for transmiting

    void transmit();
    void recive();

    bool standbyMode(bool state = true, bool speedMode = false);
    bool powerMode  (bool state = true);
    bool setPinForTransmision(bool transmit = true);
    bool setPinToRecive(bool recive = true);
    void commandStart();
    void commandEnd();
    void terminate();
    void init();

    uint8_t clearBits(uint8_t number, uint8_t pattern);
    bool getBit(uint8_t byte, uint8_t index);

    // //ConfigRegisters
    // void getAllData();

    // void getConfig();
    // void setConfig();
    // void getTX_Address();
    // void setTX_Address(uint8_t *address, uint8_t len);
    // void getRX_Address();
    // void setRX_Address(uint8_t *address, uint8_t len);

    // //utils
    // void printAll();
    // void clearToZeroConfig();
    // void printConfig();
    // void printPinStates();
    // void printTxAddress();
    // void printRxAddress();
    // void printTxPayload();
    // void printRxPayload();

    void transmit() {
            setPinForTransmision();
            standbyMode(false);
            while (!gpio_get(DATA_READY_PIN)) {}

            printf("Data send");
            
            setPinToRecive();
            standbyMode(true);
            sleep_ms(1000);
    }

    void recive() {
            setPinToRecive();
            standbyMode(false);
            
            while (!gpio_get(DATA_READY_PIN)) {
                if (gpio_get(ADRESS_MATCH_PIN)) printf("Address match\n");
            }
            printf("Data recived");
            getRxPayload();
            printRxPayload();
            setPinForTransmision();
            standbyMode(true);
            
            sleep_ms(1000);            

    }

    bool setPinForTransmision(bool transmit) {
        if (transmit) {
            gpio_put(TX_RX_MODE_PIN, 1);
            TRX_CE_PinState = true;
            sleep_us(550);
            return true;
        }
        return false;
    }
    bool setPinToRecive(bool recive) {
        if (recive) {
            TRX_CE_PinState = false;
            gpio_put(TX_RX_MODE_PIN, 0);
            sleep_us(550);
            return true;
        }
        return false;
    }

    bool standbyMode(bool state,  bool speedMode) {
        standBy_PinState = state;

        if (standBy_PinState) {
            gpio_put(STANDBY_PIN, 0);
            sleep_us(650);
            return true; 
        }

        gpio_put(STANDBY_PIN, 1);
        sleep_us(650);
        return false;
    }

    bool powerMode(bool state) {
        powerUp_PinState = state;

        if (powerUp_PinState) {
            gpio_put(POWER_UP_PIN, 1);
            sleep_ms(3);
            return true;
        }
        gpio_put(POWER_UP_PIN, 0);
        return false;
    }

    void commandStart() {
        gpio_put(SPI_CS, 0);
    }

    void commandEnd() {
        gpio_put(SPI_CS, 1);
    }

    void terminate() {
        powerMode(false);
        standbyMode(true);
        setPinToRecive();
    }

    uint8_t clearBits(uint8_t number, uint8_t pattern) {
        for (int i = 0; i < 8; i++) {
            if (!getBit(pattern, i)) continue;
            number &= ~(1 << i);
        }
        return number;
    }

    bool getBit(uint8_t byte, uint8_t index) {
        switch (index) {
            case 0:
                return (byte & 0x01 ? true : false);
            case 1:
                return (byte & 0x02 ? true : false);
            case 2:
                return (byte & 0x04 ? true : false);
            case 3:
                return (byte & 0x08 ? true : false);
            case 4:
                return (byte & 0x10 ? true : false);
            case 5:
                return (byte & 0x20 ? true : false);
            case 6:
                return (byte & 0x40 ? true : false);
            case 7:
                return (byte & 0x80 ? true : false);
        }
        return false;
    }

    void initPins() {
        //SPI
        spi_init(SPI_INTERFACE, 10*1000*1000);

        gpio_set_function(SPI_MOSI,  GPIO_FUNC_SPI);
        gpio_set_function(SPI_MISO,  GPIO_FUNC_SPI);
        gpio_set_function(SPI_CLK,   GPIO_FUNC_SPI);

        //OUT

        gpio_init(SPI_CS);
        gpio_set_dir(SPI_CS, GPIO_OUT);
        gpio_put(SPI_CS, 1);

        gpio_init(TX_RX_MODE_PIN);
        gpio_set_dir(TX_RX_MODE_PIN, GPIO_OUT);
        gpio_put(TX_RX_MODE_PIN, 0);

        gpio_init(STANDBY_PIN);
        gpio_set_dir(STANDBY_PIN, GPIO_OUT);
        gpio_put(STANDBY_PIN, 0);
    
        gpio_init(POWER_UP_PIN);
        gpio_set_dir(POWER_UP_PIN, GPIO_OUT);
        gpio_put(POWER_UP_PIN, 0);
        
        //IN

        gpio_init(DATA_READY_PIN);
        gpio_set_dir(DATA_READY_PIN, GPIO_IN);

        gpio_init(ADRESS_MATCH_PIN);
        gpio_set_dir(ADRESS_MATCH_PIN, GPIO_IN);

        gpio_init(CARRIER_DETECT_PIN);
        gpio_set_dir(CARRIER_DETECT_PIN, GPIO_IN);
    }

    void init() {
        initPins();



        standbyMode(true);
        powerMode(true);

    }

}
#include "nRF905_ConfigRegisters.cpp"

#endif