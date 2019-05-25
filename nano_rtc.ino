#include <Wire.h>
#include <DS3231.h>
#include <SoftwareSerial.h>
#include "libraries/ShiftRegister/ShiftRegister.h"
// #define DS3231_ADDR 0x68
#define CMDSIZE 64
#define LATCH_PIN 7 //Pin connected to Pin 12 of 74HC595 (Latch)
#define CLOCK_PIN 4 //Pin connected to Pin 11 of 74HC595 (Clock)
#define DATA_PIN 6  //Pin connected to Pin 14 of 74HC595 (Data)

ShiftRegister sr(CLOCK_PIN,LATCH_PIN,DATA_PIN); //create a new ShiftRegister Object
SoftwareSerial Bluetooth(10, 9); // RX, TX
DS3231 rtc(SDA, SCL);

char Data; // the data received

//cmds
char cmd[CMDSIZE + 1];
char *fcmd, *fparam;
byte cmdpointer = 0;

//millistracker
unsigned long millis1 = 0;
long ticker1 = 1000;

void setup()
{
  // Wire.begin();
  Bluetooth.begin(9600);
  Serial.begin(9600);
  rtc.begin();
}

// the loop function runs over and over again forever
void loop() {
  //Bluetooth comm
  while (Bluetooth.available())
  {
    Data = Bluetooth.read();
    if (Data == ';')
    {
      //new line, execute
      controller(cmd);
      //empty the buffer
      memset(cmd, 0, sizeof(cmd));
      cmdpointer = 0;
    }
    else
    {
      //buffer the string
      cmd[cmdpointer] = Data;
      cmdpointer++;
    }
  }

  // millistracked
  unsigned long currentMillis = millis();
  // serial
  if (currentMillis - millis1 >= ticker1)
  {
    // Send Day-of-Week
    Serial.print(rtc.getDOWStr());
    Serial.print(" ");

    // Send date
    Serial.print(rtc.getDateStr());
    Serial.print(" -- ");
    // Send time
    Serial.println(rtc.getTimeStr());
    Serial.print("Temperature: ");
    Serial.print(rtc.getTemp());
    Serial.println(" C");
    millis1 = currentMillis;  // update millis
  }
}

void controller(char *command)
{
  fcmd = strtok(command, " ");
  fparam = strtok(NULL, " ");
  if (fcmd == NULL || fparam == NULL)
  {
    Bluetooth.println("0;NODE:Wrong command format.");
  }
  else
  {
    Bluetooth.print("Command : ");
    Bluetooth.print(fcmd);
    Bluetooth.print(" . Param : ");
    Bluetooth.println(fparam);
    action(fcmd,fparam);
  }
}

void action(char *command, char *param){
  Serial.print(command);
  Serial.println(" command received.");
  if(strcmp(command,"srd") == 0) {
    //--------------------------------------------------srd SET date
    int sy=0;
    int sm=0;
    int sd=0;
    sscanf(param, "%d:%d:%d", &sy, &sm, &sd);
    Serial.println("Change Date.");
    Bluetooth.print("Change Date to:");
    Bluetooth.print(sy);
    Bluetooth.print("-");
    Bluetooth.print(sm);
    Bluetooth.print("-");
    Bluetooth.print(sd);
    Bluetooth.println(".");
    rtc.setDate(sd, sm, sy);
  }else if(strcmp(command,"rga") == 0) {
    //--------------------------------------------------rgd GET datetime
    Bluetooth.print(rtc.getDateStr());
    Bluetooth.print(" ");
    Bluetooth.println(rtc.getTimeStr());
  }else if(strcmp(command,"rgd") == 0) {
    //--------------------------------------------------rgd GET date
    Bluetooth.println(rtc.getDateStr());
  }else if(strcmp(command,"rgt") == 0) {
    //--------------------------------------------------rgt GET time
    Bluetooth.println(rtc.getTimeStr());
  }else if(strcmp(command,"rgw") == 0) {
    //--------------------------------------------------rgw GET week
    Bluetooth.println(rtc.getDOWStr());
  }else if(strcmp(command,"rgc") == 0) {
    //--------------------------------------------------rgc GET temp
    Bluetooth.print("Temperature: ");
    Bluetooth.print(rtc.getTemp());
    Bluetooth.println(" C");
  }else {
    Serial.println("Unknown command.");
    Bluetooth.println("Unknown command.");
  }
}
