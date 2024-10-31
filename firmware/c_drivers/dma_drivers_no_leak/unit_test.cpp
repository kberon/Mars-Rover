#include "dma_drivers.h"
 //#include <ctime>
#include <unistd.h>
#include "gpio_drivers.h"
#include <iostream>
#include <fstream>
#include <string>
 
#define SONAR1 16
#define SONAR2 20
#define SONAR3 21

#define MOTOR1_EN 5
#define MOTOR2_EN 6
#define MOTOR3_EN 13
#define MOTOR4_EN 19
#define MOTOR5_EN 26
#define MOTOR6_EN 12

#define L_IN1	8
#define L_IN2	7
#define R_IN1	14
#define R_IN2	15

void move_forward(uint8_t power,dma_handler& dma_object, gpio_drivers gpio)
{

gpio.set_high(L_IN1);
gpio.set_low(L_IN2);
gpio.set_low(R_IN1);
gpio.set_high(R_IN2);


dma_object.modify_blocks(power,250,MOTOR1_EN);
dma_object.modify_blocks(power,250,MOTOR2_EN);
dma_object.modify_blocks(power,250,MOTOR3_EN);
dma_object.modify_blocks(power,250,MOTOR4_EN);
dma_object.modify_blocks(power,250,MOTOR5_EN);
dma_object.modify_blocks(power,250,MOTOR6_EN);

}

void move_backward(uint8_t power, dma_handler& dma_object, gpio_drivers& gpio)
{
gpio.set_low(L_IN1);
gpio.set_high(L_IN2);
gpio.set_high(R_IN1);
gpio.set_low(R_IN2);

dma_object.modify_blocks(power,250,MOTOR1_EN);
dma_object.modify_blocks(power,250,MOTOR2_EN);
dma_object.modify_blocks(power,250,MOTOR3_EN);
dma_object.modify_blocks(power,250,MOTOR4_EN);
dma_object.modify_blocks(power,250,MOTOR5_EN);
dma_object.modify_blocks(power,250,MOTOR6_EN);

}

void turn_right(uint8_t power, dma_handler& dma_object, gpio_drivers& gpio)
{
gpio.set_low(L_IN1);
gpio.set_high(L_IN2);
gpio.set_high(R_IN1);
gpio.set_low(R_IN2);

dma_object.modify_blocks(power,250,MOTOR1_EN);
dma_object.modify_blocks(power,250,MOTOR2_EN);
dma_object.modify_blocks(power,250,MOTOR3_EN);
dma_object.modify_blocks(power,250,MOTOR4_EN);
dma_object.modify_blocks(power,250,MOTOR5_EN);
dma_object.modify_blocks(power,250,MOTOR6_EN);

}

void turn_left(uint8_t power, dma_handler& dma_object, gpio_drivers& gpio)
{
gpio.set_low(L_IN1);
gpio.set_high(L_IN2);
gpio.set_high(R_IN1);
gpio.set_low(R_IN2);

dma_object.modify_blocks(power,250,MOTOR1_EN);
dma_object.modify_blocks(power, 250, MOTOR2_EN);
dma_object.modify_blocks(power, 250, MOTOR3_EN);
dma_object.modify_blocks(power, 250, MOTOR4_EN);
dma_object.modify_blocks(power, 250, MOTOR5_EN);
dma_object.modify_blocks(power, 250, MOTOR6_EN);
}

void print_all_thing(dma_handler& dma_object)
{
	std::cout << "\n";

	for (int i=0;i<20;i++)
	{
		std::cout << " " << dma_object.reserved[i].reserved_me;
	}

}

void read_sonar_1(long long& time_me)
{
        FILE *file;
        file = fopen("/sys/kernel/sonar_1_time/time_diff", "r");
	long long time = -1;
        if (file == NULL)
        {
                perror("Error opening file");
                time_me = -1;
                return;
        }
        if (fscanf(file, "%lld", &time) != 1) {
                printf("Error reading number from file\n");
                time_me = -1;
        }
        else
        {
                //printf("sonar 1 pre-conversion: %lld\n" , time);
                time_me = time/58000;
                printf("sonar_1 Read number: %lld\n", time_me);
        }
        fclose(file);
}

void read_sonar_2(long long& time_me)
{
        FILE *file;
	long long time = -1;
        file = fopen("/sys/kernel/sonar_2_time/time_diff", "r");
        if (file == NULL)
        {
                perror("Error opening file");
                time_me = -1;
                return;
        }
        if (fscanf(file, "%lld", &time) != 1) {
                printf("Error reading number from file\n");
                time_me = -1;
        }
        else
        {
                time_me = time/58000;
                printf("sonar_2 Read number: %lld\n", time_me);
        }
        fclose(file);
}

