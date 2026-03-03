#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;

int fd = -1;

void displayInfo();

int main()
{
    std::cout << "Starting GPS program..." << std::endl;

    // Initialize WiringPi
    if (wiringPiSetup() == -1)
    {
        std::cerr << "Failed to initialize WiringPi" << std::endl;
        return 1;
    }

    // Open serial port
    fd = serialOpen("/dev/serial0", 115200);
    if (fd < 0)
    {
        std::cerr << "Unable to open serial device" << std::endl;
        return 1;
    }

    std::cout << "Serial opened successfully." << std::endl;

    // Example GPIO test (WiringPi pin numbering)
    pinMode(0, OUTPUT);
    digitalWrite(0, HIGH);
    delay(1000);
    digitalWrite(0, LOW);

    // Main loop
    unsigned long lastPrint = 0;

    while (true)
    {
        // Drain all incoming serial data
        while (serialDataAvail(fd) > 0)
        {
            gps.encode(serialGetchar(fd));
        }

        // Print every 1 second
        if (millis() - lastPrint >= 1000)
        {
            lastPrint = millis();
            displayInfo();
            serialFlush(fd); // Clear the serial buffer after processing
        }

        delay(1); // tiny yield to CPU
    }

    serialClose(fd);
    return 0;
}

void displayInfo()
{
    std::cout << "Satellites: "<< gps.satellites.value()<< " | HDOP: "<< gps.hdop.hdop();
    if (gps.location.isValid())
    {
        std::cout << " | Lat: "<< gps.location.lat()<< " | Lng: "<< gps.location.lng();
    }
    else
    {
        std::cout << " | Location: INVALID";
    }

    std::cout << std::endl;
}