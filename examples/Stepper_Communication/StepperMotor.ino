/*
 * Stepper Motor Driving with predefined Angle and trigger action
 * Step Angle assumed: 1.8 Degree
 * 
 */
#include <Stepper.h>
#include <ArduinoJson.h>
#include "constants.h"

// Default Initialize the stepper library on pins 8 through 11:
Stepper myStepper = Stepper(STEPS_PER_REVOLUTION, STEPPER_1, STEPPER_2, STEPPER_3, STEPPER_4);

String dataReceived = "";
boolean isStringComplete = false;

StaticJsonDocument<200> json;

void setup() {
  pinMode(STEPPER_DIRECTION,OUTPUT);
  
  // initialize the serial port:
  Serial.begin(BAUD_RATE);
  while (!Serial) continue;

}

void loop() {
  
  if(isStringComplete)
  {      
    isStringComplete = false;
    
    //Parsing String to JSON data
    DeserializationError error = deserializeJson(json,dataReceived);

    if(error)
    {
        Serial.write("{\"status\":500, \"msg\":\"JSON Parsing error\"}");
        
        return;
    }

    analyisJsonData(json.as<JsonObject>());

    //Reseting the Flag
    dataReceived = "";
    
  }
  delay(500);
}


void analyisJsonData(JsonObject obj )
{
  int config1 = obj[String(KEY_COMMAND_TYPE)];

  //Configuration Data
  switch(config1)
  {
    //To configure the Stepper Motor
    case 0:
            if(setupStepperMotor(obj))
              Serial.write("{\"status\": 201}");
            break;
            
   //To rotate the Stepper Motor with given angel
    case 1:
            int angel = json[String(KEY_ANGEL)];
            if( rotateMotorByAngle(angel) )
              Serial.write("{\"status\": 200}");
            break;
    default:
            Serial.write("{\"status\": 400}");
  }
}

boolean setupStepperMotor(JsonObject configure)
{   
    float stepAngel = configure[String(KEY_STEP_ANGEL)]; 
    int speed = configure[String(KEY_SPEED)];
    int direction = configure[String(KEY_DIRECTION)];
    
    digitalWrite(STEPPER_DIRECTION,direction);
    
    int steps_per_revolution  = 360 / stepAngel;
 
    //Configure the Stepper Motor with new values
    myStepper = Stepper(steps_per_revolution, STEPPER_1, STEPPER_2, STEPPER_3, STEPPER_4);
    myStepper.setSpeed(speed);
     
    return true;
}

boolean rotateMotorByAngle(int angel)
{
    //Calculating the Steps required to make; i.e. 360/1.8 = 200 steps
    int stepCount = angel/STEP_ANGLE;

    if(stepCount<=200)
      myStepper.step(stepCount);  
      
    return true;
}

void serialEvent() {
  while (Serial.available()) {
    
    // get the new byte:
    char inChar = (char)Serial.read();
    
    dataReceived += inChar;
    
    if (inChar == '}') 
    { 
      dataReceived +="\0";
      isStringComplete = true;
    }
  }
}
