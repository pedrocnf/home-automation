

#include <ESP8266WiFi.h> 
#include <PubSubClient.h> 
#include <Wire.h>
#include <MPU6050.h>

const char* ssid = ".....";
const char* wifi_password = ".....";

MPU6050 mpu;
int SCL_PIN=5;
int SDA_PIN=4;

const char* mqtt_server = "192.168.0.117";
const char* mqtt_topic = "acc_norm_x";
const char* mqtt_username = "...";
const char* mqtt_password = "...";
const char* clientID = "ESP-8266";

WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); 

char acc_raw_x_char[10];
char acc_raw_y_char[10]; 
char acc_raw_z_char[10];

char acc_norm_x_char[10]; 
char acc_norm_y_char[10]; 
char acc_norm_z_char[10]; 
  
char gyro_raw_x_char[10];
char gyro_raw_y_char[10];
char gyro_raw_z_char[10];

char gyro_norm_x_char[10];
char gyro_norm_y_char[10];
char gyro_norm_z_char[10];

void setup() {


  Serial.begin(115200);

    while(!mpu.beginSoftwareI2C(SCL_PIN,SDA_PIN,MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Sensor MPU6050 nao detectado");
    delay(500);
  }

  Serial.print("Conectando");
  Serial.println(ssid);
  WiFi.begin(ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi conectado");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Conectado ao broker MQTT");
  }
  else {
    Serial.println("Falha em conectar ao broker MQTT");
  }

   checkSettings();
  
}

void loop() {
  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();
  Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro();
 
  float acc_raw_x = rawAccel.XAxis;
  float acc_raw_y = rawAccel.YAxis;
  float acc_raw_z = rawAccel.ZAxis;
 
  float acc_norm_x = normAccel.XAxis;
  float acc_norm_y = normAccel.YAxis;
  float acc_norm_z = normAccel.ZAxis;
  
  float gyro_raw_x = rawGyro.XAxis;
  float gyro_raw_y = rawGyro.YAxis;
  float gyro_raw_z = rawGyro.ZAxis;

  float gyro_norm_x = normGyro.XAxis;
  float gyro_norm_y = normGyro.YAxis;
  float gyro_norm_z = normGyro.ZAxis;
  

  
sprintf(acc_raw_x_char, "%.02f", acc_raw_x);
sprintf(acc_raw_y_char, "%.02f", acc_raw_y);
sprintf(acc_raw_z_char, "%.02f", acc_raw_z);
sprintf(acc_norm_x_char, "%.02f", acc_norm_x);
sprintf(acc_norm_y_char, "%.02f", acc_norm_y);
sprintf(acc_norm_z_char, "%.02f", acc_norm_z);
sprintf(gyro_raw_x_char, "%.02f", gyro_raw_x);
sprintf(gyro_raw_y_char, "%.02f", gyro_raw_y);
sprintf(gyro_raw_z_char, "%.02f", gyro_raw_z);
sprintf(gyro_norm_x_char, "%.02f", gyro_norm_x);
sprintf(gyro_norm_y_char, "%.02f", gyro_norm_y);
sprintf(gyro_norm_z_char, "%.02f", gyro_norm_z);

client.publish("acc_raw_x", acc_raw_x_char);
client.publish("acc_raw_y", acc_raw_y_char);
client.publish("acc_raw_z", acc_raw_z_char);
client.publish("acc_norm_x", acc_norm_x_char);
client.publish("acc_norm_y", acc_norm_y_char);
client.publish("acc_norm_z", acc_norm_z_char);
client.publish("gyro_raw_x", gyro_raw_x_char);
client.publish("gyro_raw_y", gyro_raw_y_char);
client.publish("gyro_raw_z", gyro_raw_z_char);
client.publish("gyro_norm_x", gyro_norm_x_char);
client.publish("gyro_norm_y", gyro_norm_y_char);
client.publish("gyro_norm_z", gyro_norm_z_char);


delay(50);
 
  
}

void checkSettings()
{
  Serial.println();
  
  Serial.print(" * Sleep Mode:            ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
  
  Serial.print(" * Clock Source:          ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  Serial.print(" * Accelerometer:         ");
  switch(mpu.getRange())
  {
    case MPU6050_RANGE_16G:            Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G:             Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G:             Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G:             Serial.println("+/- 2 g"); break;
  }  

  Serial.print(" * Accelerometer offsets: ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getAccelOffsetZ());
  
  Serial.println();
}
