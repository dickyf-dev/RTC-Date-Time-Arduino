#include <Wire.h> 
#include <RTClib.h>
#include <LiquidCrystal_I2C.h> 
 
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
const unsigned int BUTTON_PIN = 7;
 
uint8_t clock[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
RTC_DS1307 RTC;
 
char daysOfTheWeek[7][12] = {"Ming", "Sen", "Sel", "Rab", "Kam", "Jum", "Sab"};
char bulan[13][12] = {"Jan","Feb", "Mar", "Apr", "Mei", "Jun", "Jul", "Agu", "Sep", "Okt", "Jan", "Nov","Des"};

 //sensor
int led = 13;                // the pin that the LED is atteched to
int sensor = 2;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)


void setup() {
 
  
 Wire.begin();
 RTC.begin();
 Serial.begin(9600);
 pinMode(BUTTON_PIN, INPUT);
 pinMode(led, OUTPUT);      // initalize LED as an output
 pinMode(sensor, INPUT);    // initialize sensor as an input
lcd.noBacklight();
delay(6000); 
digitalWrite(led, HIGH);
 lcd.begin(16, 2);
  //lcd.print("Belajar I2C LCD");
 
if (! RTC.begin()) {
    Serial.println("RTC tidak ditemukan");
    while (1);
  }
 
  if (! RTC.isrunning()) {
    Serial.println("RTC tidak jalan!");
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
 
 // Mengatur tanggal dan waktu sesuai dengan waktu code di compile
 RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
//RTC.adjust(DateTime(2014, 1, 21, 3, 0, 0));
 
}

void loop(){

  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led, LOW);   // turn LED ON
   // delay(6000000);                // delay 1 mnt milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      //delay(2000);  
     // digitalWrite(led, HIGH); // turn LED OFF
     //delay(3000);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }

  //date time
   DateTime now = RTC.now();
    lcd.setCursor(0,0);
    lcd.print("Pukul : ");
     lcd.backlight();
    if(now.hour()<10){
    lcd.print("0");}
     
    lcd.print(now.hour(), DEC);
    lcd.print(':');
     
    if(now.minute()<10){
    lcd.print("0");}
     
    lcd.print(now.minute(), DEC);
    lcd.print(':');
     
    if(now.second()<10){
    lcd.print("0");}
     
    lcd.print(now.second(), DEC);
 
    lcd.setCursor(0,1);
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.print(",");
    lcd.print(now.day(), DEC);
    lcd.print('/');

  
   //// //lcd.print(now.month(), DEC);
    lcd.print(bulan[now.month()]);
    lcd.print('/');
    lcd.print(now.year(), DEC);
     
    
    delay(1000);
}
