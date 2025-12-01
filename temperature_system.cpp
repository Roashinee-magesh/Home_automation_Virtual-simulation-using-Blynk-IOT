#include "temperature_system.h"
#include "Arduino.h"
#include "main.h"
float temperature;

void init_temperature_system(void)
{
    //SETTING HEATER AND COOLER AS OUTPUT PINS
    pinMode(HEATER,OUTPUT);
    pinMode(COOLER,OUTPUT);
    
}

float read_temperature(void)
{
    //lm35 temp sensor is used which doesnt need the requirement 
      //of calibration.for 1 degree celcius the output given is 10 milli volt
      temperature=(((analogRead(A0)*(float)5/1024))/(float)0.01);
      //to get voltage value ,this is being multiplied with step size which is Vmax-Vmin by 2 power r
      return temperature;
}

void cooler_control(bool control)//state of the button is being received on the blynk app
{
   if(control){
           //turn on cooler ;assign digital value  to the cooler pin
           digitalWrite(COOLER,1);
          
   }
   else{
            digitalWrite(COOLER,0);//OFF CONDITION
            
   }
}
void heater_control(bool control)
{
     if(control){
           //turn on heater ;assign digital value  to the cooler pin
           digitalWrite(HEATER,1);
           
   }
   else{
            digitalWrite(HEATER,0);//OFF CONDITION
           
   }
}

