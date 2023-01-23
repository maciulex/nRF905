#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "../nRF905/nRF905_utils.cpp"
#include "../nRF905/nRF905.cpp"

const uint8_t LED_PIN = 25;
const uint8_t INPUT_BUTTON_ONE   = 18;
const uint8_t INPUT_BUTTON_TWO   = 19;
const uint8_t INPUT_BUTTON_THREE = 20;

const uint8_t ALLWAYS_HIGHT = 16;

void blink_led(uint8_t time) {
    sleep_ms(time);
    gpio_put(LED_PIN, 1);
    sleep_ms(time);
    gpio_put(LED_PIN, 0);
    sleep_ms(time);
}

void initializationWait(uint8_t input) {
    while (!gpio_get(input));
    blink_led(200);
}

int main() {
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(INPUT_BUTTON_ONE);
    gpio_set_dir(INPUT_BUTTON_ONE, GPIO_IN);

    gpio_init(INPUT_BUTTON_TWO);
    gpio_set_dir(INPUT_BUTTON_TWO, GPIO_IN);

    gpio_init(INPUT_BUTTON_THREE);
    gpio_set_dir(INPUT_BUTTON_THREE, GPIO_IN);

    gpio_init(ALLWAYS_HIGHT);
    gpio_set_dir(ALLWAYS_HIGHT, GPIO_OUT);
    gpio_put(ALLWAYS_HIGHT, 1);

    nRF905::init();
    initializationWait(INPUT_BUTTON_ONE);

    using namespace nRF905;
    
    // uint8_t addressTx[4] = {0b0100'0110, 0b1100'1010, 0b0111'0001, 0b0010'1101};
    // uint8_t addressRx[4] = {0b1001'0011, 0b0010'0101, 0b0101'1110, 0b1100'1010};
    uint8_t payload[10] = {0,1,2,3,4,5,6,7,8,9};
    // setTX_Address(addressTx, 4);
    // setRX_Address(addressRx, 4);
    setTXPayload(payload, 10);

    getAllData();
    printAll();

    while (true) {

        if (gpio_get(INPUT_BUTTON_TWO)) {
            transmit();
        }

        if (gpio_get(INPUT_BUTTON_THREE)) {
            blink_led(250);

        }
    }
}
