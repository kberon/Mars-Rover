#include <iostream>
#include <iomanip> // for std::fixed and std::setprecision
#include "ISM330DHCX/ISM330DHCX.h"
#include "BME280/BME280.h"

int main() {
    BME280 bme = BME280();
    ISM330DHCX imu = ISM330DHCX();
    bme.init();
    imu.init();

    //read all sensors
    while(1){
        int32_t T = bme.get_temp();
        printf("Temperature is: %d.%d C\n", T/100, T - (T/100)*100);
        printf("Humidity: %.3f %RH\n", bme.get_hum());
        printf("Pressure: %.2f Pa \n", bme.get_press());
        ISM330DHCX::GyroData gyro = imu.get_gyro();
        printf("Gyro: [%.2f, %.2f, %.2f] rads/s\n", gyro.x, gyro.y, gyro.z);
        ISM330DHCX::AccelData accel = imu.get_accel();
        printf("Accel: [%.2f, %.2f, %.2f] m/s^2\n", accel.x, accel.y, accel.z);
        delay(3000);
    }

    return 0;
}

