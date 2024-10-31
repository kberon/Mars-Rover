#include "gpio_drivers.h"
#include "dma_drivers.h"
#include <iostream>
#include <fstream>
#include <string>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

#define SONAR1 16
#define SONAR2 20
#define SONAR3 21

#define MOTOR1_EN 5
#define MOTOR2_EN 6
#define MOTOR3_EN 13
#define MOTOR4_EN 19
#define MOTOR5_EN 26
#define MOTOR6_EN 12

//had to swap forward and backward
//#define L_IN1 8
//#define L_IN2 7
//#define R_IN1 14
//#define R_IN2 15

#define L_IN1 7
#define L_IN2 8
#define R_IN1 15
#define R_IN2 14

#define device_path "/dev/input/event4" // change as needed
// const char* device_path = "/dev/input/event10";
// ls /dev/input/event*

// buttons: right middle : switch modes, left middle: kill

//--------------- GLOBAL VARIABLES ------------------
bool mode = true; // 0 = autonomous, 1 = teleop
dma_handler dma_object = dma_handler(50, 250, 0, 26);

int current_dir = 0; // 0 for stop, 1 for forward, 2 for right, 3 for back, 4 for left

int fd_controller;
struct input_event ev;

void move_backward(uint8_t power, dma_handler &dma_object, gpio_drivers& gpio)
{

    gpio.set_high(L_IN1);
    gpio.set_low(L_IN2);
    gpio.set_low(R_IN1);
    gpio.set_high(R_IN2);

    dma_object.modify_blocks(power, 250, MOTOR1_EN);
    dma_object.modify_blocks(power, 250, MOTOR2_EN);
    dma_object.modify_blocks(power, 250, MOTOR3_EN);
    dma_object.modify_blocks(power, 250, MOTOR4_EN);
    dma_object.modify_blocks(power, 250, MOTOR5_EN);
    dma_object.modify_blocks(power, 250, MOTOR6_EN);
}

void move_forward(uint8_t power, dma_handler &dma_object, gpio_drivers& gpio)
{
    gpio.set_low(L_IN1);
    gpio.set_high(L_IN2);
    gpio.set_high(R_IN1);
    gpio.set_low(R_IN2);

    dma_object.modify_blocks(power, 250, MOTOR1_EN);
    dma_object.modify_blocks(power, 250, MOTOR2_EN);
    dma_object.modify_blocks(power, 250, MOTOR3_EN);
    dma_object.modify_blocks(power, 250, MOTOR4_EN);
    dma_object.modify_blocks(power, 250, MOTOR5_EN);
    dma_object.modify_blocks(power, 250, MOTOR6_EN);
}

void turn_left(uint8_t power, dma_handler &dma_object, gpio_drivers& gpio)
{
    gpio.set_high(L_IN1);
    gpio.set_low(L_IN2);
    gpio.set_high(R_IN1);
    gpio.set_low(R_IN2);

    dma_object.modify_blocks(power, 250, MOTOR1_EN);
    dma_object.modify_blocks(power, 250, MOTOR2_EN);
    dma_object.modify_blocks(power, 250, MOTOR3_EN);
    dma_object.modify_blocks(power, 250, MOTOR4_EN);
    dma_object.modify_blocks(power, 250, MOTOR5_EN);
    dma_object.modify_blocks(power, 250, MOTOR6_EN);
}

