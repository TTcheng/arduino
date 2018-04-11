/**
    Test
    PressureDetectingNode on the bed
*/
const int OneSec = 1000;
const int HalfSec = 500;
const int STANDARD_PRESSURE = 1000;
int sensorPin1 = A0;
int sensorPin2 = A1;
int sensorPin3 = A2;
int sensorPin4 = A3;

int powerPin1 = 2;
int powerPin2 = 3;
int powerPin3 = 4;
int powerPin4 = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
  pinMode(sensorPin4, INPUT);
  pinMode(powerPin1, OUTPUT);
  pinMode(powerPin2, OUTPUT);
  pinMode(powerPin3, OUTPUT);
  pinMode(powerPin4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  detecting();
  delay(OneSec);
}

/**
   detecting mankind in Seconds
*/
bool detecting() {
  int i, times = 0;
  int totalpressure = 0;
  int pressure[4];// = {0};
  //start sensor power supply
  digitalWrite(powerPin1, HIGH);
  digitalWrite(powerPin2, HIGH);
  digitalWrite(powerPin3, HIGH);
  digitalWrite(powerPin4, HIGH);
  //read sensor data and output to Serial
  pressure[0] = analogRead(sensorPin1);
  Serial.print(pressure[0]);
  Serial.println();
  pressure[1] = analogRead(sensorPin2);
  Serial.print(pressure[1]);
  Serial.println();
  pressure[2] = analogRead(sensorPin3);
  Serial.print(pressure[2]);
  Serial.println();
  pressure[3] = analogRead(sensorPin4);
  Serial.print(pressure[3]);
  Serial.println();

  Serial.print(pressure[0] + pressure[1] + pressure[2] + pressure[3]); //all
  Serial.println();
  Serial.println();
  //stop sensor power supply
  digitalWrite(powerPin1, LOW);
  digitalWrite(powerPin2, LOW);
  digitalWrite(powerPin3, LOW);
  digitalWrite(powerPin4, LOW);
}


//int sensorPin = A0;
//int pressValue = 0;
//void setup() {
//  // put your setup code here, to run once:
//  Serial.begin(9600);
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  pressValue = analogRead(sensorPin);
//  Serial.println(pressValue);
//  delay(500);
//}
