int powerPin1 = 2;
int powerPin2 = 3;

bool status__ = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(powerPin1,OUTPUT);
  pinMode(powerPin2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(status__){
    digitalWrite(powerPin1,HIGH);
    digitalWrite(powerPin2,LOW);
    delay(5000);
  }else{
    digitalWrite(powerPin1,LOW);
    digitalWrite(powerPin2,HIGH);
    delay(5000);
  }
  status__ = !status__;
  digitalWrite(powerPin1,LOW);
  digitalWrite(powerPin2,LOW);
  delay(10000);//wait for stopping turntable 
  
}
