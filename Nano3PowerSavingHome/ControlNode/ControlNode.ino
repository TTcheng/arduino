/**
   ControlNode besides the door with infrared ray
*/
const char *WAKE_UP = "wakeup";
const char *COMMAND_ERROR = "commanderror";
const char *HUMAN_DETECTED = "yes";
const char *HUMAN_UNDETECTED = "no";
const char *POWER = "power";
const char *POWER1_ON = "power1_on";
const char *POWER2_ON = "power2_on";
const char *POWER3_ON = "power3_on";
const char *POWER4_ON = "power4_on";

const bool HUMAN_IN = true;
const bool HUMAN_NONE = false;
const bool EP_PWR_ON = true;
const bool EP_PWR_OFF = false;

const int ALL_DENIED = 4;
const int ALL_RECIEVED = 4;
const int ONE_SEC = 1000;
const int CHECK_TIME = 180; //check response in 3 min after power query sended
int sensorPin = 2;   //infrared ray reciever endpotint
int timer = 0;
int denies = 0;     //the quantity of HUMAN_UNDETECTED responses
int responses = 0;  //responses >= denies
bool power_status[5] = {EP_PWR_ON};
bool power_query_in_waiting = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if (detecting()) {    //detected door event
    turnLightON();      //turn off the light power
    wakeup();           //wakeup end nodes
    //then delay 30 s to avoid repeatedly doorEvent
    delay(30 * ONE_SEC);
  }
  if (Serial.available() > 0) { //msg event
    delay(20);
    if (processFedback() == HUMAN_NONE) {
      turnLightOFF();      //turn off the light power
    }
  }
  if (timer > CHECK_TIME) { //check power response
    checkPowerResponse();
    timer = 0;              //reset timer
  }
  delay(ONE_SEC);
  timer++;
}

bool processFedback() {
  int j = 0;
  char msg[20];
  while (Serial.available() > 0) {  //read feedback
    msg[j] = Serial.read();
    j++;
  }
  msg[j] = '\0';                     //end char of string
  //handle feedback
  if (strcmp(msg, HUMAN_DETECTED) == 0) {   //human detected
    responses++;
  } else if (strcmp(msg, HUMAN_UNDETECTED) == 0) { //human undetected
    responses++;
  }
  //if power_query_in_waiting change power status
  if (power_query_in_waiting) {
    if (strcmp(msg, POWER1_ON) == 0) {
      power_status[1] = EP_PWR_ON;
    } else if (strcmp(msg, POWER2_ON) == 0) {
      power_status[2] = EP_PWR_ON;
    } else if (strcmp(msg, POWER3_ON) == 0) {
      power_status[3] = EP_PWR_ON;
    } else if (strcmp(msg, POWER4_ON) == 0) {
      power_status[4] = EP_PWR_ON;
    }
  }
  //exist none-response end point
  if (responses < ALL_RECIEVED) {
    powerQuery();
  }
  //nonexistent end points found human
  if (denies == ALL_DENIED) {
    return HUMAN_NONE;
  } else return HUMAN_IN;
}
void powerQuery() {
  Serial.write(POWER);            //send query command
  power_query_in_waiting = true;  //power query in waiting
  power_status[1] = EP_PWR_OFF;   //reset power status
  power_status[2] = EP_PWR_OFF;
  power_status[3] = EP_PWR_OFF;
  power_status[4] = EP_PWR_OFF;
  timer = 0;
}
void checkPowerResponse() {
  int itr = 1;
  while (itr < 5) {
    if (power_status[itr] == EP_PWR_OFF) {
      notifyBatteryReplace(itr);
    }
    itr++;
  }
  power_query_in_waiting = false;
}
void notifyBatteryReplace(int ep_id) {
  //
}
void turnLightOFF() {
  digitalWrite(LED_BUILTIN, LOW);
}
void turnLightON() {
  digitalWrite(LED_BUILTIN, HIGH);
}
void wakeup() {
  Serial.write(WAKE_UP);
  responses = 0;
  denies = 0;
}
bool detecting() {
  if (digitalRead(sensorPin) == HIGH) {
    return true;
  }
  return false;
}

