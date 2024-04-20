#include "BME280.h"
#include <cmath>
#include <wiringPiI2C.h>

BME280::BME280(void) {}

bool BME280::init(void)
{
    // Initialize I2C
    // reset
    set_reg(RESET, 0xB6);
    delay(300);

    fd = wiringPiI2CSetup(ADDRESS);

    if (fd == -1)
    {
        return false;
}

    // ctrl hum: 16x oversampling
    set_reg(CTRL_HUM, 0x05);
    // ctrl meas: 16x oversampling, normal mode
    set_reg(CTRL_MEAS, 0x27);

    // read calibration values
    uint16_t temp = read_reg(DIG_T1) | read_reg(DIG_T1 + 1) << 8;
    dig_T1 = (uint16_t)(temp >> 8) | (temp << 8);
    temp = (int16_t)read_reg(DIG_T2) | read_reg(DIG_T2 + 1) << 8;
    dig_T2 = (temp >> 8) | (temp << 8);
    temp = (int16_t)read_reg(DIG_T3) | read_reg(DIG_T3 + 1) << 8;
    dig_T3 = (temp >> 8) | (temp << 8);
    
    uint16_t u_press = read_reg(DIG_P1) | read_reg(DIG_P1 + 1) << 8;
    dig_P1 = (u_press >> 8) | (u_press << 8);
    int16_t press = read_reg(DIG_P2) | read_reg(DIG_P2 + 1) << 8;
    dig_P2 = (press >> 8) | (press << 8);
    press = read_reg(DIG_P3) | read_reg(DIG_P3 + 1) << 8;
    dig_P3 = (press >> 8) | (press << 8);
    press = read_reg(DIG_P4) | read_reg(DIG_P4 + 1) << 8;
    dig_P4 = (press >> 8) | (press << 8);
    press = read_reg(DIG_P5) | read_reg(DIG_P5 + 1) << 8;
    dig_P5 = (press >> 8) | (press << 8);
    press = read_reg(DIG_P6) | read_reg(DIG_P6 + 1) << 8;
    dig_P6 = (press >> 8) | (press << 8);
    press = read_reg(DIG_P7) | read_reg(DIG_P7 + 1) << 8;
    dig_P7 = (press >> 8) | (press << 8);
    press = read_reg(DIG_P8) | read_reg(DIG_P8 + 1) << 8;
    dig_P8 = (press >> 8) | (press << 8);
    press = read_reg(DIG_P9) | read_reg(DIG_P9 + 1) << 8;
    dig_P9 = (press >> 8) | (press << 8);


    dig_H1 = read_reg(DIG_H1);
    uint16_t hum = read_reg(DIG_H2) | read_reg(DIG_H2 + 1) << 8;
    dig_H2 = (hum >> 8) | (hum << 8);
    dig_H3 = read_reg(DIG_H3);
    dig_H4 = read_reg(DIG_H4) << 4 | (read_reg(DIG_H4 + 1) & 0x0F);
    dig_H5 = read_reg(DIG_H5) >> 4 | read_reg(DIG_H5 + 1) << 4;
    dig_H6 = read_reg(DIG_H6);


    return true;
}

void BME280::set_reg(uint8_t reg, uint8_t val)
{
    uint8_t data[2];
    data[0] = reg;
    data[1] = val;
    wiringPiI2CWriteReg8(fd, reg, val);
}

uint8_t BME280::read_reg(uint8_t reg)
{
    return wiringPiI2CReadReg8(fd, reg);
}

float BME280::get_temp(void)
{
    // returns in C
    int32_t var1, var2;

    int32_t adc_T = read_reg(TEMP_MSB) << 16 | read_reg(TEMP_LSB) << 8 | read_reg(TEMP_XLSB);
    if (adc_T == 0x800000) // value in case temp measurement was disabled
        return NAN;
    adc_T >>= 4;

    var1 = (int32_t)((adc_T / 8) - ((int32_t)read_reg(dig_T1) * 2));
    var1 = (var1 * ((int32_t)read_reg(dig_T2))) / 2048;
    var2 = (int32_t)((adc_T / 16) - ((int32_t)read_reg(dig_T1)));
    var2 = (((var2 * var2) / 4096) * ((int32_t)read_reg(dig_T3))) / 16384;

    t_fine = var1 + var2;

    int32_t T = (t_fine * 5 + 128) / 256;

    return (float)T / 100;
}

float BME280::get_hum(void)
{
    int32_t var1, var2, var3, var4, var5;

    int32_t adc_H = read_reg(HUM_MSB) << 8 | read_reg(HUM_LSB);
    if (adc_H == 0x8000) // value in case humidity measurement was disabled
        return NAN;

    var1 = t_fine - ((int32_t)76800);
    var2 = (int32_t)(adc_H * 16384);
    var3 = (int32_t)(((int32_t)read_reg(dig_H4)) * 1048576);
    var4 = ((int32_t)read_reg(dig_H5)) * var1;
    var5 = (((var2 - var3) - var4) + (int32_t)16384) / 32768;
    var2 = (var1 * ((int32_t)read_reg(dig_H6))) / 1024;
    var3 = (var1 * ((int32_t)read_reg(dig_H3))) / 2048;
    var4 = ((var2 * (var3 + (int32_t)32768)) / 1024) + (int32_t)2097152;
    var2 = ((var4 * ((int32_t)read_reg(dig_H2))) + 8192) / 16384;
    var3 = var5 * var2;
    var4 = ((var3 / 32768) * (var3 / 32768)) / 128;
    var5 = var3 - ((var4 * ((int32_t)read_reg(dig_H1))) / 16);
    var5 = (var5 < 0 ? 0 : var5);
    var5 = (var5 > 419430400 ? 419430400 : var5);
    uint32_t H = (uint32_t)(var5 / 4096);

    return ((float)H / 1024.0);
}

float BME280::get_press(void)
{
    int64_t var1, var2, var3, var4;

    int32_t adc_P = read_reg(PRESS_MSB) << 16 | read_reg(PRESS_LSB) << 8 | read_reg(PRESS_XLSB);
    if (adc_P == 0x800000) // value in case pressure measurement was disabled
        return NAN;
    adc_P >>= 4;

    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)read_reg(dig_P6);
    var2 = var2 + ((var1 * (int64_t)read_reg(dig_P5)) * 131072);
    var2 = var2 + (((int64_t)read_reg(dig_P4)) * 34359738368);
    var1 = ((var1 * var1 * (int64_t)read_reg(dig_P3)) / 256) +
           ((var1 * ((int64_t)read_reg(dig_P2)) * 4096));
    var3 = ((int64_t)1) * 140737488355328;
    var1 = (var3 + var1) * ((int64_t)read_reg(dig_P1)) / 8589934592;

    if (var1 == 0)
    {
        return 0; // avoid exception caused by division by zero
    }

    var4 = 1048576 - adc_P;
    var4 = (((var4 * 2147483648) - var2) * 3125) / var1;
    var1 = (((int64_t)read_reg(dig_P9)) * (var4 / 8192) * (var4 / 8192)) /
           33554432;
    var2 = (((int64_t)read_reg(dig_P8)) * var4) / 524288;
    var4 = ((var4 + var1 + var2) / 256) + (((int64_t)read_reg(dig_P7)) * 16);

    float P = var4 / 256.0;

    return P;
}