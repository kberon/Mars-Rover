#include "BME280.h"

BME280::BME280(void) {}

bool BME280::init(void) {
    // Initialize I2C
    //reset
    set_reg(RESET, 0xB6);
    delay(300);

    fd = wiringPiI2CSetup(ADDRESS);

    if(fd == -1) {
        return false;
    }

    //ctrl hum: 16x oversampling
    set_reg(CTRL_HUM, 0x05);
    //ctrl meas: 16x oversampling, normal mode
    set_reg(CTRL_MEAS, 0x27);
    

    
    return true;
}

void BME280::set_reg(uint8_t reg, uint8_t val) {
    uint8_t data[2];
    data[0] = reg;
    data[1] = val;
    wiringPiI2CWriteReg8(fd, reg, val);
}

uint8_t BME280::read_reg(uint8_t reg) {
    return wiringPiI2CReadReg8(fd, reg);
}

uint16_t BME280::get_temp(void) {    
    return read_reg(TEMP_LSB) | (read_reg(TEMP_MSB) << 8);
}

uint16_t* BME280::get_hum(void) {
    uint16_t hum[2];
    hum[0] = read_reg(HUM_LSB) | (read_reg(HUM_MSB) << 8);
    return hum;
}

uint16_t* BME280::get_press(void) {
    uint16_t press[2];
    press[0] = read_reg(PRESS_LSB) | (read_reg(PRESS_MSB) << 8);
    return press;
}