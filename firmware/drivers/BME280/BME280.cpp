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

    //sensor mode = normal mode, t_standby = 0.5ms, pressure oversampling = 16x, temperature oversampling = 2x, humidity 1x
    //current consumption = 633uA, RMS Noise = 0.2Pa, Data output rate = 25Hz, Filter bandwith = .53 Hz, Response time = .9s



    //set_reg()

    // ctrl hum: 16x oversampling
    set_reg(CTRL_HUM, 0x05);
    // ctrl meas: 16x oversampling, normal mode
    set_reg(CTRL_MEAS, 0x27);

    // read calibration values
    dig_T1 = read_unsigned16(DIG_T1);
    dig_T2 = read_signed16(DIG_T2);
    dig_T3 = read_signed16(DIG_T3);
    
   dig_P1 = read_unsigned16(DIG_P1);
    dig_P2 = read_signed16(DIG_P2);
    dig_P3 = read_signed16(DIG_P3);
    dig_P4 = read_signed16(DIG_P4);
    dig_P5 = read_signed16(DIG_P5);
    dig_P6 = read_signed16(DIG_P6);
    dig_P7 = read_signed16(DIG_P7);
    dig_P8 = read_signed16(DIG_P8);
    dig_P9 = read_signed16(DIG_P9);

    dig_H1 = read_unsigned8(DIG_H1);
    dig_H2 = read_signed16(DIG_H2);
    dig_H3 = read_unsigned8(DIG_H3);
    dig_H4 = (read_signed8(DIG_H4) << 4) | (read_unsigned8(DIG_H4 + 1) & 0xF);
    dig_H5 = (read_signed8(DIG_H5 + 1) << 4) | (read_unsigned8(DIG_H5) >> 4);
    dig_H6 = read_signed8(DIG_H6);


    return true;
}

void BME280::set_reg(uint8_t reg, uint8_t val)
{
    uint8_t data[2];
    data[0] = reg;
    data[1] = val;
    wiringPiI2CWriteReg8(fd, reg, val);
}

uint8_t BME280::read_unsigned8(uint8_t reg)
{
    return wiringPiI2CReadReg8(fd, reg) && 0xFF;
}

int8_t BME280::read_signed8(uint8_t reg)
{
    int8_t result = read_reg(reg);
    if (result > 127)
    {
        result -= 256;
    }
    return result;
}

uint16_t BME280:: read_unsigned16(uint8_t reg){
    return (read_reg(reg) | read_reg(reg + 1) << 8) && 0xFFFF;
}

int16_t BME280:: read_signed16(uint8_t reg){
    uint16_t val = read_unsigned16(reg);
    if(val > 32767){
        val -= 65536;
    }
    return (int16_t)val;
}

uint8_t BME280:: read_reg(uint8_t reg){
    return wiringPiI2CReadReg8(fd, reg);
}

float BME280::get_temp(void)
{
    // returns in C
    int32_t var1, var2, T;

    int32_t adc_T = ((read_reg(TEMP_MSB) << 16 | read_reg(TEMP_LSB) << 8 | read_reg(TEMP_XLSB)));
   

    var1 = ((((adc_T>>3) - ((int32_t)dig_T1<<1))) * ((int32_t)dig_T2)) >> 11; 
    var2 = (((((adc_T>>4) - ((int32_t)dig_T1)) * ((adc_T>>4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14; 
    t_fine = var1 + var2; 
    T = (t_fine * 5 + 128);

    return T/100.0;
}

float BME280::get_hum(void)
{
    int32_t v_x1_u32r; 
    v_x1_u32r = (t_fine - ((int32_t)76800));

    int32_t adc_H = read_reg(HUM_MSB) << 8 | read_reg(HUM_LSB);

    v_x1_u32r = (((((adc_H << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) * v_x1_u32r)) + ((int32_t)16384)) >> 15) * 
        (((((((v_x1_u32r * ((int32_t)dig_H6)) >> 10) * (((v_x1_u32r * ((int32_t)dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + 
        ((int32_t)2097152)) * ((int32_t)dig_H2) + 8192) >> 14)); 
    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)dig_H1)) >> 4));
     v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
    v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r); 
    return ((uint32_t)(v_x1_u32r >> 7) / 1024);
    
}

float BME280::get_press(void)
{
    int32_t adc_P = (read_reg(PRESS_MSB) << 16 | read_reg(PRESS_LSB) << 8 | read_reg(PRESS_XLSB)) >> 4;
    int64_t var1, var2, p; 
    var1 = ((int64_t)t_fine) - 128000; 
    var2 = var1 * var1 * (int64_t)dig_P6; 
    var2 = var2 + ((var1*(int64_t)dig_P5)<<17); 
    var2 = var2 + (((int64_t)dig_P4)<<35); 
    var1 = ((var1 * var1 * (int64_t)dig_P3)>>8) + ((var1 * (int64_t)dig_P2)<<12); 
    var1 = (((((int64_t)1)<<47)+var1))*((int64_t)dig_P1)>>33; 
    if (var1 == 0) 
        { 
            return 0; // avoid exception caused by division by zero 
        } 
    p = 1048576-adc_P; 
    p = (((p<<31)-var2)*3125)/var1; 
    var1 = (((int64_t)dig_P9) * (p>>13) * (p>>13)) >> 25; 
    var2 = (((int64_t)dig_P8) * p) >> 19; p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7)<<4); 
    return (uint32_t) p/ 10000.0;
}