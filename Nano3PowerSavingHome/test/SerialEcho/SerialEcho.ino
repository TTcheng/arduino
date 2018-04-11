
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  char msg[10];
  if(Serial.available()>0){
    delay(20);
    int j = 0;
    while(Serial.available()>0){
      msg[j] = Serial.read();
      j++;
    }
    msg[j++]='2';
    msg[j]='\0';
    Serial.write(msg);
  }
}
