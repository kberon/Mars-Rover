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
    while(1) {
        std::cout << std::fixed << std::setprecision(3); // Set precision to 3 decimal places
        std::cout << "Temperature: " << bme.get_temp()/2 << " C\n";
        std::cout << "Humidity: " << bme.get_hum()/4 << " %\n";
        std::cout << "Pressure: " << bme.get_press()/400.0 << " hPa\n";
        std::cout << "Gyro: [" << imu.get_gyro().x << ", " << imu.get_gyro().y << ", " << imu.get_gyro().z << "] rads/s\n";
        std::cout << "Accel: [" << imu.get_accel().x << ", " << imu.get_accel().y << ", " << imu.get_accel().z << "] m/s^2\n";
        std::cout << std::flush;
        delay(1000);
    }

    return 0;
}

