#include <gtk/gtk.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <thread>
#include <atomic>
#include <unistd.h>
#include <iostream>
#include <iomanip> // for std::fixed and std::setprecision
#include "ISM330DHCX/ISM330DHCX.h"
#include "BME280/BME280.h"

// Global variables for GTK+ widgets
GtkWidget *image_widget;
std::atomic<bool> running(true);

// Function to capture frames from the camera and overlay sensor data
void update_camera_feed() {
    cv::VideoCapture camera(0);
    if (!camera.isOpened()) {
        std::cerr << "Error: Could not access the camera." << std::endl;
        return;
    }

    // Initialize sensors
    BME280 bme;
    ISM330DHCX imu;
    bme.init();
    imu.init();

    while (running) {
        cv::Mat frame;
        camera >> frame;  // Capture frame

        if (frame.empty()) {
            std::cerr << "Error: Failed to capture image." << std::endl;
            break;
        }

        // Resize frame to fit the 480x360 window size
        cv::resize(frame, frame, cv::Size(480, 360));

        // Get sensor data
        int32_t temp = bme.get_temp();
        std::string temp_text = "Temp: " + std::to_string(temp / 100) + "." + std::to_string(temp % 100) + " C";

        std::string hum_text = "Humidity: " + std::to_string(bme.get_hum()) + " %RH";
        std::string press_text = "Pressure: " + std::to_string(bme.get_press()) + " Pa";

        ISM330DHCX::GyroData gyro = imu.get_gyro();
        std::string gyro_text = "Gyro: [" + std::to_string(gyro.x) + ", " + std::to_string(gyro.y) + ", " + std::to_string(gyro.z) + "] rads/s";

        ISM330DHCX::AccelData accel = imu.get_accel();
        std::string accel_text = "Accel: [" + std::to_string(accel.x) + ", " + std::to_string(accel.y) + ", " + std::to_string(accel.z) + "] m/s^2";

        // Add sensor data as overlay text on the frame
        int font = cv::FONT_HERSHEY_SIMPLEX;
        cv::Scalar text_color(255, 255, 255);  // White text
        cv::Scalar background_color(0, 0, 0);  // Black background for text

        // Reduce black box size to fit smaller text
        cv::rectangle(frame, cv::Point(10, 10), cv::Point(360, 160), background_color, cv::FILLED);

        // Reduce font size to 0.4 for smaller text and adjust spacing
        int y_offset = 30;
        cv::putText(frame, temp_text, cv::Point(20, y_offset), font, 0.4, text_color, 1);
        cv::putText(frame, hum_text, cv::Point(20, y_offset + 25), font, 0.4, text_color, 1);
        cv::putText(frame, press_text, cv::Point(20, y_offset + 50), font, 0.4, text_color, 1);
        cv::putText(frame, gyro_text, cv::Point(20, y_offset + 75), font, 0.4, text_color, 1);
        cv::putText(frame, accel_text, cv::Point(20, y_offset + 100), font, 0.4, text_color, 1);

        // Convert OpenCV Mat to GdkPixbuf to display in GTK
        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);  // Convert to RGB
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data(
            (guchar*) frame.data,
            GDK_COLORSPACE_RGB,
            false,
            8,
            frame.cols,
            frame.rows,
            frame.step,
            nullptr, nullptr
        );

        // Update the image widget with the new frame
        if (pixbuf) {
            gtk_image_set_from_pixbuf(GTK_IMAGE(image_widget), pixbuf);
            g_object_unref(pixbuf);
        }

        gtk_main_iteration_do(FALSE);
        usleep(100000);  // Sleep for 100 milliseconds (~10 FPS)
    }
    camera.release();
}

// Function to handle window close event
void on_window_destroy(GtkWidget *widget, gpointer data) {
    running = false;
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Camera Feed with Sensor Data");
    
    // Set window size to 480x360 (slightly larger)
    gtk_window_set_default_size(GTK_WINDOW(window), 480, 360);
    
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

    // Create image widget to display the camera feed
    image_widget = gtk_image_new();
    gtk_container_add(GTK_CONTAINER(window), image_widget);

    gtk_widget_show_all(window);

    // Start the camera feed in a separate thread
    std::thread camera_thread(update_camera_feed);

    // Run the GTK main loop
    gtk_main();

    // Cleanup
    running = false;
    camera_thread.join();

    return 0;
}
