#ifndef NRF905
#define NRF905

#include "pico/stdlib.h"
#include "hardware/spi.h"

#define SPI_INTERFACE spi0
#define SPI_MOSI 3
#define SPI_MISO 0
#define SPI_CLK  2
#define SPI_CS  1

#define DATA_READY_PIN 8
#define ADRESS_MATCH_PIN 7
#define CARRIER_DETECT_PIN 6
#define TX_RX_MODE_PIN 4
#define STANDBY_PIN 5
#define POWER_UP_PIN 9

#define COMMAND_W_CONFIG     0b0000'0000
#define COMMAND_R_CONFIG     0b0001'0000
#define COMMAND_W_TX_PAYLOAD 0b0010'0000
#define COMMAND_R_TX_PAYLOAD 0b0010'0001
#define COMMAND_W_TX_ADDRESS 0b0010'0010
#define COMMAND_R_TX_ADDRESS 0b0010'0011
#define COMMAND_R_RX_PAYLOAD 0b0010'0100

//BYTE 0
//chanel frequency + first bit of BYTE 1 (total bit width 9)

//BYTE 1
#define OPERATIONAL_FREAQUENCY_BIT_STYLE  0b0000'0011 
#define OPERATIONAL_FREAQUENCY_430MHZ     0b0000'0000 //default
#define OPERATIONAL_FREAQUENCY_868_915MHZ 0b0000'0010 

#define OUTPUT_POWER_NEGATIVE_BIT_STYLE 0b0000'1100 
#define OUTPUT_POWER_NEGATIVE_10        0b0000'0000 //default
#define OUTPUT_POWER_NEGATIVE_2         0b0000'0100 
#define OUTPUT_POWER_POSITIVE_6         0b0000'1000
#define OUTPUT_POWER_POSITIVE_10        0b0000'1100

#define REDUCED_RX_SENSIVITY_BIT_STYLE  0b0001'0000  
#define REDUCED_RX_SENSIVITY_ON         0b0001'0000  
#define REDUCED_RX_SENSIVITY_OFF        0b0000'0000 //default

#define AUTO_RETAIN_BIT_STYLE           0b0010'0000  
#define AUTO_RETAIN_ON                  0b0010'0000  
#define AUTO_RETAIN_OFF                 0b0000'0000  //default

//BYTE 2
#define RX_ADDRESS_WIDTH_BIT_STYLE 0b0000'0111
#define RX_ADDRESS_WIDTH_1BYTE     0b0000'0001
#define RX_ADDRESS_WIDTH_2BYTE     0b0000'0010 
#define RX_ADDRESS_WIDTH_3BYTE     0b0000'0011 
#define RX_ADDRESS_WIDTH_4BYTE     0b0000'0100 //deafult

#define TX_ADDRESS_WIDTH_BIT_STYLE 0b0111'0000
#define TX_ADDRESS_WIDTH_1BYTE     0b0001'0000
#define TX_ADDRESS_WIDTH_1BYTE     0b0001'0000
#define TX_ADDRESS_WIDTH_2BYTE     0b0010'0000 
#define TX_ADDRESS_WIDTH_3BYTE     0b0011'0000 
#define TX_ADDRESS_WIDTH_4BYTE     0b0100'0000 //deafult

//BYTE 3 
//size of rx payload 0-5 max 32 byte min 1 byte
//BYTE 4 
//size of tx payload 0-5 max 32 byte min 1 byte
//BYTE 5-8 RX ADRESSS
//BYTE 9

#define OUTPUT_CLOCK_FREQUENCY_BIT_STYLE 0b0000'0011
#define OUTPUT_CLOCK_FREQUENCY_4MHZ      0b0000'0000
#define OUTPUT_CLOCK_FREQUENCY_2MHZ      0b0000'0001
#define OUTPUT_CLOCK_FREQUENCY_1MHZ      0b0000'0010
#define OUTPUT_CLOCK_FREQUENCY_500KHZ    0b0000'0011 //deafult

#define OUTPUT_CLOCK_ENABLE_BIT_STYLE 0b0000'0100
#define OUTPUT_CLOCK_ENABLE_OFF       0b0000'0000
#define OUTPUT_CLOCK_ENABLE_ON        0b0000'0100 //deafult

#define CRYSTAL_CLOCK_FREQUENCY_BIT_STYLE 0b0011'1000
#define CRYSTAL_CLOCK_FREQUENCY_4MHZ      0b0000'0000
#define CRYSTAL_CLOCK_FREQUENCY_8MHZ      0b0000'1000 
#define CRYSTAL_CLOCK_FREQUENCY_12MHZ     0b0001'0000 
#define CRYSTAL_CLOCK_FREQUENCY_16MHZ     0b0001'1000 
#define CRYSTAL_CLOCK_FREQUENCY_20MHZ     0b0010'0000 //deafult 

