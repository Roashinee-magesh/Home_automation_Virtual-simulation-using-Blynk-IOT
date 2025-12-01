#include "ldr.h"
#include "Arduino.h"
#include "main.h"

void init_ldr(void)
{
   pinMode(GARDEN_LIGHT, OUTPUT);
   
}
unsigned int Light_intensity,duty;
void brightness_control(void)
{
  Light_intensity=analogRead(LDR_SENSOR); // scale of 0 to 1023 bcoz of 10 bit ADC to 8 bit PWM.
  duty=255-(Light_intensity/4);
   //scales down to 0-255 since analogwrite inputs are limited range
  analogWrite(GARDEN_LIGHT,duty); //0 means light and 255 means dark
  delay(100);
}
