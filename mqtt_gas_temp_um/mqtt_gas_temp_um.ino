
//SCL no pino D1
//SDA no pino D2


#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "EspMQTTClient.h"

EspMQTTClient client(
  "Skynet",
  "91709152",
  "skynet-iot.com.br",  // MQTT Broker server ip
  "skynet-mqtt",   // Can be omitted if not needed
  "Gliese581a",   // Can be omitted if not needed
  "Esp",     // Client name that uniquely identify your device
  8084              // The MQTT port, default to 1883. this line can be omitted
);


#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

void setup() {
    Serial.begin(9600);
    while(!Serial);   
    Serial.println(F("BME280 test"));
    unsigned status;
    status = bme.begin();  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1);
    }
    Serial.println("-- Default Test --");
    delayTime = 1000;
    Serial.println();
    
    client.enableDebuggingMessages(); 
    client.enableHTTPWebUpdater(); 
 
    }

    void onConnectionEstablished(){
      client.subscribe("mytopic/test", [](const String & payload));
      Serial.println(payload);
    }
    client.publish("mytopic/test", "This is a message"); // You can activate the retain flag by setting the third parameter to true

  
  




void printValues() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
}
