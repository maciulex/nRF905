#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "../nRF905.cpp"

int main() {
    stdio_init_all();
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    nRF905::init();
    nRF905::readConfig();
        
    nRF905::setRXAddressWidth(RX_ADDRESS_WIDTH_4BYTE);
    nRF905::setTXAddressWidth(TX_ADDRESS_WIDTH_4BYTE);

    nRF905::setRXPayloadWidth(0b0000'0100);
    nRF905::setTXPayloadWidth(0b0000'0100);


    nRF905::setOutputPower(OUTPUT_POWER_NEGATIVE_2);

    uint8_t addressTX[4] ={0b0101'1011, 0b1011'0010, 0b1011'0110, 0b0011'0101};
    uint8_t addressRX[4] ={0b1011'1101, 0b0110'1110, 0b0101'1010, 0b1011'0110};
    nRF905::setRXAddress(&addressRX[0], 4);
    nRF905::setTXAddress(&addressTX[0], 4);


    while (true)
    {
        /* code */
        nRF905::recive();
        sleep_ms(1000);
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
        nRF905::readRXPayload();
        nRF905::printRXPayload();
        continue;
        printf("done\n");
        nRF905::readConfig();
        sleep_ms(1000);
    }
    


}
