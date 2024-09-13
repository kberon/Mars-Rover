#include <gtk/gtk.h>
#include <string> 
#include "ISM330DHCX/ISM330DHCX.h"
#include "BME280/BME280.h"

// Global variables for GTK+ widgets
GtkWidget *temp_label;
GtkWidget *hum_label;
GtkWidget *press_label;
GtkWidget *gyro_label;
GtkWidget *accel_label;

// Function to update GUI with sensor data
void update_sensor_data() {
    BME280 bme = BME280();
    ISM330DHCX imu = ISM330DHCX();
    bme.init();
    imu.init();

    while (true) {
        int32_t T = bme.get_temp();
        std::string temp_text = "Temperature: " + std::to_string(T / 100) + "." + std::to_string(T % 100) + " C";
        gtk_label_set_text(GTK_LABEL(temp_label), temp_text.c_str());

        std::string hum_text = "Humidity: " + std::to_string(bme.get_hum()) + " %RH";
        gtk_label_set_text(GTK_LABEL(hum_label), hum_text.c_str());

        std::string press_text = "Pressure: " + std::to_string(bme.get_press()) + " Pa";
        gtk_label_set_text(GTK_LABEL(press_label), press_text.c_str());

        ISM330DHCX::GyroData gyro = imu.get_gyro();
        std::string gyro_text = "Gyro: [" + std::to_string(gyro.x) + ", " + std::to_string(gyro.y) + ", " + std::to_string(gyro.z) + "] rads/s";
        gtk_label_set_text(GTK_LABEL(gyro_label), gyro_text.c_str());

        ISM330DHCX::AccelData accel = imu.get_accel();
        std::string accel_text = "Accel: [" + std::to_string(accel.x) + ", " + std::to_string(accel.y) + ", " + std::to_string(accel.z) + "] m/s^2";
        gtk_label_set_text(GTK_LABEL(accel_label), accel_text.c_str());

        // Update every 3 seconds
        gtk_main_iteration_do(FALSE);
        g_usleep(3000000); // Sleep for 3 seconds
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Sensor Data");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    temp_label = gtk_label_new("Temperature: N/A");
    gtk_box_pack_start(GTK_BOX(vbox), temp_label, TRUE, TRUE, 0);

    hum_label = gtk_label_new("Humidity: N/A");
    gtk_box_pack_start(GTK_BOX(vbox), hum_label, TRUE, TRUE, 0);

    press_label = gtk_label_new("Pressure: N/A");
    gtk_box_pack_start(GTK_BOX(vbox), press_label, TRUE, TRUE, 0);

    gyro_label = gtk_label_new("Gyro: N/A");
    gtk_box_pack_start(GTK_BOX(vbox), gyro_label, TRUE, TRUE, 0);

    accel_label = gtk_label_new("Accel: N/A");
    gtk_box_pack_start(GTK_BOX(vbox), accel_label, TRUE, TRUE, 0);

    gtk_widget_show_all(window);

    // Start sensor data update in a separate thread
    g_thread_new(NULL, (GThreadFunc)update_sensor_data, NULL);

    gtk_main();

    return 0;
}
