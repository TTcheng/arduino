/**
    McrowaveHumanDetectingNode in the room

*/
const int OneSec = 1000;
const int HalfSec = 500;
const char *WAKEUP = "wakeup";
const char *COMMAND_ERROR = "commanderror";
const char *POWER = "power";
const char *POWER_ON = "power1_on";
int sensorPin = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);
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
    bool hasHuman = detectSec(30);
    if (hasHuman)
      Serial.write("yes");                //write to serial to notify control node
    else Serial.write("no");
  } else if (strcmp(command, POWER) == 0) {
    Serial.write(POWER_ON);
  } else Serial.write(COMMAND_ERROR);
  Serial.flush();                   //clear repeated command
}
/**
   detecting mankind in Seconds
*/
bool detectSec(int s) {
  int i, var1, times = 0;
  for (i = 0; i < s; i++) {
    var1 = digitalRead(sensorPin);
    if (var1 == HIGH) {
      times++;
    }
    delay(OneSec);
  }
  if (times > 0)
    return true;
  else return false;
}
