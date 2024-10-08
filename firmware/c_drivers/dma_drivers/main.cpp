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

void move_forward(uint8_t power,dma_handler& dma_object)
{

gpio_drivers::set_high(L_IN1);
gpio_drivers::set_low(L_IN2);
gpio_drivers::set_low(R_IN1);
gpio_drivers::set_high(R_IN2);


dma_object.modify_blocks(power,250,MOTOR1_EN);
dma_object.modify_blocks(power,250,MOTOR2_EN);
dma_object.modify_blocks(power,250,MOTOR3_EN);
dma_object.modify_blocks(power,250,MOTOR4_EN);
dma_object.modify_blocks(power,250,MOTOR5_EN);
dma_object.modify_blocks(power,250,MOTOR6_EN);

}

void move_backward(uint8_t power, dma_handler& dma_object)
{
gpio_drivers::set_low(L_IN1);
gpio_drivers::set_high(L_IN2);
gpio_drivers::set_high(R_IN1);
gpio_drivers::set_low(R_IN2);

dma_object.modify_blocks(power,250,MOTOR1_EN);
dma_object.modify_blocks(power,250,MOTOR2_EN);
dma_object.modify_blocks(power,250,MOTOR3_EN);
dma_object.modify_blocks(power,250,MOTOR4_EN);
dma_object.modify_blocks(power,250,MOTOR5_EN);
dma_object.modify_blocks(power,250,MOTOR6_EN);

}

void turn_right(uint8_t power, dma_handler& dma_object)
{
gpio_drivers::set_low(L_IN1);
gpio_drivers::set_high(L_IN2);
gpio_drivers::set_high(R_IN1);
gpio_drivers::set_low(R_IN2);

dma_object.modify_blocks(power,250,MOTOR1_EN);
dma_object.modify_blocks(power,250,MOTOR2_EN);
dma_object.modify_blocks(power,250,MOTOR3_EN);
dma_object.modify_blocks(power,250,MOTOR4_EN);
dma_object.modify_blocks(power,250,MOTOR5_EN);
dma_object.modify_blocks(power,250,MOTOR6_EN);

}

void turn_left(uint8_t power, dma_handler& dma_object)
{
gpio_drivers::set_low(L_IN1);
gpio_drivers::set_high(L_IN2);
gpio_drivers::set_high(R_IN1);
gpio_drivers::set_low(R_IN2);

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

void read_sonar_1(long long& time)
{
	FILE *file;
	file = fopen("/sys/kernel/sonar_1_time/time_diff", "r");
	if (file == NULL) 
	{
    		perror("Error opening file");
		time = -1;
    		return;
	}
	if (fscanf(file, "%lld", &time) != 1) {
    		printf("Error reading number from file\n");
		time = -1;
	} 
	else 
	{
		time = time/58000;
    		printf("Read number: %lld\n", time);
	}
	fclose(file);
}

void read_sonar_2(long long& time)
{
        FILE *file;
        file = fopen("/sys/kernel/sonar_2_time/time_diff", "r");
        if (file == NULL)
        {
                perror("Error opening file");
                time = -1;
                return;
        }
        if (fscanf(file, "%lld", &time) != 1) {
                printf("Error reading number from file\n");
                time = -1;
        }
        else
        {
		time = time/58000;
                printf("Read number: %lld\n", time);
        }
        fclose(file);
}

void read_sonar_3(long long& time)
{
        FILE *file;
        file = fopen("/sys/kernel/sonar_3_time/time_diff", "r");
        if (file == NULL)
        {
                perror("Error opening file");
                time = -1;
                return;
        }
        if (fscanf(file, "%lld", &time) != 1) {
                printf("Error reading number from file\n");
                time = -1;
        }
        else
        {
		time = time/58000;
                printf("Read number: %lld\n", time);
        }
        fclose(file);
}

void prompt_sonar()
{
	gpio_drivers::set_high(SONAR1);
	gpio_drivers::set_high(SONAR2);
	gpio_drivers::set_high(SONAR3);
	sleep(0.002);
	gpio_drivers::set_low(SONAR1);
	gpio_drivers::set_low(SONAR2);
	gpio_drivers::set_low(SONAR3);
	return;
}


int main()
{

//pwm_dma(125,250,0); // pwm_dma(uint8_t on_block,uint8_t num_blocks_f,uint32_t dma_num)//rate should be a number between>
gpio_drivers::set_output(MOTOR1_EN);
gpio_drivers::set_output(MOTOR2_EN);
gpio_drivers::set_output(MOTOR3_EN);
gpio_drivers::set_output(MOTOR4_EN);
gpio_drivers::set_output(MOTOR5_EN);
gpio_drivers::set_output(MOTOR6_EN);

gpio_drivers::set_output(L_IN1);
gpio_drivers::set_output(L_IN2);
gpio_drivers::set_output(R_IN1);
gpio_drivers::set_output(R_IN2);

//setting up sonar triggers
gpio_drivers::set_output(SONAR1);
gpio_drivers::set_output(SONAR2);
gpio_drivers::set_output(SONAR3);
//end of setting up sonar triggers



dma_handler dma_object = dma_handler(125,250,0,26);
dma_object.turn_off();
move_forward(100,dma_object);


long long sonar_1_value = -1;
long long sonar_2_value = -1;
long long sonar_3_value = -1;

while((sonar_1_value <= 0 || sonar_1_value >= 15) && (sonar_2_value <= 0 || sonar_2_value >= 15) && (sonar_3_value <= 0 || sonar_3_value >= 15))
{
long long sonar_1_value = -1;
prompt_sonar();
read_sonar_1(sonar_1_value);
sleep(1);
}




/*
std::string line;
int distance;
do{
	//trigger PWM
	gpio_drivers::set_high(SONAR3);
	sleep(0.00001);
	gpio_drivers::set_low(SONAR3);

	//get interrupt info (Distance)
	std::getline(inputFile1, line);
	int distance = std::atoi(line.c_str());
	
	move_forward(175, dma_object);
	//sleep(1);

	
}while(distance>15); 

dma_object.turn_off();*/


return 0;
}
