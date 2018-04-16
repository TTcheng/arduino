
int sensorPin = 2;
int powerPin1 = 3;
int powerPin2 = 4;
bool clockwise = false;

int values = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  detecting();
  delay(5000);
}
void detecting() {
  if (digitalRead(sensorPin) == HIGH) {
    Serial.write("yes");
  } else {
    Serial.write("no");
  }
}

