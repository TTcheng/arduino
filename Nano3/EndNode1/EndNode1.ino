/**
 *  McrowaveHumanDetectingNode in the room
 *  
 */
const int OneSec = 1000;
const int HalfSec = 500;
const char *COMMAND = "wakeup";
const char *COMMAND_ERROR = "commanderror";
int sensorPin = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    delay(20);
    process();
  }
}
/**
 * process UART and comand
 */
void process(){
  int j=0;
  char command[10];
  while(Serial.available()>0){      //read command
      command[j] = Serial.read();
      j++;
  }
  command[j]='\0';
  if(isCommand(command)){                             //start detecting
    bool hasHuman = detectSec(30);
    if(hasHuman)
      Serial.write("yes");                //write to serial to notify control node
    else Serial.write("no");
    Serial.flush();                   //clear repeated command
  }
  else Serial.write(COMMAND_ERROR);
}
bool isCommand(char cmd[]){
  if(strcmp(cmd,COMMAND)==0)
    return true;
  else return false;
}
/**
 * detecting mankind in Seconds
 */
bool detectSec(int s){
  int i,var1,times=0;
  for(i=0;i<s;i++){
    var1 = digitalRead(sensorPin);
    if(var1==HIGH){
      times++;
    }
    delay(OneSec);
  }
  if(times>0) 
    return true;
  else return false;
}
