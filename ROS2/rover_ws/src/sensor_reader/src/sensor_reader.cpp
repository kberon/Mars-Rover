#include <iostream>
#include <iomanip> // for std::fixed and std::setprecision
#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include "ISM330DHCX/ISM330DHCX.h"
#include "BME280/BME280.h"

using namespace std::chrono_literals;

class SensorReaderNode : public rclcpp::Node {
public:
    SensorReaderNode() : Node("sensor_reader_node") {
        temperature_pub_ = this->create_publisher<std_msgs::msg::Float32>("temperature", 10);
        humidity_pub_ = this->create_publisher<std_msgs::msg::Float32>("humidity", 10);
        pressure_pub_ = this->create_publisher<std_msgs::msg::Float32>("pressure", 10);
        gyro_pub_ = this->create_publisher<std_msgs::msg::Float32MultiArray>("gyro", 10);
        accel_pub_ = this->create_publisher<std_msgs::msg::Float32MultiArray>("accel", 10);

        timer_ = this->create_wall_timer(3000ms, std::bind(&SensorReaderNode::readSensors, this));
        
        bme.init();
        imu.init();
    }

private:
    void readSensors() {
        // Read Temperature
        auto temp_msg = std_msgs::msg::Float32();
        int32_t T = bme.get_temp();
        temp_msg.data = T / 100.0;
        temperature_pub_->publish(temp_msg);

        // Read Humidity
        auto hum_msg = std_msgs::msg::Float32();
        hum_msg.data = bme.get_hum();
        humidity_pub_->publish(hum_msg);

        // Read Pressure
        auto press_msg = std_msgs::msg::Float32();
        press_msg.data = bme.get_press();
        pressure_pub_->publish(press_msg);

        // Read Gyroscope
        ISM330DHCX::GyroData gyro = imu.get_gyro();
        auto gyro_msg = std_msgs::msg::Float32MultiArray();
        gyro_msg.data = {gyro.x, gyro.y, gyro.z};
        gyro_pub_->publish(gyro_msg);

        // Read Accelerometer
        ISM330DHCX::AccelData accel = imu.get_accel();
        auto accel_msg = std_msgs::msg::Float32MultiArray();
        accel_msg.data = {accel.x, accel.y, accel.z};
        accel_pub_->publish(accel_msg);
    }

    BME280 bme;
    ISM330DHCX imu;

    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr temperature_pub_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr humidity_pub_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr pressure_pub_;
    rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr gyro_pub_;
    rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr accel_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SensorReaderNode>());
    rclcpp::shutdown();
    return 0;
}
