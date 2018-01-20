#define VERSION "H.8.3"
//list of library
#include <TimeLib.h>       //TIME KEEP
#include <DS3232RTC.h>     //RTC 
#include <TimeAlarms.h>    //ALARMS MAX 30 alarms/day
#include <Wire.h>          //I2C bus
#include <NewTone.h>       //Tone 
#include "pitches.h"       //list of pitch
#include <LiquidCrystal.h> //LCD
#include <SoftReset.h>     //Use soft_restart() to restart
#include <EEPROM.h>        //EEPROM library
#include <MemoryFree.h>    //RAM usage library
boolean NC = false;        // bool for checking if pc is connected
boolean MUTED;             // bool For muting The buzzer
byte Ls[2];                //[0] = Total alarm ; [1] = Total active alarm at that day
byte MaxHoMin[2];          //[0]= Hour, [1]= min
byte MinHoMin[2];          //[0]= hour, [1]= minutes

//LCD pin-out
LiquidCrystal lcd(2,3,4,5,6,7); 
//pin 12 IS FOR AUDIO


// SET TIME FUNCTION
void FuncTimeSet() {
  SerialClear();
  int TS[6];
  Serial.println("SET RTC CLOCK TIME");
  delay(500);
  Serial.println("SET YEAR");
  TS[0] = SerialGetData();
  Serial.println("SET MONTH");
  TS[1] = SerialGetData();
  Serial.println("SET DAY");
  TS[2] = SerialGetData();
  Serial.println("SET HOUR");
  TS[3] = SerialGetData();
  Serial.println("SET MINUTE");
  TS[4] = SerialGetData();
  Serial.println("SET SECOND");
  TS[5] = SerialGetData() + 1;
  setTime(TS[3],TS[4],TS[5],TS[2],TS[1],TS[0]);
  RTC.set(now());
  Serial.println(RTC.get());
  Serial.println("TIME SET");
}

String GETDATE(){
  switch(weekday()){
    case 1:
    {return "Sun";}
    break;
    case 2:
    {return "Mon";}
    break;
    case 3:
    {return "Tue";}
    break;
    case 4:
    {return "Wed";}
    break;
    case 5:
    {return "Thu";}
    break;
    case 6:
    {return "Fri";}
    break;
    case 7:
    {return "Sat";}
    break;
  }
}

//for simple printing LCD Int
void LCDDISPINT(byte x,byte y,int z){
  lcd.setCursor(x,y);
  lcd.print(z);
} 

//for Simple Printing LCD Strings
void LCDDISPSTR(byte x,byte y,String z){
  lcd.setCursor(x,y);
  lcd.print(z);
}

//Clear serial BUFFER
void SerialClear(){
  while (Serial.available()) {
    Serial.read();
  }
}

//Wait for Serial Input
void SerialWait(){
  while(!Serial.available()){
    //GOOD LUCK DOING ANYTHING
  }
}

//To Get int Form serial
int SerialGetData(){
  char Buffer[7];
  SerialClear();
  SerialWait();
  Serial.readBytesUntil('\n',Buffer,7);
  return atoi(Buffer);
}

//exit from debug menu
void SerEx() {
   NC = true;
   Serial.println("EXITING DEBUG"); 
   Serial.end();
   digitalWrite(13,LOW); 
}

//DEBUG greeting
void GreetingUI(){
  Serial.println("Please Refers To The GuideBook");
  Serial.println("Please Input Command:"); 
}

//Function to restart
void ReStart(){
  soft_restart();
}

//Plays the note for N duration
void PlayNoteDuration(int NOTE,int Length){
  NewTone(12,NOTE,Length);
  Alarm.delay(Length);
}

//Don`t do anything i`m just lazy
void NoPlay(int Len) {
  Alarm.delay(Len);
}

//Yeah Basically creating something like an tempo
void PlayNoteWithIntersmis(int NOTE,int Length){
  PlayNoteDuration(NOTE,Length);
  NoPlay(Length/2);
}


