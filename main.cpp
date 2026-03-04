#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>
// #include <TinyGPS++.h>
#include <RF24/RF24.h>
#include "nrf.h"

void recieve_data();
// TinyGPSPlus gps;

#define CE_PIN 6
#define CSN_PIN 10
#define PAYLOAD_SIZE 32
RF24 radio(CE_PIN, CSN_PIN); // CE, CSN pins for nRF24L01?S
Commands data_in;
int fd = -1;

// void displayInfo();
void cleanup();
// #define ADDRESS 0xFF
// const uint8_t address[6] = "00001";
const uint8_t address =0xFF;
int main()
{
    wiringPiSetup();
    // wiringPiSetupGpio();
    pinMode(0,OUTPUT);
    std::cout << "Starting GPS and RF24 communication..." << std::endl;
    if (!radio.begin()) {
        std::cout << "radio hardware is not responding!!" << std::endl;
        cleanup();
        return 0; // quit now
    }
    radio.setAutoAck(false);
    radio.setPALevel(RF24_250KBPS);
    radio.openReadingPipe(1, address);
    radio.startListening();

    digitalWrite(0,HIGH);

    while (true)
    {
        recieve_data();
        delay(10);
    }

    cleanup();

    return 0;
}

void cleanup()
{
    digitalWrite(0,LOW);
    digitalWrite(CE_PIN,LOW);
    digitalWrite(CSN_PIN,LOW);
}


void recieve_data(){
    if (radio.available()) {
        radio.read(&data_in, sizeof(data_in));
        std::cout << "Received data: " << (int)data_in.JOYSTICK_R_X << " " << (int)data_in.JOYSTICK_R_Y << " " << (int)data_in.BUTTON_A << " " << (int)data_in.BUTTON_B << std::endl;
    }
}

// void displayInfo()
// {
//     std::cout << "Satellites: "<< gps.satellites.value()<< " | HDOP: "<< gps.hdop.hdop();
//     if (gps.location.isValid())
//     {
//         std::cout << " | Lat: "<< gps.location.lat()<< " | Lng: "<< gps.location.lng();
//     }
//     else
//     {
//         std::cout << " | Location: INVALID";
//     }

//     std::cout << std::endl;
// }