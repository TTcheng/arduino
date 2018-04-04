
//void process();
//bool isCommand(char cmd[]);
const char *COMMAND = "wakeup";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    delay(20);
    process();
  }
}
void process(){
  int j=0;
  char command[6];
  while(Serial.available()>0){      //read command
      command[j] = Serial.read();
      j++;
  }
  command[j]='\0';
//  Serial.write(command);
//  Serial.write(COMMAND);
  if(isCommand(command))
    Serial.write("yes");
  else Serial.write("no");
}
bool isCommand(char cmd[]){
  if(strcmp(cmd,COMMAND)==0)
    return true;
  else return false;
}
