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

// instantiate the font and ITDB02 object
extern uint8_t BigFont[];
ITDB02 myGLCD(19, 18, 17, 16); 

void setup() {
  // initialise the LCD in landscape mode and clear screen
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.clrScr();
  
  // set the initial time
  setTime(21, 5, 55, 11, 2, 2012);
}

void loop(){
  
  // call the digital clock function
  String timestr = digitalClockDisplay();
  char lcdtimestr[10] = "";
  timestr.toCharArray(lcdtimestr, 10);
  
  // call the date string function
  String datestr = digitalDateDisplay();
  char lcddatestr[30] = "";
  datestr.toCharArray(lcddatestr, 30);
  
  // set the initial forground and background color
  myGLCD.setColor(0, 255, 0);
  myGLCD.setBackColor(0, 0, 0);
  
  // Set the font and print the date and time strings to the LCD
  myGLCD.setFont(BigFont);
  myGLCD.print(lcddatestr, CENTER, 100);
  myGLCD.print(lcdtimestr, CENTER, 130);
  
  delay(1000);
}

String digitalClockDisplay(){
  
  // build the time string
  String timestr = "";
  timestr += hour();
  timestr += ":";
  timestr += printDigits(minute());
  timestr += ":";
  timestr += printDigits(second());
  
  return timestr;
}

String digitalDateDisplay(){
  
  // build the date string
  String datestr = "";
  datestr += String(dayStr(weekday())).substring(0,3);
  datestr += ", ";
  datestr += day();
  datestr += " ";
  datestr += String(monthShortStr(month())).substring(0,3);
  datestr += " ";
  datestr += year();
  
  return datestr;
}

String printDigits(int digits){
  
  // append the time digit with a zero if it is less than 10
  String appended = String("");
  if(digits < 10)
    appended += String('0');
  appended += String(digits);
  
  return appended;
}

