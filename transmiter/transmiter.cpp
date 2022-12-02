#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "../nRF905.cpp"

int main() {
    stdio_init_all();
    nRF905::init();
    nRF905::readConfig();
        
    nRF905::setRXAddressWidth(RX_ADDRESS_WIDTH_2BYTE);
    nRF905::setTXAddressWidth(TX_ADDRESS_WIDTH_2BYTE);
    nRF905::setOutputPower(OUTPUT_POWER_NEGATIVE_2);
    
    uint8_t address[4] ={0b0101'1011, 0b1011'0010, 0b1011'0110, 0b0011'0101};
    nRF905::setRXAddress(&address[0], 4);
    
    while (true)
    {
        /* code */
        nRF905::printLocalConfig();
        sleep_ms(10000);

        continue;
        printf("done\n");
        nRF905::readConfig();
        sleep_ms(1000);
    }
    


}