#define CRC_ENABLED_BIT_STYLE 0b0100'0000
#define CRC_ENABLED_ON        0b0100'0000 //deafult
#define CRC_ENABLED_OFF       0b0000'0000 

#define CRC_MODE_BIT_STYLE 0b1000'0000
#define CRC_MODE_8BIT      0b0000'0000 
#define CRC_MODE_16BIT     0b1000'0000  //deafult


#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 


namespace nRF905 {
    bool powerUpMode(bool state);
    bool TX_mode(bool activate = true);
    bool RX_mode(bool activate = true);
    bool standbyMode(bool state = true);
    bool powerUpMode(bool state = true);
    bool configSet();
    void printLocalConfig();
    void initPins();
    void init();
    uint8_t clearBits(uint8_t input, uint8_t configBitStyle);
    bool getBit(uint8_t byte, uint8_t index);

    void setOperationalFeaquency(uint8_t value);
    void setOutputPower(uint8_t value);
    void setRXSensivity(uint8_t value);
    void setAutoretain(uint8_t value);
    void setRXAddressWidth(uint8_t value);
    void setTXAddressWidth(uint8_t value);
    void setRXPayloadWidth(uint8_t value);
    void setTXPayloadWidth(uint8_t value);
    void setRXAddress(uint8_t values, uint8_t size);
    void setOutputClockFrequency(uint8_t values);
    void setEnabledOutputClockFrequency(uint8_t values);
    void setCrystalClockFrequency(uint8_t values);
    void setCrcEnabled(uint8_t values);
    void setCrcMode(uint8_t values);

    void writeTXPayload(uint8_t *data, uint8_t size);
    void clearTxPayload();
    void readTXPayload();
    void printTXPayload();


    uint8_t TX_PAYLOAD[32];
    uint8_t RX_PAYLOAD[32];
    uint8_t TX_ADDRESS[4];
    uint8_t RX_ADDRESS[4];
    uint8_t CONFIG[11];

    bool readyToOperate = false;
    bool powerUp = false;
    bool standBy = false;
    bool RXmode  = false;

    bool TX_mode(bool activate) {
        if (activate) {
            if (RXmode) return !RX_mode(false);
            return true;
        }
        if (RXmode) return false;
        return !RX_mode(true);
    } 

    bool RX_mode(bool activate) {
        if (activate == RXmode) return RXmode;
        
        RXmode = activate;
        if (!readyToOperate) standbyMode(true);
        if (!RXmode) {
            gpio_put(TX_RX_MODE_PIN, 1);
            sleep_us(1);
            return false;
        } 

        gpio_put(TX_RX_MODE_PIN, 0);
        sleep_us(1);
        return true;
    }

    bool standbyMode(bool state) {
        if (state == standBy) return standBy;
        
        standBy = state;
        if (!standBy) {
            gpio_put(STANDBY_PIN, 0);
            sleep_us(1);
            readyToOperate = false;
            return false;
        } 

        gpio_put(STANDBY_PIN, 1);
        if (!powerUp) {
            powerUpMode(true);
            sleep_ms(3);
            readyToOperate = true;
        }
        return true;
    }

    bool powerUpMode(bool state) {
        if (state == powerUp) return powerUp;

        powerUp = state;
        if (!powerUp) {
            gpio_put(POWER_UP_PIN, 0);
            standbyMode(false);
            return false;
        } 
        gpio_put(POWER_UP_PIN, 1);
        return true;
    }

    void startCommand() {
        if (powerUp && !standBy) standbyMode(true);
        gpio_put(SPI_CS, 0);
    }

    void endCommand() {
        gpio_put(SPI_CS, 1);
    }

    void printLocalConfig() {
        printf("Config: ");
        for (int i = 0; i < 11; i++) printf("\n\t" BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(CONFIG[i]));
        printf("\n");
    }

    bool readConfig() {
        uint8_t command[11] = {COMMAND_R_CONFIG,255,255,255,255,255,255,255,255,255,255};
        startCommand();

        spi_write_read_blocking(SPI_INTERFACE, command, CONFIG, 11);

        endCommand();
        return true;
    }

    bool configSet() {
        CONFIG[0] = COMMAND_W_CONFIG;
        startCommand();

        spi_write_blocking(SPI_INTERFACE, CONFIG, 11);

        endCommand();
        return true;
    }
    
