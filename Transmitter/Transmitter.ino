#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Wire.h"
#include "MPU6050.h"

#define CSN_GPIO    8
#define CE_GPIO     7

// Hardware configuration
RF24 radio(CE_GPIO, CSN_GPIO);                           // Set up nRF24L01 radio on SPI bus plus pins 7 & 8
MPU6050 accelgyro;

int16_t ax, ay, az; // x-axis and y-axis values, for this application z-axis is not needed.
int16_t gx, gy, gz; // these values are not used, just declaring to pass in the function.

// #define TX_ENABLE_KEY     2
// #define TX_LED            3

const byte channel = 0x76; // Your desired channel (modify if needed)
int Pot_Val_Y = 0,Pot_Val_X = 0, Up_key = 0, Dn_key = 0, Left_key = 0, Right_key = 0;
unsigned char Tx_command = 0,Speed_index = 0,Tx_Enable_Flag = 0,TX_Key_Pressed = 0;
unsigned char Tx_Array[2];



void setup() {
  Serial.begin(115200);
  // pinMode(TX_ENABLE_KEY, INPUT_PULLUP);
  // pinMode(TX_LED, OUTPUT);
  radio.setDataRate(RF24_250KBPS); 
  radio.begin();
  radio.openWritingPipe(channel);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  // radio.write(&Tx_command, sizeof(Tx_command));
  
  Wire.begin();
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  Tx_Array[0] = 0;
  Tx_Array[1] = 0;
  // radio.setAutoAck(false);
}

void loop()
{
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // we are getting all 6 value from MPU6050 i.e. 3 Accelerometer values and 3 Gyro values viz. ax,ay,az,gx,gy and gz.


  if((ay<=-4000)||((ay>=4000)))
  {
    //Serial.print("A , ");         // uncomment A,B,C..... if you are debugging
    if((ax>=-4000)||((ax<=4000)))
    {
      // Serial.print("B , ");
      if((ay<=-4000))
      {
          //Serial.print("C , ");
          Tx_command = 1;                     // forward
          Speed_index = (ay + 4000)/-2000 + 1; // more the negative value more the speed. ay valu varies from -16384 to +16384 same for ax and others.
          if(Speed_index>5)
          {
            Speed_index = 5;  
          }
      }

      if((ay>=4000))
      {
          //Serial.print("D , ");
          Tx_command = 2;                     // Backward
          Speed_index = (ay - 4000)/2000 + 1; // more the positive value more the speed. ay valu varies from -16384 to +16384 same for ax and others.
          if(Speed_index>5)
          {
            Speed_index = 5;  
          }
      }
    }
    else
    {
        //Serial.print("E , ");
        Tx_command = 0;
        Speed_index = 0;
    } 
  }
  else if((ax<=-4000)||((ax>=4000)))
  {
    //Serial.print("F , ");
    if((ay>=-4000)||((ay<=4000)))
    {
      //Serial.print("G , ");
      if((ax<=-4000))
      {
          //Serial.print("H , ");
          Tx_command = 4;                     // Right
          Speed_index = (ax + 4000)/-2000 + 1; // more the negative value more the speed. ax valu varies from -16384 to +16384 same for ay and others.
          if(Speed_index>5)
          {
            Speed_index = 5;  
          }
      }

      if((ax>=4000))
      {
          //Serial.print("I , ");
          Tx_command = 3;                     // Left
          Speed_index = (ax - 4000)/2000 + 1; // more the positive value more the speed. ax valu varies from -16384 to +16384 same for ay and others.
          if(Speed_index>5)
          {
            Speed_index = 5;  
          }
      }
    }
    else
    {
        //Serial.print("J , ");
        Tx_command = 0;
        Speed_index = 0;
    } 
  }
  else
  {
      //Serial.print("K , ");
      Tx_command = 0;
      Speed_index = 0;
  }
  Serial.println(Tx_command);
  // Serial.print(" , ");
  // Serial.println(Speed_index);
  Tx_Array[0] = Tx_command;
  // Tx_Array[1] = Speed_index;
  if(radio.write(&Tx_command, 1)){
    Serial.println("Sent");
  }    // 1st byte = Direction , 2nd Byte = Speed
  
  delay(500);
}
