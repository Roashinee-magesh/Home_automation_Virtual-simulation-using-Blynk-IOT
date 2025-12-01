/*************************************************************
Title         :   Home automation using blynk
Description   :   To control light's brigntness with brightness,monitor temperature , monitor water level in the tank through blynk app
Pheripherals  :   Arduino UNO , Temperature system, LED, LDR module, Serial Tank, Blynk cloud, Blynk App.
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings



// Comment this out to disable prints 
#define BLYNK_TEMPLATE_ID "TMPL3rlI7Jby2"
#define BLYNK_TEMPLATE_NAME "homeautomation"
#define BLYNK_AUTH_TOKEN "HRRxT3PkllYWY_TOZLyKpsM4fEsGuMZS"


#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
#include <Wire.h>  //for clcd i2c communication
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
#include "ldr.h"
#include "main.h"
#include "temperature_system.h"

BlynkTimer timer;//creating ibject called timer to update the temp on blunk app at particular period





#include "serial_tank.h"

bool heater_sw,inlet_sw,outlet_sw,cooler_sw;

//unsigned int tank_volume;





// This function is called every time the Virtual Pin 0 state changes
/*To turn ON and OFF cooler based virtual PIN value*/
BLYNK_WRITE(COOLER_V_PIN)
{
  //read the changed value in the pin
  cooler_sw=param.asInt();
  cooler_control(cooler_sw);
  if(cooler_sw){
    lcd.setCursor(7,0);
  lcd.print("C0LR_ON "); 

  }
  else{
  lcd.setCursor(7,0);
  lcd.print("C0LR_OFF"); 
  }


}
/*To turn ON and OFF heater based virtual PIN value*/
BLYNK_WRITE(HEATER_V_PIN )
{
   heater_sw=param.asInt();
  heater_control(heater_sw);
  if(heater_sw){
    lcd.setCursor(7,0);
  lcd.print("HTR_ON "); 

  }
  else{
  lcd.setCursor(7,0 );
  lcd.print("HTR_OFF"); 
  }


}

/*To turn ON and OFF inlet vale based virtual PIN value*/
BLYNK_WRITE(INLET_V_PIN)
{
  inlet_sw=param.asInt();
  if (inlet_sw){
     enable_inlet();
     lcd.setCursor(7,1); //PRINT ON CLCD SECOND LINE
     lcd.print("IN_FL_ON ");
  }
  else{
     disable_inlet();
     lcd.setCursor(7,1);  // print on clcd
     lcd.print("IN_FL_OFF");
  }
}
/*To turn ON and OFF outlet value based virtual switch value*/
BLYNK_WRITE(OUTLET_V_PIN)
{
  outlet_sw=param.asInt();
  if (outlet_sw){
     enable_outlet();
     lcd.setCursor(7,1); //PRINT ON CLCD SECOND LINE
     lcd.print("OT_FL_ON ");
  }
  else{
     disable_outlet();
     lcd.setCursor(7,1);  // print on clcd
     lcd.print("OT_FL_OFF");
  }
}
/* To display temperature and water volume as gauge on the Blynk App*/  
void update_temperature_reading()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  
  Blynk.virtualWrite(TEMPERATURE_GAUGE,read_temperature());//send temp to blynk app n pin v1
  Blynk.virtualWrite(WATER_VOL_GAUGE,volume());
}

/*To turn off the heater if the temperature raises above 35 deg C*/
void handle_temp(void)
{
 //read temp and compare it with 35 
 if(read_temperature()>(float)35 && heater_sw){
  //turn off the heater and also the button in the blynk 
    heater_sw = 0;
    /*Turn off the heater*/
    heater_control(OFF);
    /*To print heater status on the dashboard*/
    lcd.setCursor(7,0);
    lcd.print("HT_R OFF");

    /*To print notification on the Blynk app*/
    Blynk.virtualWrite(BLYNK_TERMINAL_V_PIN, "Temperature is above 35 degree celsius\n");
    Blynk.virtualWrite(BLYNK_TERMINAL_V_PIN, "Turning OFF the heater\n");

    /*To reflect the status on the button widget on heater pin*/
    Blynk.virtualWrite(HEATER_V_PIN, 0);


 }
 //turn off the heater and the button
}

/*To control water volume above 2000ltrs*/
void handle_tank(void)
{
  if(volume()<2000 && (inlet_sw==0)){
  //if the volume of water is more than 2000
    inlet_sw = 1;
   //turn on the inlet valve
   enable_inlet();
    Blynk.virtualWrite(INLET_V_PIN,1);
    lcd.setCursor(7,1);
    lcd.print("IN_FL_ON");

 }
 
  

}

void setup(void)
{
  Blynk.begin(BLYNK_AUTH_TOKEN);
    init_ldr();
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.home();
    lcd.setCursor(0,0);
    lcd.print("Home Automation"); // also correct spelling
    delay(1000);
    lcd.clear();
    init_serial_tank();
    init_temperature_system();
    timer.setInterval(1000, update_temperature_reading);
}

float temp;
unsigned int volume_water;
void loop(void) 
{
      Blynk.run();//CONTROL HEATER AND cooler from blynk heater-v0 and cooler v1
     
      timer.run(); //turn on timer
      brightness_control();
      temp=read_temperature();
      handle_temp();
      handle_tank();
      volume_water=volume(); //reading the volume of the water
      lcd.setCursor(0,0);//to set pointer position
      lcd.print(temp); //display temp on clcd
      lcd.setCursor(0,1); //display volume on clcd
      lcd.print(volume_water);
      
       
}