void read_sonar_3(long long& time_me)
{
        FILE *file;
        file = fopen("/sys/kernel/sonar_3_time/time_diff", "r");
	long long time = -1;
        if (file == NULL)
        {
                perror("Error opening file");
                time_me = -1;
                return;
        }
        if (fscanf(file, "%lld", &time) != 1) {
                printf("Error reading number from file\n");
                time_me = -1;
        }
        else
        {
                time_me = time/58000;
                printf("sonar_3 Read number: %lld\n", time_me);
        }
        fclose(file);
}

void prompt_sonar(gpio_drivers& gpio)
{
        gpio.set_high(SONAR1);
        sleep(0.01);
        gpio.set_low(SONAR1);
        sleep(0.80);
        gpio.set_high(SONAR2);
        sleep(0.01);
        gpio.set_low(SONAR2);
        sleep(0.80);
        gpio.set_high(SONAR3);
        sleep(0.01);
        gpio.set_low(SONAR3);
        sleep(.4);
        return;
}



int main()
{


/*
gpio_drivers gpio = gpio_drivers();


//pwm_dma(125,250,0); // pwm_dma(uint8_t on_block,uint8_t num_blocks_f,uint32_t dma_num)//rate should be a number between>
gpio.set_output(MOTOR1_EN);
gpio.set_output(MOTOR2_EN);
gpio.set_output(MOTOR3_EN);
gpio.set_output(MOTOR4_EN);
gpio.set_output(MOTOR5_EN);
gpio.set_output(MOTOR6_EN);

gpio.set_output(L_IN1);
gpio.set_output(L_IN2);
gpio.set_output(R_IN1);
gpio.set_output(R_IN2);






dma_handler dma_object = dma_handler(125,250,0,26);
dma_object.turn_off();

//testing motors moving forward
gpio.set_high(L_IN1);
gpio.set_low(L_IN2);
gpio.set_low(R_IN1);
gpio.set_high(R_IN2);


//testing motor_1
std::cout << "\ntesting motor 1: "; 
dma_object.modify_blocks(100,250,MOTOR1_EN);
sleep(1);
dma_object.turn_off();
//testing motor_2
std::cout << "\ntesting motor 2: ";
dma_object.modify_blocks(100,250,MOTOR2_EN);
sleep(1);
dma_object.turn_off();
//testing motor_3
std::cout << "\ntesting motor 3: ";
dma_object.modify_blocks(100,250,MOTOR3_EN);
sleep(1);
dma_object.turn_off();
//testing motor_4
std::cout << "\ntesting motor 4: ";
dma_object.modify_blocks(100,250,MOTOR4_EN);
sleep(1);
dma_object.turn_off();
//testing motor_5
std::cout << "\ntesting motor 5: ";
dma_object.modify_blocks(100,250,MOTOR5_EN);
sleep(1);
dma_object.turn_off();
//testing motor_1
std::cout << "\ntesting motor 6: ";
dma_object.modify_blocks(100,250,MOTOR6_EN);
sleep(1);
dma_object.turn_off();
*/



gpio_drivers gpio = gpio_drivers();

//setting up sonar triggers
gpio.set_output(SONAR1);
gpio.set_output(SONAR2);
gpio.set_output(SONAR3);
//end of setting up sonar triggers


//testing sonar from here on out

long long sonar_1_value = -1;
long long sonar_2_value = -1;
long long sonar_3_value = -1;

//while((sonar_1_value <= 0 || sonar_1_value >= 15) && (sonar_2_value <= 0 || sonar_2_value >= 15) && (sonar_3_value <= 0 || sonar_3_value >= 15))

long long x = 50000;
while(x > 1)
{
prompt_sonar(gpio);
std::cout << "1\n";
read_sonar_1(sonar_1_value);
std::cout << "2\n";
read_sonar_2(sonar_2_value);
std::cout << "3\n";
read_sonar_3(sonar_3_value);
std::cout << "4\n";
//sleep(1);
sonar_1_value = sonar_1_value/58000;
sonar_2_value = sonar_2_value/58000;
sonar_3_value = sonar_3_value/58000;
std::cout << "\nsonar 1 value: " << sonar_1_value;
std::cout << "\nsonar 2 value: " << sonar_2_value;
std::cout << "\nsonar 3 value: " << sonar_3_value;
std::cout << "\nx";
x--;
}






return 0;
}