//Normal Train Station Sounds
void TrainStation() {
  PlayNoteDuration(NOTE_A5,1000);
  PlayNoteDuration(NOTE_F5,1000);
  PlayNoteDuration(NOTE_G5,1000);
  PlayNoteDuration(NOTE_C5,1000);
  NoPlay(1000);
  PlayNoteDuration(NOTE_C5,1000);
  PlayNoteDuration(NOTE_G5,1000);
  PlayNoteDuration(NOTE_A5,1000);
  PlayNoteDuration(NOTE_F5,1000);
}

//the 5th FING Symphony
void FifthSymp() {
  PlayNoteWithIntersmis(NOTE_G3,125);
  PlayNoteWithIntersmis(NOTE_G3,125);
  PlayNoteWithIntersmis(NOTE_G3,125);
  PlayNoteWithIntersmis(NOTE_DS3,750);
  PlayNoteWithIntersmis(NOTE_F3,125);
  PlayNoteWithIntersmis(NOTE_F3,125);
  PlayNoteWithIntersmis(NOTE_F3,125);
  PlayNoteWithIntersmis(NOTE_D3,750);
  PlayNoteWithIntersmis(NOTE_G3,125);
  PlayNoteWithIntersmis(NOTE_G3,125);
  PlayNoteWithIntersmis(NOTE_G3,125);
  PlayNoteWithIntersmis(NOTE_E3,125);
  PlayNoteWithIntersmis(NOTE_A3,125);
  PlayNoteWithIntersmis(NOTE_A3,125);
  PlayNoteWithIntersmis(NOTE_A3,125);
  PlayNoteWithIntersmis(NOTE_G3,125);
  PlayNoteWithIntersmis(NOTE_DS4,125);
  PlayNoteWithIntersmis(NOTE_DS4,125);
  PlayNoteWithIntersmis(NOTE_DS4,125);
  PlayNoteWithIntersmis(NOTE_C4,625);
  PlayNoteWithIntersmis(NOTE_G3,125);
  PlayNoteWithIntersmis(NOTE_G3,125);
  PlayNoteWithIntersmis(NOTE_G3,125);
  PlayNoteWithIntersmis(NOTE_DS3,125);
  PlayNoteWithIntersmis(NOTE_A3,125);
  PlayNoteWithIntersmis(NOTE_A3,125);
  PlayNoteWithIntersmis(NOTE_A3,125);
  PlayNoteWithIntersmis(NOTE_G3,125);
  PlayNoteWithIntersmis(NOTE_F4,125);
  PlayNoteWithIntersmis(NOTE_F4,125);
  PlayNoteWithIntersmis(NOTE_F4,125);
  PlayNoteWithIntersmis(NOTE_D4,625);
  PlayNoteWithIntersmis(NOTE_G4,125);
  PlayNoteWithIntersmis(NOTE_G4,125);
  PlayNoteWithIntersmis(NOTE_F4,125);
  PlayNoteWithIntersmis(NOTE_DS4,500);
  PlayNoteWithIntersmis(NOTE_C4,100);
  PlayNoteWithIntersmis(NOTE_G4,125);
  PlayNoteWithIntersmis(NOTE_G4,125);
  PlayNoteWithIntersmis(NOTE_F4,125);
  PlayNoteWithIntersmis(NOTE_DS4,500);
  PlayNoteWithIntersmis(NOTE_C4,100);
  PlayNoteWithIntersmis(NOTE_G4,125);
  PlayNoteWithIntersmis(NOTE_G4,125);
  PlayNoteWithIntersmis(NOTE_F4,125);
  PlayNoteWithIntersmis(NOTE_DS4,500);
  PlayNoteWithIntersmis(NOTE_C4,500);
  PlayNoteWithIntersmis(NOTE_G4,1000);
}

