import time
from adafruit_motorkit import MotorKit

kit = MotorKit()
kit2 = MotorKit(address = 0x61)

kit.motor1.throttle = 0
kit.motor2.throttle = 0
kit.motor3.throttle = 0
kit.motor4.throttle = 0
kit2.motor1.throttle = 0
kit2.motor4.throttle = 0