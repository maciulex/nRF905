#ifndef NRF905_UTILS
#define NRF905_UTILS
#include "nRF905_defines.cpp"

namespace nRF905 {
    extern uint8_t CONFIG[11];
    extern uint8_t ADDRESS_TX[5];
    extern uint8_t ADDRESS_RX[5];
    extern uint8_t RX_PAYLOAD[33];
    extern uint8_t TX_PAYLOAD[33];

    extern bool powerUp_PinState;
    extern bool standBy_PinState;
    extern bool TRX_CE_PinState;

    void printAll();
    void clearToZeroConfig();
    void printConfig();
    void printPinStates();
    void printTxAddress();
    void printRxAddress();
    void printTxPayload();
    void printRxPayload();
    
    void clearToZeroConfig() {
        const uint8_t clearValue = 0;
        for (int i = 0; i < 11; i++) CONFIG[i]     = clearValue; 
        for (int i = 0; i < 4; i++)  ADDRESS_TX[i] = clearValue; 
        for (int i = 0; i < 4; i++)  ADDRESS_RX[i] = clearValue; 
        for (int i = 0; i < 33; i++) RX_PAYLOAD[i] = clearValue; 
        for (int i = 0; i < 33; i++) TX_PAYLOAD[i] = clearValue; 
    }

    void printAll() {
        printConfig();
        printPinStates();
        printTxAddress();
        printRxAddress();
        printTxPayload();
        printRxPayload();
    }
    void printPinStates() {
        printf("Pin States");
        printf("\n\tPowerUP: %i", (powerUp_PinState) ? 1 : 0);
        printf("\n\tStandBY: %i", (standBy_PinState) ? 1 : 0);
        printf("\n\tTXRXPIN: %i", (TRX_CE_PinState) ? 1 : 0);
        printf("\n\tData Ready: %i", (gpio_get(DATA_READY_PIN)) ? 1 : 0);
        printf("\n\tAdress match: %i", (gpio_get(ADRESS_MATCH_PIN)) ? 1 : 0);
        printf("\n\tCarrier Detect: %i\n\n", (gpio_get(CARRIER_DETECT_PIN)) ? 1 : 0);
        
    }

    void printConfig() {
        printf("Config\n");
        for (int i = 0; i < 11; i++) {
            printf("\t%i: ", i);
            printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(CONFIG[i]));
            printf("\n");
        }
        printf("\n");
    }

    void printTxAddress() {
        printf("Tx Address: \n");
        for (int i = 0; i < 5; i++) {
            printf("\t%i: ", i);
            printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(ADDRESS_TX[i]));
            printf("\n");
        }
        printf("\n");
    }

    void printRxAddress() {
        printf("Rx Address\n");
        for (int i = 0; i < 5; i++) {
            printf("\t%i: ", i);
            printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(ADDRESS_RX[i]));
            printf("\n");
        }
        printf("\n");
    }

    void printTxPayload() {
        printf("Tx Payload: \n");
        for (int i = 0; i < 33; i++) {
            printf("\t%i: ", i);
            printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(TX_PAYLOAD[i]));
            printf("\n");
        }
        printf("\n");
    }

    void printRxPayload() {
        printf("Rx Payload: \n");
        for (int i = 0; i < 33; i++) {
            printf("\t%i: ", i);
            printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(RX_PAYLOAD[i]));
            printf("\n");
        }
        printf("\n");
    }
}

#endif