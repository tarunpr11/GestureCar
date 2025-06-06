#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CSN_GPIO    7
#define CE_GPIO     8

const int in1 = 2; 
const int in2 = 3;  // Controls motor 1 direction
const int in3 = 4; 
const int in4 = 5;  // Controls motor 2 direction
const int speedPin1 = 9; // PWM pin for motor 1 speed
const int speedPin2 = 10; // PWM pin for motor 2 speed

// Hardware configuration
RF24 radio(CE_GPIO, CSN_GPIO);                           // Set up nRF24L01 radio on SPI bus plus pins 7 & 8

const byte channel = 0x76; // Your desired channel (modify if needed)
unsigned char Received_Command = 0;
unsigned char Rx_Array[2];

void setup() {
  Serial.begin(115200);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Set speed control pins as outputs (PWM)
  pinMode(speedPin1, OUTPUT);
  pinMode(speedPin2, OUTPUT);
  radio.setDataRate(RF24_250KBPS); 
  radio.begin();
  radio.openReadingPipe(1, channel);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  Serial.println("START");

}

void loop()
{
  if (radio.available())    // If the NRF240L01 module received data
  {  
    delay(250);
    radio.read(&Received_Command, 1);
    // radio.read(&Rx_Array, 2);
    // Received_Command = Rx_Array[0];
    Serial.println(Received_Command);
    radio.enableAckPayload();
  }

/***************** Speed control Logic ********************/
  if (Received_Command == 1){
    Serial.println("forward");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

  // Set motor speed (0-255)
    analogWrite(speedPin1, 255); // Adjust value for desired speed (0 = stopped, 255 = full speed)
    analogWrite(speedPin2, 255);
  }
  if (Received_Command == 2){
    Serial.println("backward");
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

  // Set motor speed (0-255)
    analogWrite(speedPin1, 255); // Adjust value for desired speed (0 = stopped, 255 = full speed)
    analogWrite(speedPin2, 255);
  }
  if (Received_Command == 3){
    Serial.println("left");
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

  // Set motor speed (0-255)
    analogWrite(speedPin1, 255); // Adjust value for desired speed (0 = stopped, 255 = full speed)
    analogWrite(speedPin2, 255);
  }
  if (Received_Command == 4){
    Serial.println("right");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

  // Set motor speed (0-255)
    analogWrite(speedPin1, 255); // Adjust value for desired speed (0 = stopped, 255 = full speed)
    analogWrite(speedPin2, 255);
  }

}
