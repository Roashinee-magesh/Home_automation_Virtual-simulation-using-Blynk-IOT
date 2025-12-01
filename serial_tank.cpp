#include "serial_tank.h"
#include "Arduino.h"
#include "main.h"


unsigned char valueh, valuel;
unsigned int volume_value;
void init_serial_tank(void) 
{
    Serial.begin(19200); //initialising serial tank
    Serial.write(0xFF); //sending dummy data
    Serial.write(0xFF);
    Serial.write(0xFF);   
}

unsigned int volume(void)
{
    Serial.write(VOLUME); //read the volume of the water
    while(!Serial.available());
    valueh=Serial.read();
    while(!Serial.available());
    valuel= Serial.read();
    volume_value=valueh<<8 | valuel;
    return volume_value;
}
void enable_inlet(void)
{
    Serial.write(INLET_VALVE);
    Serial.write(ENABLE);
}  
void disable_inlet(void)
{
    Serial.write(INLET_VALVE);
    Serial.write(DISABLE);
}  
void enable_outlet(void)
{  
    Serial.write(OUTLET_VALVE);
    Serial.write(ENABLE);
}
void disable_outlet(void)
{  
    Serial.write(OUTLET_VALVE);
    Serial.write(DISABLE);
}