    void initPins() {
        spi_init(SPI_INTERFACE, 500*1000);
        gpio_set_function(SPI_MOSI,  GPIO_FUNC_SPI);
        gpio_set_function(SPI_MISO,  GPIO_FUNC_SPI);
        gpio_set_function(SPI_CLK,   GPIO_FUNC_SPI);

        gpio_init(SPI_CS);
        gpio_set_dir(SPI_CS, GPIO_OUT);
        gpio_put(SPI_CS, 1);
        gpio_init(DATA_READY_PIN);
        gpio_set_dir(DATA_READY_PIN, GPIO_IN);

        gpio_init(ADRESS_MATCH_PIN);
        gpio_set_dir(ADRESS_MATCH_PIN, GPIO_IN);

        gpio_init(CARRIER_DETECT_PIN);
        gpio_set_dir(CARRIER_DETECT_PIN, GPIO_IN);

        gpio_init(TX_RX_MODE_PIN);
        gpio_set_dir(TX_RX_MODE_PIN, GPIO_OUT);

        gpio_init(STANDBY_PIN);
        gpio_set_dir(STANDBY_PIN, GPIO_OUT);
    
        gpio_init(POWER_UP_PIN);
        gpio_set_dir(POWER_UP_PIN, GPIO_OUT);
    }

    void init() {
        initPins();
        standbyMode();
    }
    
    void setOperationalFeaquency(uint8_t value) {
        CONFIG[2] = clearBits(CONFIG[2], OPERATIONAL_FREAQUENCY_BIT_STYLE);
        CONFIG[2] += value;
    }

    void setOutputPower(uint8_t value) {
        CONFIG[2] = clearBits(CONFIG[2], OUTPUT_POWER_NEGATIVE_BIT_STYLE);
        CONFIG[2] += value;
    }

    void setRXSensivity(uint8_t value) {
        CONFIG[2] = clearBits(CONFIG[2], REDUCED_RX_SENSIVITY_BIT_STYLE);
        CONFIG[2] += value;
    }

    void setAutoretain(uint8_t value) {
        CONFIG[2] = clearBits(CONFIG[2], AUTO_RETAIN_BIT_STYLE);
        CONFIG[2] += value;
    }

    void setRXAddressWidth(uint8_t value) {
        CONFIG[3] = clearBits(CONFIG[3], RX_ADDRESS_WIDTH_BIT_STYLE);
        CONFIG[3] += value;
    }

    void setTXAddressWidth(uint8_t value) {
        CONFIG[3] = clearBits(CONFIG[3], TX_ADDRESS_WIDTH_BIT_STYLE);
        CONFIG[3] += value;
    }

    void setRXPayloadWidth(uint8_t value) {
        CONFIG[4] = clearBits(CONFIG[4], 0b0001'1111);
        CONFIG[4] += value;
    }

    void setTXPayloadWidth(uint8_t value) {
        CONFIG[5] = clearBits(CONFIG[5], 0b0001'1111);
        CONFIG[5] += value;
    }

    void setRXAddress(uint8_t *values, uint8_t size) {
        for (int i = 0; i < size; i++) {
            CONFIG[6+i] = values[i];
            TX_ADDRESS[i] = values[i];
        }
    }

    void writeTXPayload(uint8_t *data, uint8_t size) {
        for (int i = 0; i < size; i++) {
            TX_PAYLOAD[i] = data[i];
        }
        uint8_t command[2] = {COMMAND_W_TX_PAYLOAD, *TX_PAYLOAD};
        startCommand();

        spi_write_blocking(SPI_INTERFACE, command, 33);

        endCommand();
    }

    void clearTxPayload() {
        for (int i = 0; i < 32; i++) {
            TX_PAYLOAD[i] = 0;
        }
        writeTxPayload();
    }
    
    void readTXPayload() {

    }

    void printTXPayload() {

    }

    void setOutputClockFrequency(uint8_t values) {
        CONFIG[10] = clearBits(CONFIG[10], OUTPUT_CLOCK_FREQUENCY_BIT_STYLE);
        CONFIG[10] += values;
    }

    void setEnabledOutputClockFrequency(uint8_t values) {
        CONFIG[10] = clearBits(CONFIG[10], OUTPUT_CLOCK_ENABLE_BIT_STYLE);
        CONFIG[10] += values;
    }

    void setCrystalClockFrequency(uint8_t values) {
        CONFIG[10] = clearBits(CONFIG[10], CRYSTAL_CLOCK_FREQUENCY_BIT_STYLE);
        CONFIG[10] += values;
    }

    void setCrcEnabled(uint8_t values) {
        CONFIG[10] = clearBits(CONFIG[10], CRC_ENABLED_BIT_STYLE);
        CONFIG[10] += values;
    }

    void setCrcMode(uint8_t values) {
        CONFIG[10] = clearBits(CONFIG[10], CRC_MODE_BIT_STYLE);
        CONFIG[10] += values;
    }

    uint8_t clearBits(uint8_t input, uint8_t configBitStyle) {
        for (int i = 0; i < 8; i++) {
            if (!getBit(configBitStyle, i)) continue;
            input &= ~(1 << i);
        }   
        return input;
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
}

#endif