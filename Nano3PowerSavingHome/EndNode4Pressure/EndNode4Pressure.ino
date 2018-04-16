/**
    PressureDetectingNode on the bed

*/
const int OneSec = 1000;
const int HalfSec = 500;
const char *WAKEUP = "wakeup4";
const char *COMMAND_ERROR = "commanderror";
const char *POWER = "power";
const char *POWER_ON = "power4_on";
const int STANDARD_PRESSURE = 200;
int sensorPin1 = A0;
int sensorPin2 = A1;
int sensorPin3 = A2;
int sensorPin4 = A3;

int powerPin1 = 2;`
int powerPin2 = 3;
int powerPin3 = 4;
int powerPin4 = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
  pinMode(sensorPin4, INPUT);
  pinMode(powerPin1,OUTPUT);
  pinMode(powerPin2,OUTPUT);
  pinMode(powerPin3,OUTPUT);
  pinMode(powerPin4,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    delay(20);
    process();
  }
}
/**
   process UART and comand
*/
void process() {
  int j = 0;
  char command[10];
  while (Serial.available() > 0) {  //read command
    command[j] = Serial.read();
    j++;
  }
  command[j] = '\0';
  if (strcmp(command, WAKEUP) == 0) {                        //start detecting
    bool hasHuman = detectSec(5);
    if (hasHuman){
      Serial.write("yes");                //write to serial to notify control node
      digitalWrite(LED_BUILTIN,HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN,LOW);
    }
    else Serial.write("no");
  } else if (strcmp(command, POWER) == 0) {
    Serial.write(POWER_ON);
  }
  else Serial.write(COMMAND_ERROR);
  Serial.flush();                   //clear repeated command
}
/**
   detecting mankind in Seconds
*/
bool detectSec(int s) {
  int i, times = 0;
  int totalpressure = 0;
  int pressure[4] = {0};
  digitalWrite(powerPin1,HIGH);
  digitalWrite(powerPin2,HIGH);
  digitalWrite(powerPin3,HIGH);
  digitalWrite(powerPin4,HIGH);
  for (i = 0; i < s; i++) {
    pressure[0] += analogRead(sensorPin1);
    pressure[1] += analogRead(sensorPin2);
    pressure[2] += analogRead(sensorPin3);
    pressure[3] += analogRead(sensorPin4);
    delay(OneSec);
  }
  for (i = 0; i < 4; i++) {
    pressure[i] /= s;
    totalpressure += pressure[i];
  }
  digitalWrite(powerPin1,LOW);
  digitalWrite(powerPin2,LOW);
  digitalWrite(powerPin3,LOW);
  digitalWrite(powerPin4,LOW);
  if (totalpressure > STANDARD_PRESSURE)
    return true;
  else return false;
}
