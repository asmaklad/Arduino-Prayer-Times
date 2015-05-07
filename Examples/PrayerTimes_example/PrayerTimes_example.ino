#include <stdio.h>
#include <Wire.h>
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
  //get_prayer_times(year(), month(), day(), latitude, longitude, timezone, &times);
  set_calc_method(ISNA);
  set_asr_method(Shafii);
  //set_high_lats_adjust_method(AngleBased);
  //set_fajr_angle(15);
  //set_maghrib_angle(15);
  //set_isha_angle(15);
  int dst=1;
  
  //MEKKA
  float latitude=21.427378;
  float longitude=39.814838;
  get_prayer_times(year(), month(), day(), latitude, longitude, dst, times);
  
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
