/* 

LCD Clock.pde
This sketch demonstates a simple clock with the date in alpha-numerical form
on a 2.4" LCD touch screen.

Requires:
 - ITDB02_Graph (http://www.henningkarlsen.com/electronics/library.php?id=38)
 - Time (http://www.arduino.cc/playground/uploads/Code/Time.zip)

*/ 

#include <ITDB02_Graph.h>
#include <Time.h>

extern uint8_t BigFont[];
ITDB02 myGLCD(19, 18, 17, 16); 

void setup()  {
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.clrScr();
  setTime(22, 20, 20, 9, 2, 2012);
}

void loop(){
  String timestr = digitalClockDisplay();
  char lcdtimestr[10] = "";
  timestr.toCharArray(lcdtimestr, 10);
  
  String datestr = digitalDateDisplay();
  char lcddatestr[30] = "";
  datestr.toCharArray(lcddatestr, 30);
  
  myGLCD.setColor(0, 255, 0);
  myGLCD.setBackColor(0, 0, 0);

  myGLCD.setFont(BigFont);
  myGLCD.print(lcddatestr, CENTER, 100);
  myGLCD.print(lcdtimestr, CENTER, 130);
  
  delay(1000);
}

String digitalClockDisplay(){
  String timestr = "";
  timestr += String(hour());
  timestr += String(":");
  timestr += String(printDigits(minute()));
  timestr += String(":");
  timestr += String(printDigits(second()));
  
  return timestr;
}

String digitalDateDisplay(){
  String datestr = "";
  datestr += String(dayStr(weekday())).substring(0,3);
  datestr += String(", ");
  datestr += String(day());
  datestr += String(" ");
  datestr += String(monthShortStr(month())).substring(0,3);
  datestr += String(" ");
  datestr += String(year());
  
  return datestr;
}

String printDigits(int digits){
  String appended = String("");
  if(digits < 10)
    appended += String('0');
  appended += String(digits);
  
  return appended;
}