//CANON FING D
void CanonD(){
  PlayNoteWithIntersmis(NOTE_A5,500);
PlayNoteWithIntersmis(NOTE_FS5,250);
PlayNoteWithIntersmis(NOTE_G5,250);
PlayNoteWithIntersmis(NOTE_A5,500);
PlayNoteWithIntersmis(NOTE_FS5,250);
PlayNoteWithIntersmis(NOTE_G5,250);
PlayNoteWithIntersmis(NOTE_A5,250);
PlayNoteWithIntersmis(NOTE_A4,250);
PlayNoteWithIntersmis(NOTE_B4,250);
PlayNoteWithIntersmis(NOTE_CS5,250);
PlayNoteWithIntersmis(NOTE_D5,250);
PlayNoteWithIntersmis(NOTE_E5,250);
PlayNoteWithIntersmis(NOTE_FS5,250);
PlayNoteWithIntersmis(NOTE_G5,250);
PlayNoteWithIntersmis(NOTE_FS5,500);
PlayNoteWithIntersmis(NOTE_D5,250);
PlayNoteWithIntersmis(NOTE_E5,250);
PlayNoteWithIntersmis(NOTE_FS5,500);
PlayNoteWithIntersmis(NOTE_FS4,250);
PlayNoteWithIntersmis(NOTE_G4,250);
PlayNoteWithIntersmis(NOTE_A4,250);
PlayNoteWithIntersmis(NOTE_B4,250);
PlayNoteWithIntersmis(NOTE_A4,250);
PlayNoteWithIntersmis(NOTE_G4,250);
PlayNoteWithIntersmis(NOTE_A4,250);
PlayNoteWithIntersmis(NOTE_FS4,250);
PlayNoteWithIntersmis(NOTE_G4,250);
PlayNoteWithIntersmis(NOTE_A4,250);
PlayNoteWithIntersmis(NOTE_G4,500);
PlayNoteWithIntersmis(NOTE_B4,250);
PlayNoteWithIntersmis(NOTE_A4,250);
PlayNoteWithIntersmis(NOTE_B4,500);
PlayNoteWithIntersmis(NOTE_FS4,250);
PlayNoteWithIntersmis(NOTE_E4,250);
PlayNoteWithIntersmis(NOTE_FS4,250);
PlayNoteWithIntersmis(NOTE_E4,250);
PlayNoteWithIntersmis(NOTE_D4,250);
PlayNoteWithIntersmis(NOTE_E4,250);
PlayNoteWithIntersmis(NOTE_FS4,250);
PlayNoteWithIntersmis(NOTE_G4,250);
PlayNoteWithIntersmis(NOTE_A4,250);
PlayNoteWithIntersmis(NOTE_B4,250);
PlayNoteWithIntersmis(NOTE_G4,500);
PlayNoteWithIntersmis(NOTE_B4,250);
PlayNoteWithIntersmis(NOTE_A4,250);
PlayNoteWithIntersmis(NOTE_B4,500);
PlayNoteWithIntersmis(NOTE_CS5,250);
PlayNoteWithIntersmis(NOTE_D5,250);
PlayNoteWithIntersmis(NOTE_B4,250);
PlayNoteWithIntersmis(NOTE_CS5,250);
PlayNoteWithIntersmis(NOTE_D5,250);
PlayNoteWithIntersmis(NOTE_CS5,250);
PlayNoteWithIntersmis(NOTE_E5,250);
PlayNoteWithIntersmis(NOTE_D5,250);
PlayNoteWithIntersmis(NOTE_B4,250);
PlayNoteWithIntersmis(NOTE_CS5,250);
PlayNoteWithIntersmis(NOTE_D5,1000);
}

byte DiEL() {
  return (weekday()+ 10);
}

//Music For the bell 
void Bell(){
  /*
  byte EA[2]; //0-1
  EA[1] = DiEL();  //get the eeprom address
  EA[0] = EEPROM.read(EA[1]);  // reads the addrs
  EA[0]++; // add 1
  EEPROM.update(EA[1],EA[0]); //write back the address
  */ // Yhea im gonna just comment this in case the probability of this fails i have a backup
  if(!MUTED){
    // To: Haru
    // Apparently You CAN`T use a var for constants is Switch
    // So Here`s if else-if and else case for you
    // enjoy with love Haru.
    if ( hour() == MinHoMin[0] && minute() == MinHoMin[1] ){
      FifthSymp(); //Plays the 5th Symphony
    }else if ( hour() == MaxHoMin[0] && minute() == MaxHoMin[1] ){
      CanonD(); //Plays CANON IN D
    }else{
      TrainStation(); // else the just play the station bell
    }
  }
}

