// Nehan Mohammed/Sushaan Kathirgamar           Hand Gesture-Controlled Car Transmitter             January 18/24

// This Arduino code uses the MPU6050 accelerometer to detect tilt along the y and z axes.
//  The degree of tilt determines motion states for Speed_index, which is sent via HC-05 Bluetooth to reciever. 

#include "Wire.h"
#include "MPU6050.h"
int Tilt_Activation = 8000; 
// Threshold value of the accelerometer for motion activation. 
// Adjust this value based on the desired sensitivity for activation.

int16_t ax, ay, az; 
// Accelerometer values (x, y, z). X-axis is not needed for this application.
int16_t gx, gy, gz; 
// Gyroscope values (x, y, z). These values are declared but not used in this code.
int Speed_index; 
// Speed value sent to the receiver for controlling motion.

void setup() {
    Serial.begin(38400);
    Wire.begin();
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize(); // Assuming accelgyro is declared and initialized somewhere in your code.
}

void loop() {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); 
    // Retrieving 6 values from MPU6050 - 3 Accelerometer (ax, ay, az) and 3 Gyroscope (gx, gy, gz).

    if ((ay <= -Tilt_Activation) || (ay >= Tilt_Activation)) // Forward/Backward motion 
    {
        if ((az >= -Tilt_Activation) || (az <= Tilt_Activation)) // Checking z-value of accelerometer.
        {
            if (ay <= -Tilt_Activation) {
                Speed_index = 1;  // Forward
            }
            else if (ay >= Tilt_Activation) {
                Speed_index = 2;  // Backward
            }
        }
        else {
            Speed_index = 0; // Stop
        } 
    }
    else if ((az <= -Tilt_Activation) || (az >= Tilt_Activation)) // Right/Left motion
    {
        if ((ay >= -Tilt_Activation) || (ay <= Tilt_Activation)) // Checking y-value of accelerometer.
        {
            if (az <= -Tilt_Activation) {
                Speed_index = 3;  // Right
            }
            else if (az >= Tilt_Activation) {
                Speed_index = 4;  // Left
            }
        }
        else {
            Speed_index = 0; // Stop
        }
    }
    else {
        Speed_index = 0; // Stop
    }

    Serial.write(Speed_index); //send speed value to reciever
    delay(10);
}
