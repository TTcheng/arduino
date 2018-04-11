
int sensorPin = 2;
int powerPin1 = 3;
int powerPin2 = 4;
bool clockwise = false;

int values = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(powerPin1, OUTPUT);
  pinMode(powerPin2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  detecting();
  delay(5000);
}
void detecting() {
  values = 0;
  if (clockwise) {
    digitalWrite(powerPin1, HIGH);
    digitalWrite(powerPin1, LOW);
  } else {
    digitalWrite(powerPin1, LOW);
    digitalWrite(powerPin1, HIGH);
  }
  int i;
  for (i = 0; i < 10; i++) {
    delay(1000);
    if (digitalRead(sensorPin) == HIGH) {
      values++;
    }
  }
  clockwise = !clockwise;
  digitalWrite(powerPin1, LOW);
  digitalWrite(powerPin1, LOW);

  if (values > 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.write("Human");
    delay(10000);
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    Serial.write("None");
    delay(10000);

  }
  Serial.println();
}