//does a startupCheck
void StartupCheck(){
  lcd.clear();
  checkMute();
  LCDDISPSTR(0,0,"Ver :");
  LCDDISPSTR(6,0,VERSION);
  LCDDISPSTR(0,1,"EEPROM :");
  byte Check = EEPROM.read(0);
  if (Check == 42){
    LCDDISPSTR(10,1,"OK");
  } else {
    LCDDISPSTR(10,1,"NO");
  }
}

//restartTimedProscured
void TimRestd(){
  EEPROM.write(DiEL(),0); 
  ReStart();
}

//Check If MUTED
void checkMute(){
  if (!EEPROM.read(1)){
    MUTED = false;
  }else {
    MUTED = true;
  }
}

//for printing the mute
void PrintMute(bool x){
  if (x){
    Serial.println("Mute : True");
  } else {
    Serial.println("Mute : False");
  }
}

//Toggling MuteViaSerial
void ToggleMute(){
  SerialClear();
  MUTED = EEPROM.read(1);
  PrintMute(MUTED);
  delay(500);
  Serial.println("press 1 to Toggle, any to cancel");
  int xc = SerialGetData();
  if(xc == 1){
    if(MUTED){
      MUTED = false;
    } else {
      MUTED = true;
    }
    PrintMute(MUTED);
    EEPROM.write(1,MUTED);
  }
}

//Format The EEPROM
//0-10 Reerved for Status & Info
//11-20 Reserved for Counting days
void Format(){
  SerialClear();
  Serial.println("press 1 to continue, any to cancel");
  delay(500);
  int x = SerialGetData();
  if( x == 1 ){
    for (int i = 0 ; i < EEPROM.length() ; i++) {
     EEPROM.write(i, 0);
    }
    //EEPROM.write(2,4);  //Write the start address
    EEPROM.write(0,42); //write the sign
    Serial.println("Format successful");
  } else {
    Serial.println("Format canceled");
  }
}

//Prints the EEPROM Contents
void DumpEEPROM(){
	Serial.println("EEPROM DATA:");
	for (int i = 0 ; i < EEPROM.length() ; i++) {
		Serial.print(i);
		Serial.print(":");
		Serial.println(EEPROM.read(i));
		delay(200);
    }
}

//A very lazy me, turns the hour into min elapsed in a day 
int MinInADay(byte Hor,byte Min){
  int Num = Hor*60;
  Num = Num + Min;
  return Num;
}

void PutMinMax(byte hx,byte mx) {
//  MinHoMin[0] = 100;
//  MaxHoMin[0] = 0;
int Time = MinInADay(hx,mx);
  if (Time <= MinInADay(MinHoMin[0],MinHoMin[1])){
     MinHoMin[0] = hx;
     MinHoMin[1] = mx;
  }
  if (Time >= MinInADay(MaxHoMin[0],MaxHoMin[1])){
    MaxHoMin[0] = hx;
    MaxHoMin[1] = mx;
  }
}

//HELLO THERE IT`S NICE ISNT IT ?
//PULL THE ALARM
void ManAlarms(byte Ho,byte Mi,byte Da){
  if(bitRead(Da,0)){
    Ls[0]++;
    if(bitRead(Da,weekday())){
      Alarm.alarmOnce(Ho,Mi,1,Bell);
      PutMinMax(Ho,Mi); 
      Ls[1]++;
    }
  }
}

//ACTUAL ALARMS FINALY
void StartAlarms(){
	/*
	anyway the way you set up the alarm is like this
	ManAlarms(hours,Minutes,Days)
    the days goes like this : (also binary counting is from the right)
	1 = ACTIVE
	0 = DISABLED
	
    Number		FUNCTION
	0			ACTIVE/NON ACTIVE	
	1			SUNDAY
	2			MONDAY
	3			TUESDAY
	4			WEDNESDAY
	5			THURSDAY
	6			FRIDAY
	7			SATURDAY	
	
	so for demonstration a alarm for Sunday and Saturday at 9,30 AM
		ManAlarms(9,30,B10000011)
	
	also this uses the 24 clock cycle just Remember that.
	*/
}

void LcdAlamrs(){
  lcd.clear();
  LCDDISPSTR(0,0,"ACTIVE :");
  LCDDISPINT(8,0,Ls[1]);
  LCDDISPSTR(0,1,"TOTAL :");
  LCDDISPINT(7,1,Ls[0]);
}

