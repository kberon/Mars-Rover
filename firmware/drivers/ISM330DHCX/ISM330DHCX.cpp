#include "ISM330DHCX.h"

ISM330DHCX::ISM330DHCX(void) {}

bool ISM330DHCX::init(void) {
    // Initialize I2C
    //pull pin CS high physically!!
    //accelerometer control: 416 Hz (high performance), 2g, high-resultion = 0
    set_reg(CTRL1_XL, 0x60);
    //gyroscope control: 416 Hz (high performance), 2000 dps, high-resultion = 0
    set_reg(CTRL2_G, 0x60);

    fd = wiringPiI2CSetup(ADDRESS);
    
    return true;
}

void ISM330DHCX::set_reg(uint8_t reg, uint8_t val) {
    uint8_t data[2];
    data[0] = reg;
    data[1] = val;
    wiringPiI2CWriteReg8(fd, reg, val);
}

uint8_t ISM330DHCX::read_reg(uint8_t reg) {
    return wiringPiI2CReadReg8(fd, reg);
}

uint16_t ISM330DHCX::get_temp(void) {    
    return read_reg(OUT_TEMP_L) | (read_reg(OUT_TEMP_H) << 8);
}

uint16_t* ISM330DHCX::get_gyro(void) {
    uint16_t gyro[3];
    gyro[0] = read_reg(OUTX_L_G) | (read_reg(OUTX_H_G) << 8);
    gyro[1] = read_reg(OUTY_L_G) | (read_reg(OUTY_H_G) << 8);
    gyro[2] = read_reg(OUTZ_L_G) | (read_reg(OUTZ_H_G) << 8);
    return gyro;
}

uint16_t* ISM330DHCX::get_accel(void) {
    uint16_t accel[3];
    accel[0] = read_reg(OUTX_L_A) | (read_reg(OUTX_H_A) << 8);
    accel[1] = read_reg(OUTY_L_A) | (read_reg(OUTY_H_A) << 8);
    accel[2] = read_reg(OUTZ_L_A) | (read_reg(OUTZ_H_A) << 8);
    return accel;
}