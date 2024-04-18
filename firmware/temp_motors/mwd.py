'''
This file is used to control the motors and allow the rover to change directions. 
Run this file by typing: 'python mwd.py []', with the direction in brackets.
Send w for forwards, s for backwards, a for left, d for right, and e to stop all movement.
'''

import time
from adafruit_motorkit import MotorKit
import sys

kit = MotorKit()

'''

MOTOR 1: Front right, proper forwards
MOTOR 2: Back Right, proper
MOTOR 3: Back left, inverted
MOTOR 4: Front left, inverted

'''

def main():
    kit = MotorKit()
    
    if len(sys.argv) != 2:
        print("Usage: python script.py <direction>")
        return

    direction = sys.argv[1].lower()

    if direction == "w": #straight
        print("Heading forwards")
        kit.motor1.throttle = 0.3
        kit.motor2.throttle = 0.3
        kit.motor3.throttle = -0.3
        kit.motor4.throttle = -0.3
        
    elif direction == "a": #left
        print("Heading left") 
        kit.motor1.throttle = 0.3
        kit.motor2.throttle = 0.3
        kit.motor3.throttle = 0.2
        kit.motor4.throttle = 0.2
        
    elif direction == "s":#backwards
        print("Heading backwards")
        kit.motor1.throttle = -0.3
        kit.motor2.throttle = -0.3
        kit.motor3.throttle = 0.3
        kit.motor4.throttle = 0.3
        
    elif direction == "d":#right
        print("Heading right")
        kit.motor1.throttle = -0.2
        kit.motor2.throttle = -0.2
        kit.motor3.throttle = -0.3
        kit.motor4.throttle = -0.3
        
    elif direction == "e":#stop
        kit.motor1.throttle = 0
        kit.motor2.throttle = 0
        kit.motor3.throttle = 0
        kit.motor4.throttle = 0
        

if __name__ == "__main__":
    main()
