#include ../c_drivers/gpio_drivers "gpio_drivers.h"
#include <iostream>
#include <unistd.h>
#include <SDL2/SDL.h>


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
gpio_drivers::set_high(R_IN1);
gpio_drivers::set_low(R_IN2);



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
gpio_drivers::set_low(R_IN1);
gpio_drivers::set_high(R_IN2);

dma_object.modify_blocks(power,250,MOTOR2_EN);
dma_object.modify_blocks(power,250,MOTOR3_EN);
dma_object.modify_blocks(power,250,MOTOR4_EN);
dma_object.modify_blocks(power,250,MOTOR5_EN);
dma_object.modify_blocks(power,250,MOTOR6_EN);

}

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
    {
        std::cerr << "Could not initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_GameController* controller = nullptr;

    // Search for available controllers
    for (int i = 0; i < SDL_NumJoysticks(); ++i)
    {
        if (SDL_IsGameController(i))
        {
            controller = SDL_GameControllerOpen(i);
            if (controller)
            {
                std::cout << "Controller connected!" << std::endl;
                break;
            }
            else
            {
                std::cerr << "Could not open game controller: " << SDL_GetError() << std::endl;
            }
        }
    }

    if (controller == nullptr)
    {
        std::cerr << "No game controller found." << std::endl;
        SDL_Quit();
        return -1;
    }

    dma_handler dma_object;  // Assuming you have a constructor for dma_handler

    bool running = true;
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
            else if (e.type == SDL_CONTROLLERBUTTONDOWN)
            {
                switch (e.cbutton.button)
                {
                    case SDL_CONTROLLER_BUTTON_DPAD_UP:
                        std::cout << "Moving forward" << std::endl;
                        move_forward(128, dma_object);  // Example power level
                        break;

                    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                        std::cout << "Moving backward" << std::endl;
                        move_backward(128, dma_object);  // Example power level
                        break;

                    case SDL_CONTROLLER_BUTTON_B:
                        std::cout << "Stopping motors" << std::endl;
                        // Add a function to stop the motors if needed
                        break;
                }
            }
        }

        // Add a small delay to avoid busy-waiting
        SDL_Delay(16);
    }

    if (controller)
    {
        SDL_GameControllerClose(controller);
    }

    SDL_Quit();
    return 0;
}