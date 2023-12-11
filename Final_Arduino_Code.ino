
#include <LiquidCrystal.h>  
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); 
float m = 4.7/14.7;


// ************* Measuring Voltage [STEP DOWN TRANSFORMER (500mA 9-0-9)] ******************

//#include "EmonLib.h"
//EnergyMonitor emon1; // object emon1
const int V_Pin = A0;


// ************** Measuring Current [ACS712 Module (((TO BUY)))] ***************

const int Sensor_Pin = A1; // A1 done
int sensitivity = 66; // 100 : 20A Module & 66 : 30A Module & 185 : 5A
int offsetvoltage = 2666; //2542 mV

void setup(){
  //emon1.voltage(A0,187, 1.7); // V : input pin, calibration, phase_shift

  lcd.begin(20, 4); // LCD's columns x rows matrix
  lcd.setCursor(0,0); //begin
  //lcd.print("***** B321065 *****");
  lcd.setCursor(0,1); // 2nd print
  lcd.print("* ENERGY METER *");
}

void loop(){
  
//************************* Measuring Voltage ******************************************
  
  //emon1.calcVI(20,200); // half wavelengths (crossings), time-out
  //int Voltage   = emon1.Vrms;  //Vrms setup

  float Voltage = analogRead(V_Pin);
  Voltage = Voltage*m/sqrt(2);
  
  lcd.setCursor(0,2);
  lcd.print("V = ");
  lcd.print(Voltage);
  lcd.print("V  ");


//************************* Measuring Current ******************************************
  unsigned int temp=0;
  float maxpoint = 0;
  for(int i=0; i<500; i++){
    if(temp = analogRead(Sensor_Pin), temp > maxpoint){
      maxpoint = temp;
    }
  }
  float ADCvalue = maxpoint; 
  double eVoltage = (ADCvalue / 1024.0) * 5000; // mV
  double Current = ((eVoltage - offsetvoltage) / sensitivity);
  double AC_Current = ( Current ) / ( sqrt(2) );

  lcd.print("I = ");
  lcd.print(AC_Current,2);
  lcd.print("A \n");




//************************* Measuring Power ******************************************
  float Power = (Voltage * AC_Current);
  
  lcd.setCursor(0,3); // 4th print
  lcd.print("P = ");
  lcd.print(Power, 1);
  lcd.print("W "); 
  



//************************* Measuring Energy ******************************************
  long milisec = millis(); // ms 
  long time = milisec/1000; //s
  
  float Energy = (Power*time)/3600; //Watt-sec to Watt-Hr 

  lcd.print("E = ");
  lcd.print(Energy,1);
  //lcd.print("*");
  //lcd.print(time);
  lcd.print("Wh");
  
  delay(100); // ms
}
