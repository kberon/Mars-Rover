#include "ISM330DHCX/ISM330DHCX.h"
#include "BME280/BME280.h"

int main(){
    BME280 bme = BME280();
    ISM330DHCX imu = ISM330DHCX();
    bme.init();
    imu.init();

    //read all sensors
    while(1){
        printf("Temperature: %f C \n", bme.get_temp());
        printf("Humidity: %f %\n", bme.get_hum());
        printf("Pressure: %f hPa \n", bme.get_press()/100.0);
        printf("Gyro: [%f, %f, %f] rads/s\n", imu.get_gyro().x, imu.get_gyro().y, imu.get_gyro().z);
        printf("Accel: [%f, %f, %f] m/s^2\n", imu.get_accel().x, imu.get_accel().y, imu.get_accel().z);
        delay(1000);
    }

    return 0;

}