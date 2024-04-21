#include "BME280.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(){

    BME280 bme = BME280();

    if(!bme.init()){
        printf("BME280 init failed\n");
        return 1;
    }

    while(1){
        printf("Temperature: %f C \n", bme.get_temp());
        printf("Humidity: %f %\n", bme.get_hum());
        printf("Pressure: %f hPa \n", bme.get_press()/100.0);
        delay(1000);
    }

    return 0;
}