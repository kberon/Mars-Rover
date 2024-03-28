#ifndef BME280_H
#define BME280_H

#include <stdio.h>
#include <string.h>
#include <cstdint>
#include <wiringPi.h>

using namespace std;

class BME280 {
    public:
        const uint8_t ADDRESS = 0x77; //might change to 76 if jumper from SDO to GND or soldering ADDR jumper closed
        
        const uint8_t RESET = 0xE0;
        const uint8_t STATUS = 0xF3;


        const uint8_t CTRL_HUM = 0xF2; //write before ctrl meas
        const uint8_t CTRL_MEAS = 0xF4;

        const uint8_t TEMP_LSB = 0xFB;
        const uint8_t TEMP_MSB = 0xFC;

        const uint8_t PRESS_LSB = 0xF7;
        const uint8_t PRESS_MSB = 0xF6;

        const uint8_t HUM_LSB = 0xFD;
        const uint8_t HUM_MSB = 0xFE;

        int fd;

        BME280(void);
        bool init(void);
        void set_reg(uint8_t reg, uint8_t val);
        uint8_t read_reg(uint8_t reg);
        uint16_t get_temp(void);
        uint16_t* get_hum(void);
        uint16_t* get_press(void);


};

#endif
