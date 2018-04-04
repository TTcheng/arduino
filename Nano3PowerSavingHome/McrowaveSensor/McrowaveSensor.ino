
int sensorPin = 2;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(sensorPin,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(sensorPin)==HIGH){
    digitalWrite(LED_BUILTIN,HIGH);
    Serial.println(true);
    delay(1000);
    digitalWrite(LED_BUILTIN,LOW);
  }else{
    delay(100);
  }
}
