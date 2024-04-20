#include "ISM330DHCX.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(){

    ISM330DHCX imu = ISM330DHCX();
    imu.init();

    while(1){
        printf("Gyro: [%d, %d, %d] \n", imu.get_gyro().x, imu.get_gyro().y, imu.get_gyro().z);
        printf("Accel: [%d, %d, %d] \n", imu.get_accel().x, imu.get_accel().y, imu.get_accel().z);
        delay(1000);
    }

    return 0;
}