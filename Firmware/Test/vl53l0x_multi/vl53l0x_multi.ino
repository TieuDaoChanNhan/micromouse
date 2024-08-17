#include <Wire.h>

#include <VL53L0X.h>

VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;
//VL53L0Xsensor3;

int pin1 = 23;
int pin2 = 25;
int pin3 = 32;
int a;
int b;
int c;



void setup()

{

  pinMode(pin1, OUTPUT);

  pinMode(pin2, OUTPUT);

  pinMode(pin3, OUTPUT);

  digitalWrite(pin2, LOW);

  digitalWrite(pin1, LOW);

  digitalWrite(pin3, LOW);

  delay(500);

  Wire.begin();

  Serial.begin(9600);



  digitalWrite(pin1, HIGH);

  sensor1.init(true);

  sensor1.setAddress((uint8_t)01);

  digitalWrite(pin2, HIGH);

  sensor2.init(true);

  sensor2.setAddress((uint8_t)02);

  digitalWrite(pin3, HIGH);

  sensor3.init(true);

  sensor3.setAddress((uint8_t)03);

  sensor1.startContinuous();

  sensor2.startContinuous();

  sensor3.startContinuous();

  
}

void loop()

{



  a = sensor1.readRangeContinuousMillimeters();

  Serial.print(a);

  Serial.print(" ");

  b = sensor2.readRangeContinuousMillimeters();

  Serial.print(b);

  Serial.print(" ");

  c = sensor3.readRangeContinuousMillimeters();

  Serial.println(c);
  //motor();
  delay(100);
}

