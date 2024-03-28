#ifndef ISM330DHCX_H
#define ISM330DHCX_H

#include <stdio.h>
#include <string.h>
#include <cstdint>
#include <wiringPi.h>

using namespace std;

class ISM330DHCX {
    public:
        const uint8_t ADDRESS = 0x6B; //might need to change to 60 or 6A

        const uint8_t CTRL1_XL = 0x10;
        const uint8_t CTRL2_G = 0x11;

        const uint8_t OUT_TEMP_L = 0x20;
        const uint8_t OUT_TEMP_H = 0x21;
        
        const uint8_t OUTX_L_G = 0x22;
        const uint8_t OUTX_H_G = 0x23;
        const uint8_t OUTY_L_G = 0x24;
        const uint8_t OUTY_H_G = 0x25;
        const uint8_t OUTZ_L_G = 0x26;
        const uint8_t OUTZ_H_G = 0x27;

        const uint8_t OUTX_L_A = 0x28;
        const uint8_t OUTX_H_A = 0x29;
        const uint8_t OUTY_L_A = 0x2A;
        const uint8_t OUTY_H_A = 0x2B;
        const uint8_t OUTZ_L_A = 0x2C;
        const uint8_t OUTZ_H_A = 0x2D;

        int fd;
        
        ISM330DHCX(void);
        bool init(void);
        void set_reg(uint8_t reg, uint8_t val);
        uint8_t read_reg(uint8_t reg);
        uint16_t get_temp(void);
        uint16_t* get_gyro(void);
        uint16_t* get_accel(void);


};

#endif
