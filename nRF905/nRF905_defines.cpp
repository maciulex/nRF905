#ifndef NRF905_DEFINES
#define NRF905_DEFINES

#define SPI_INTERFACE spi0
#define SPI_MISO 0
#define SPI_CS  1
#define SPI_CLK  2
#define SPI_MOSI 3

#define ADRESS_MATCH_PIN 4
#define STANDBY_PIN 5
#define TX_RX_MODE_PIN 6
#define POWER_UP_PIN 7
#define CARRIER_DETECT_PIN 8
#define DATA_READY_PIN 9

#define COMMAND_W_CONFIG     0b0000'0000
#define COMMAND_R_CONFIG     0b0001'0000
#define COMMAND_W_TX_PAYLOAD 0b0010'0000
#define COMMAND_R_TX_PAYLOAD 0b0010'0001
#define COMMAND_W_TX_ADDRESS 0b0010'0010
#define COMMAND_R_TX_ADDRESS 0b0010'0011
#define COMMAND_R_RX_PAYLOAD 0b0010'0100

//BYTE 0
//chanel frequency + first bit of BYTE 1 (total bit width 9)-

//BYTE 1
#define OPERATIONAL_FREAQUENCY_BIT_STYLE  0b0000'0010
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

#endif