void CheckRAM() {
  lcd.clear();
  LCDDISPSTR(0,0,"RAM USAGE :");
  LCDDISPINT(0,1,2000-freeMemory());
  LCDDISPSTR(5,1,"OUT OF");
  LCDDISPINT(12,1,2000);
}

void Set0toByts(){
  MinHoMin[0] = 100;
  MinHoMin[1] = 100;
  MaxHoMin[0] = 0;
  MaxHoMin[1] = 0;
}

void DisplayMinMax(){
  lcd.clear();
  LCDDISPSTR(0,0,"FIRST:");
  LCDDISPINT(7,0,MinHoMin[0]);//display Hour
  LCDDISPSTR(9,0,":");
  LCDDISPINT(11,0,MinHoMin[1]);//Display minute
  LCDDISPSTR(0,1,"LAST :");
  LCDDISPINT(7,1,MaxHoMin[0]);//display Hour
  LCDDISPSTR(9,1,":");
  LCDDISPINT(11,1,MaxHoMin[1]);//Display minute
}

//the things to do after the fact
void Startup(){
 setSyncProvider(RTC.get);
 setSyncInterval(960);
 StartupCheck();
 Set0toByts();
 Alarm.alarmOnce(6,30,5,TimRestd);
 Alarm.delay(2000);
 StartAlarms();
 LcdAlamrs();
 Alarm.delay(4000);
 DisplayMinMax();
 Alarm.delay(4000);
 CheckRAM();
 Alarm.delay(3000);
}

///////////////////////////////////////MAIN PROGRAM////////////////////////////////////////////

void setup() {
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  lcd.begin(16,2); 
  lcd.noCursor();
  LCDDISPSTR(2,0,"Please Wait");
  Serial.begin(9600);
  Serial.println("5 seconds to input anything");
  delay(5000);
  //Check if it connected to PC
  if(Serial.available()){
    digitalWrite(13,HIGH);
    SerialClear();
    NewTone(12,NOTE_E3,200);
    lcd.clear();
    LCDDISPSTR(5,0,"DEBUG");
    while(!NC){
     GreetingUI();
     SerialClear();
     SerialWait();
        switch (Serial.read()) {
        case '1':
         {FuncTimeSet();} //SET RTC TIME
        break;
        case '2':
         {FifthSymp();}//Plays The FifthSymp
        break;
        case '3':
         {CanonD();}// Plays Canon IN D
        break;
        case '4':
         {TrainStation();}//Play the Train Station
        break;
        case '5':
         {
          Serial.print("freeMemory()=");
          Serial.println(freeMemory());
          }// Get the amount of free ram
        break;
        case '6':
         {ToggleMute();}//TOGGLE MUTE 
        break;
        case '7':
         {DumpEEPROM();}//DUMPS the EEPROM contents
        break;
        case '8':
         {}// 
        break;
        case '9':
         {ReStart();}//Restart the arduino 
        break;
        case '0':
         {Format();}//FORMAT the EEPROM
         break;
         case 'R':
         {Serial.println(EEPROM.read(3));}//prints data in EEPROM3
         break;
        case 'X' :
         {SerEx();}
        break;
        default: 
           Serial.println("INVALD Command:");
         break;
        }
    }
  } 
  else {
   SerEx();
 }
 //Main Stuff
 Startup();
}

//DISPLAY CURRENT TIME
void DisplayTime() {
  LCDDISPINT(4,0,hour());
  LCDDISPSTR(6,0,":");
  LCDDISPINT(7,0,minute());
  LCDDISPSTR(9,0,"::");
  LCDDISPINT(11,0,second());
}

//DISPLAY CURRENT DATE
void DisplayDate(){
  LCDDISPSTR(1,1,GETDATE());
  LCDDISPSTR(4,1,":");
  LCDDISPINT(5,1,day());
  LCDDISPSTR(7,1,"/");
  LCDDISPINT(8,1,month());
  LCDDISPSTR(10,1,"/");
  LCDDISPINT(11,1,year());
}

//Shows M when its muted
void MuteShow(){
  if(MUTED){
    LCDDISPSTR(15,0,"M");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  MuteShow();
  DisplayTime();
  DisplayDate();
  Alarm.delay(1000);   
}
