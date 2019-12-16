Examples for JSON communication over Serial Port
------------------------------------------------

* This library contains examples which are compatible with "ArduinoJson" library 6.13.0 v
#### A Basic work flow of a use case, where a stepper motor is controlled by using serial port comm

#### Step 1:
To configure the Stepper motor, Android app sends a command in string format to Arduino Serial port

Arduino             `<<<<================`                 HC-05 BLE Module/Android App
           
            `{
              "command_type":0, 
              "step_angel":1.8,
              "speed":100,
              "direction":1
            }`

#### Step 2:
The command received then parsed in JSON format and respective params are set for stepper motor and status 201 is sent and if some error occurs then status 500 is sent

Arduino`=================>>>>>`               HC-05 BLE Module/Android APP
           
            {
                "status":201
            }

                    or
            {
                "status": 500,
                "msg": "JSON Parsing error"
            }


#### Step 3:
Once the motor is configure then the angel to rotate can be easily sent like this, the number of steps will be calculate internally

Arduino         `<<<<<======================`                            HC-05 BLE Module/Android APP
            
            {
                "command_type":1
                "angel": 360
            }
