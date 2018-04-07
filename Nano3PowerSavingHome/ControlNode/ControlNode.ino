/**
* ControlNode besides the door with infrared ray
*/
const char *WAKE_UP1 = "wakeup1";
const char *WAKE_UP2 = "wakeup2";
const char *WAKE_UP3 = "wakeup3";
const char *WAKE_UP4 = "wakeup4";

const char *COMMAND_ERROR = "commanderror";
const char *HUMAN_DETECTED = "yes";
const char *HUMAN_UNDETECTED = "no";
const char *POWER = "power";
const char *POWER1_ON = "power1_on";
const char *POWER2_ON = "power2_on";
const char *POWER3_ON = "power3_on";
const char *POWER4_ON = "power4_on";

//const bool HUMAN_IN = true;
//const bool HUMAN_NONE = false;
const bool EP_PWR_ON = true;
const bool EP_PWR_OFF = false;
//const bool DOOR_OPEN = true;
//const bool DOOR_CLOSE = false;

const int DEVICES = 4;
//const int ALL_RECIEVED = 4;
const int WAKEUP_INTERVAL = 12;//wakeup next node 12 s after last node
const int ONE_SEC = 1000;
const int PWR_QUERY_TIME = 86400;
const int CHECK_TIME = 180; //check response in 3 min after power query sended
int sensorPin = 2;   //infrared ray reciever endpotint
int timer = 0;
int door_status = LOW;//????????
int wakeup_timer = 0;//time counter for wake up events
int door_event = 0; //door event queue 0 for no door event
int wakeups  = 0;   //the quantity of sended wake up commands
//int denies = 0;     //the quantity of HUMAN_UNDETECTED responses
//int responses = 0;  //responses >= denies
bool human_detected = false;
bool in_wakingup = false;
bool power_status[5] = {EP_PWR_ON};
bool power_query_in_waiting = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  detectDoorEvent();
  processDoorEvent();
  if (Serial.available() > 0) { //msg event
    delay(20);
    processFedback();
  }
  if (power_query_in_waiting && timer > CHECK_TIME) {
    checkPowerResponse();
    timer = 0;              //reset timer
  }
  if (timer > PWR_QUERY_TIME) {
    powerQuery();
    timer = 0;
  }
  delay(ONE_SEC);
  timer++;
}
void processDoorEvent() {
  if (door_event > 0) {
    door_event --;
    turnLightON();    //turn off the light power
    //    responses = 0;
    //    denies = 0;
    in_wakingup = true;
    human_detected = false;
    wakeup();           //start waking up end nodes
  }
  if (in_wakingup) {
    if (wakeup_timer > WAKEUP_INTERVAL) {//time out and no response: wake up next  or  end of wake up.if has response ,processed in fedback
      if (wakeups < DEVICES) { //human status uncertain
        wakeup();             //wake up next end node
      } else {                //no human in the room
        in_wakingup = false;  //end of waking up
      }
    } else {                   //not the time
      wakeup_timer++;
    }
  }
}
void processFedback() {
  int j = 0;
  char msg[20];
  while (Serial.available() > 0) {  //read feedback
    msg[j] = Serial.read();
    j++;
  }
  msg[j] = '\0';                     //end char of string
  //handle feedback
  if (strcmp(msg, HUMAN_DETECTED) == 0) {   //human detected
    //    responses++;
    human_detected = true;
    in_wakingup = false;              //end of waking up
  } else if (strcmp(msg, HUMAN_UNDETECTED) == 0) { //human undetected
    //    responses++;
    if (in_wakingup && wakeups < DEVICES) {      //human status uncertain
      wakeup();                                //wake up next end node
    }
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
  /*
    //exist none-response end point
    if (responses < ALL_RECIEVED) {
    powerQuery();
    }*/


  //  if (denies == DEVICES) { //All denied
  //    return HUMAN_NONE;
  //  } else return HUMAN_IN;
}
void powerQuery() {
  Serial.write(POWER);            //send query command
  power_query_in_waiting = true;  //power query in waiting
  power_status[1] = EP_PWR_OFF;   //set all devices power status (off)
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
  timer = 0;
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
  wakeup_timer = 0;
  wakeups++;
  switch (wakeups) {
    case 0: Serial.write(WAKE_UP1); break;
    case 1: Serial.write(WAKE_UP2); break;
    case 2: Serial.write(WAKE_UP3); break;
    case 3: Serial.write(WAKE_UP4); break;
    default: break;
  }
}
void detectDoorEvent() {
  int sensorValue = digitalRead(sensorPin); //LOW 有遮挡物，门开 HIGH 无遮挡物，门关
  if (sensorValue != door_status) {
    door_status = sensorValue;
    if (sensorValue == LOW) {  //HIGH->LOW door open
      door_event ++;           //door event detected ,add to event queue;
    } else if (sensorValue == HIGH) { //LOW -> HIGH door close
      door_event ++;
    }
  }
}

