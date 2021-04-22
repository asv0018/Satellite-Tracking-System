#include <RTClib.h>

#define NORTH HIGH
#define SOUTH LOW
/*************************************************CONFIGURATIONS ARE TO BE DONE HERE****************************************/
// CONFIGURE TO SET THE STARTING TIME TO START THE ROTATION OF MOTOR
int start_hour = 20; // MENTION START HOUR
int start_minute = 34; // MENTION START MINUTE
int start_second = 00;

// CONFIGURE THE STEP COUNT, DIRECTION AND STEPPER SPEED DELAY IN MICROSECONDS
bool DIRECTION = SOUTH; // DIRECTION
int step_count = 100; // STEP COUNT
int timer_delay = 20000000; // DELAY

/******************************************************CONFIGURATIONS END HERE**********************************************/
RTC_DS3231 rtc;

const int dirPin = 2;
const int stepPin = 3;

void setup(){
  Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  
}

void loop(){
  float angle = 0;
  DateTime now = rtc.now();
  int current_hour = now.hour();
  int current_minute = now.minute();
  int current_second = now.second();
  Serial.print("The current time is = ");
  Serial.print(current_hour);
  Serial.print(":");
  Serial.print(current_minute);
  Serial.print(":");
  Serial.println(current_second);
  if((current_hour == start_hour)&&(current_minute == start_minute)&&(current_second == start_second)){
  //if(true){
    digitalWrite(dirPin, DIRECTION);
    Serial.println("Time to track the satellite");
    for(int i=0; i <= step_count; i++){
      Serial.print("Current angle of rotation is ");
      Serial.println(angle+=1.8);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(timer_delay);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(timer_delay);
    }
    Serial.println("Done with tracking the satellite");
    while(1);
  }
}
