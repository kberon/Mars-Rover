#include "../c_drivers/gpio_drivers/gpio_drivers.h"
#include "../c_drivers/dma_drivers/dma_drivers.h"
#include <iostream>
#include <fstream>
#include <string>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

#define SONAR3 22

#define MOTOR1_EN 5
#define MOTOR2_EN 6
#define MOTOR3_EN 13
#define MOTOR4_EN 19
#define MOTOR5_EN 26
#define MOTOR6_EN 12

#define L_IN1 8
#define L_IN2 7
#define R_IN1 14
#define R_IN2 15

void move_forward(uint8_t power, dma_handler& dma_object)
{
    gpio_drivers::set_high(L_IN1);
    gpio_drivers::set_low(L_IN2);
    gpio_drivers::set_low(R_IN1);
    gpio_drivers::set_high(R_IN2);

    dma_object.modify_blocks(power, 250, MOTOR1_EN);
    dma_object.modify_blocks(power, 250, MOTOR2_EN);
    dma_object.modify_blocks(power, 250, MOTOR3_EN);
    dma_object.modify_blocks(power, 250, MOTOR4_EN);
    dma_object.modify_blocks(power, 250, MOTOR5_EN);
    dma_object.modify_blocks(power, 250, MOTOR6_EN);
}

void move_backward(uint8_t power, dma_handler& dma_object)
{
    gpio_drivers::set_low(L_IN1);
    gpio_drivers::set_high(L_IN2);
    gpio_drivers::set_high(R_IN1);
    gpio_drivers::set_low(R_IN2);

    dma_object.modify_blocks(power, 250, MOTOR1_EN);
    dma_object.modify_blocks(power, 250, MOTOR2_EN);
    dma_object.modify_blocks(power, 250, MOTOR3_EN);
    dma_object.modify_blocks(power, 250, MOTOR4_EN);
    dma_object.modify_blocks(power, 250, MOTOR5_EN);
    dma_object.modify_blocks(power, 250, MOTOR6_EN);
}

void turn_right(uint8_t power, dma_handler& dma_object)
{
    gpio_drivers::set_low(L_IN1);
    gpio_drivers::set_high(L_IN2);
    gpio_drivers::set_high(R_IN1);
    gpio_drivers::set_low(R_IN2);

    dma_object.modify_blocks(power, 250, MOTOR1_EN);
    dma_object.modify_blocks(power, 250, MOTOR2_EN);
    dma_object.modify_blocks(power, 250, MOTOR3_EN);
    dma_object.modify_blocks(power, 250, MOTOR4_EN);
    dma_object.modify_blocks(power, 250, MOTOR5_EN);
    dma_object.modify_blocks(power, 250, MOTOR6_EN);
}

void turn_left(uint8_t power, dma_handler& dma_object)
{
    gpio_drivers::set_high(L_IN1);
    gpio_drivers::set_low(L_IN2);
    gpio_drivers::set_low(R_IN1);
    gpio_drivers::set_high(R_IN2);

    dma_object.modify_blocks(power, 250, MOTOR1_EN);
    dma_object.modify_blocks(power, 250, MOTOR2_EN);
    dma_object.modify_blocks(power, 250, MOTOR3_EN);
    dma_object.modify_blocks(power, 250, MOTOR4_EN);
    dma_object.modify_blocks(power, 250, MOTOR5_EN);
    dma_object.modify_blocks(power, 250, MOTOR6_EN);
}

int main()
{
    // GPIO setup
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

    dma_handler dma_object = dma_handler(125, 250, 0, 26);

    // Controller input setup
    const char* device_path = "/dev/input/event4"; // Adjust path as necessary for your Xbox controller
    int fd = open(device_path, O_RDONLY);
    if (fd == -1) {
        std::cerr << "Failed to open input device: " << device_path << std::endl;
        return 1;
    }

    struct input_event ev;
    uint8_t power = 175; // Default power level for motors
    while (true) {
        ssize_t bytes = read(fd, &ev, sizeof(ev));
        if (bytes < (ssize_t)sizeof(ev)) {
            std::cerr << "Error reading input event" << std::endl;
            break;
        }

        if (ev.type == EV_KEY) {
            if (ev.value == 1) { // Key pressed
                switch (ev.code) {
                    case BTN_A: // A button: Move forward
                        move_forward(power, dma_object);
                        cout << "Button A pressed: Moving forward" << endl;
                        break;
                    case BTN_B: // B button: Move backward
                        move_backward(power, dma_object);
                        cout << "Button B pressed: Moving backward" << endl;
                        break;
                    case BTN_X: // X button: Turn left
                        turn_left(power, dma_object);
                        cout << "Button X pressed: Moving left" << endl;
                        break;
                    case BTN_Y: // Y button: Turn right
                        turn_right(power, dma_object);
                        cout << "Button Y pressed: Moving right" << endl;
                        break;
                }
            } else if (ev.value == 0) { // Key released
                dma_object.turn_off();
            }
        } else if (ev.type == EV_ABS) {
            // Handle joystick movement for turning
            if (ev.code == ABS_X) {
                if (ev.value < 128) {
                    // Joystick moved left
                    turn_left(power, dma_object);
                    cout << "Joystick moved left: Moving left" << endl;
                } else if (ev.value > 128) {
                    // Joystick moved right
                    turn_right(power, dma_object);
                    cout << "Joystick moved right: Moving right" << endl;
                } else {
                    // Joystick centered
                    dma_object.turn_off();
                }
            }
        }
    }

    close(fd);
    return 0;
}
