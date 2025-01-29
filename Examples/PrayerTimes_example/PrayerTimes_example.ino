#include <stdio.h>
#include <Wire.h>
#include <TimeLib.h>
#include "PrayerTimes.h"

double times[sizeof(TimeName)/sizeof(char*)];

void p(char *fmt, ... ){
        char tmp[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(tmp, 128, fmt, args);
        va_end (args);
        Serial.print(tmp);
}



void setup() {
  Serial.begin(9600);
  
}

void loop() {

  Serial.println("PTimes:");
  
  int dst=1;
  
  set_calc_method(ISNA);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(15);
  set_isha_angle(15);
  
  //MEKKA
  //float latitude=21.427378;
  //float longitude=39.814838;
  //get_prayer_times(year(), month(), day(), latitude, longitude, dst, times);
    get_prayer_times(2015, 5, 8, 46.9500f, 7.4458f, 2, times);
    
    Serial.print("YEAR:");     
    Serial.println(year());     
    Serial.print("MONTH:");     
    Serial.println(month());     
    Serial.print("DAY:");     
    Serial.println(day());     
      
  for (int i=0;i<sizeof(times)/sizeof(double);i++){
    char tmp[10];
    int hours, minutes;
    get_float_time_parts(times[i], hours, minutes);
    p("%d \t %10s %s \t %02d:%02d \n\r",i,TimeName[i],dtostrf(times[i],2,2,tmp),hours,minutes);
    /*
    Serial.print(i); 
    Serial.print(" \t "); 
    Serial.print(TimeName[i]); 
    Serial.print(" \t\t "); 
    Serial.print(times[i]);
    Serial.print(" \t ");     
    Serial.print(hours); 
    Serial.print(":"); 
    Serial.print(minutes); 
    Serial.println();
    */
  }
  delay(10000);
}


void getNextPTime(double &pTime, char* pTimeName)
{
  double times[sizeof(TimeName)/sizeof(char*)];
  double currTime=hour()+minute()/60.0;
  int i;
  
  set_calc_method(ISNA);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(15);
  set_isha_angle(15);

  //get_prayer_times(year(), month(), day(), 46.9500, 7.4458, 1, times);
  get_prayer_times(year(), month(), day(), 46.9500, 7.4458, 2, times);
  for (i=0;i<sizeof(times)/sizeof(double);i++){
    if (times[i] >= currTime) break;
  }
  if ( (times[i]-currTime) <0 ) {    
    i=0;
  }
  pTime=times[i];
  sprintf(pTimeName,"%s",TimeName[i]);
}
