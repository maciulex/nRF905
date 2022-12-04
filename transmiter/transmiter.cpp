#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "../nRF905.cpp"

int main() {
    stdio_init_all();
    const uint8_t LED_PIN = 25;
    const uint8_t INPUT_BUTTON = 21;
    const uint8_t ALLWAYS_HIGHT = 20;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(INPUT_BUTTON);
    gpio_set_dir(INPUT_BUTTON, GPIO_IN);

    gpio_init(ALLWAYS_HIGHT);
    gpio_set_dir(ALLWAYS_HIGHT, GPIO_OUT);
    gpio_put(ALLWAYS_HIGHT, 1);
    
    nRF905::init();
    nRF905::readConfig();
        
    nRF905::setRXAddressWidth(RX_ADDRESS_WIDTH_2BYTE);
    nRF905::setTXAddressWidth(TX_ADDRESS_WIDTH_2BYTE);

    nRF905::setRXPayloadWidth(0b0000'0100);
    nRF905::setTXPayloadWidth(0b0000'0100);

    nRF905::setOutputPower(OUTPUT_POWER_POSITIVE_10);
    nRF905::setCrcMode(CRC_MODE_8BIT);
    nRF905::setCrcEnabled(CRC_ENABLED_ON);
    

    uint8_t addressRX[4] ={0b0101'1011, 0b1011'0010, 0b1011'0110, 0b0011'0101};
    uint8_t addressTX[4] ={0b1011'1101, 0b0110'1110, 0b0101'1010, 0b1011'0110};
    nRF905::setRXAddress(&addressRX[0], 4);
    nRF905::setTXAddress(&addressTX[0], 4);

    uint8_t payload[4] = {4,5,6,7};
    nRF905::writeTXPayload(&payload[0], 4);

    nRF905::configSet();
    bool first = true;
    while (true)
    {
        if (first && gpio_get(INPUT_BUTTON)) {
            nRF905::readConfig();
            nRF905::printLocalConfig();
            nRF905::readTXAddress();
            nRF905::printTXAddress();
            nRF905::readTXPayload();
            nRF905::printTXPayload();
            first = false;
        }
        /* code */
        if (gpio_get(INPUT_BUTTON)) {
            printf("transmiter \n");
            nRF905::transmit();
            // gpio_put(LED_PIN, 1);
            // sleep_ms(250);
            // gpio_put(LED_PIN, 0);
            // sleep_ms(250);
        }
        continue;
        printf("done\n");
        nRF905::readConfig();
        sleep_ms(1000);
    }
    


}