void turn_right(uint8_t power, dma_handler &dma_object, gpio_drivers& gpio)
{
    gpio.set_low(L_IN1);
    gpio.set_high(L_IN2);
    gpio.set_low(R_IN1);
    gpio.set_high(R_IN2);

    dma_object.modify_blocks(power, 250, MOTOR1_EN);
    dma_object.modify_blocks(power, 250, MOTOR2_EN);
    dma_object.modify_blocks(power, 250, MOTOR3_EN);
    dma_object.modify_blocks(power, 250, MOTOR4_EN);
    dma_object.modify_blocks(power, 250, MOTOR5_EN);
    dma_object.modify_blocks(power, 250, MOTOR6_EN);
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


void init_motors_and_sonar(gpio_drivers& gpio)
{
    dma_object.turn_off();

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

    // setting up sonar triggers
    gpio.set_output(SONAR1);
    gpio.set_output(SONAR2);
    gpio.set_output(SONAR3);
}

int init_controller()
{
    // Controller input setup
    // Adjust path as necessary for your Xbox controller
    fd_controller = open(device_path, O_RDONLY);
    if (fd_controller == -1)
    {
        std::cerr << "Failed to open input device: " << device_path << std::endl;
        return 1;
    }
    return 0;
}
int main()
{
    gpio_drivers gpio = gpio_drivers();
    init_motors_and_sonar(gpio);
    init_controller();

    while (true)
    {
        while (mode == true)
        {
            uint8_t power = 40; // 100: Default power level for motors
            cout << "IN TELOP MODE: " << mode << endl;
            ssize_t bytes = read(fd_controller, &ev, sizeof(ev));
            if (bytes < (ssize_t)sizeof(ev))
            {
                std::cerr << "Error reading input event" << std::endl;
                break;
            }

            if (ev.type == EV_KEY)
            {
                if (ev.value == 1)
                { // Key pressed
                    switch (ev.code)
                    {
                    case BTN_Y: // Y button: Move forward
                        if (current_dir != 1)
                        { // if not currently moving foward
                            dma_object.turn_off();
                            sleep(1);
                            current_dir = 1;
                        }
                        move_forward(power, dma_object,gpio);
                        cout << "Button Y pressed: Moving forward" << endl;
                        break;
                    case BTN_A: // A button: Move backward
                        if (current_dir != 3)
                        { // if not currently moving backwards
                            dma_object.turn_off();
                            sleep(1);
                            current_dir = 3;
                        }
                        move_backward(power, dma_object,gpio);
                        cout << "Button A pressed: Moving backward" << endl;
                        break;
                    case BTN_X: // X button: Turn left
                        if (current_dir != 4)
                        { // if not currently moving left
                            dma_object.turn_off();
                            sleep(1);
                            current_dir = 4;
                        }
                        turn_left(power, dma_object,gpio);
                        cout << "Button X pressed: Moving left" << endl;
                        break;
                    case BTN_B: // B button: Turn right
                        if (current_dir != 2)
                        { // if not currently moving right
                            dma_object.turn_off();
                            sleep(1);
                            current_dir = 2;
                        }
                        turn_right(power, dma_object,gpio);
                        cout << "Button B pressed: Moving right" << endl;
                        break;
                    case BTN_START:
                        dma_object.turn_off();
                        mode = false;
                        current_dir = 0;
                        cout << "Changing to autonomous mode: " << mode << endl;
                        sleep(1);
                        break;
                    case BTN_SELECT:
                        dma_object.turn_off();
                        cout << "KILLED" << endl;
                        break;
                    }
                }
                else if (ev.value == 0)
                { // Key released
                    dma_object.turn_off();
                }
            }
            cout << "END OF TELEOP LOOP: " << mode << endl;
        
        }
        
        cout << "BETWEEN LOOPS, MODE: " << mode << endl;

        prompt_sonar(gpio);
        long long sonar_1_value = -1;
        move_forward(40, dma_object,gpio);
        
        while (mode == false)
        {
         cout << "IN AUTONOMOUS MODE" << endl;

          ssize_t bytes = read(fd_controller, &ev, sizeof(ev));
            if (bytes == sizeof(ev)) {
                if (ev.type == EV_KEY && ev.value == 1) {
                    switch (ev.code) {
                        case BTN_START:
                            dma_object.turn_off();
                            mode = true;
                            std::cout << "Changing to teleop mode" << std::endl;
                            sleep(1);
                            continue;  // Skip the rest of the autonomous loop
                        case BTN_SELECT:
                            dma_object.turn_off();
                            std::cout << "KILLED" << std::endl;
                            return 0;  // Exit the program
                    }
                }
            }

            // if not switch or kill, autonomous
            prompt_sonar(gpio);
            read_sonar_1(sonar_1_value);
            prompt_sonar(gpio);
            read_sonar_1(sonar_1_value);
            sonar_1_value = 0;
            //move_forward(30, dma_object);


            
            while(sonar_1_value <= 0 || sonar_1_value >= 50){
		//while(1){
		//keep reading controller input
	ssize_t bytes = read(fd_controller, &ev, sizeof(ev));
            if (bytes == sizeof(ev)) {
                if (ev.type == EV_KEY && ev.value == 1) {
                    switch (ev.code) {
                        case BTN_START:
                            dma_object.turn_off();
                            mode = true;
                            std::cout << "Changing to teleop mode" << std::endl;
                            sleep(1);
                            continue;  // Skip the rest of the autonomous loop
                        case BTN_SELECT:
                            dma_object.turn_off();
                            std::cout << "KILLED" << std::endl;
                            return 0;  // Exit the program
                    }
                }
            }
                prompt_sonar(gpio);
                read_sonar_1(sonar_1_value);
                sleep(.4);
            }



            if(sonar_1_value < 50){
                dma_object.turn_off();
                sleep(1);
                turn_right(100, dma_object,gpio);
                sleep(2);
                dma_object.turn_off();
                move_forward(40, dma_object,gpio);
            }
            usleep(10000); 
        }
    }

    close(fd_controller);
    return 0;
}
