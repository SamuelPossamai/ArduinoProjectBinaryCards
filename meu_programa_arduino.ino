#include <Servo.h>

#define MOTORS_NUMBER 5

Servo motors[MOTORS_NUMBER];
char motors_pin[] = {3, 5, 6, 10, 11};
int motors_min[] = {0, 0, 0, 0, 0, 0};
int motors_max[] = {160, 180, 155, 155, 170};

char leds_pin[] = {2, 4, 7, 8, 12};
bool motors_state[MOTORS_NUMBER];
char last_button;

bool readAnalogasDigital(int pin){
  
  if(pin == 0) Serial.println(analogRead(pin));
  
  return analogRead(pin) > 400;
}

void setup(){
  
  Serial.begin(9600);
  
  for(char i = 0; i < MOTORS_NUMBER; i++){

    motors[i].attach(motors_pin[i]);
    pinMode(leds_pin[i], OUTPUT);
    
    motors[i].write(motors_min[i]);
    
    motors_state[i] = false;
    
    digitalWrite(leds_pin[i], motors_state[i]);
  }
  
  last_button = -1;
}

void loop(){
  
  for(char i = 0; i < MOTORS_NUMBER; i++){
    
    if(readAnalogasDigital(i)){
      
      if(last_button != i){
        
        motors_state[i] = !motors_state[i];
        
        motors[i].write(motors_state[i] ? motors_max[i] : 
                                          motors_min[i]);
        
        last_button = i;
        
        digitalWrite(leds_pin[i], motors_state[i]);
        
        delay(500);
      }
    }
    else if(last_button == i) last_button = -1;
  }
  
  Serial.println((int) last_button);
  
}

