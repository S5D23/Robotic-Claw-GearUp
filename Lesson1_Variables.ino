/*
  Lesson 1 - Variables & Data Types
  GearUp Robotics - Arduino & C++ Starter Lab

  Goal: learn how C++ stores different kinds of information,
  and how to print it to the Serial Monitor.
  Hardware: just your Arduino board + USB cable.
*/

// A constant never changes while the program runs.
const int blinkPin = LED_BUILTIN;    // the LED already on your board

// Variables hold values that CAN change.
int    blinkCount   = 0;        // whole numbers
long   bigNumber    = 100000;   // bigger whole numbers
float  batteryVolts = 7.4;      // numbers with decimals
bool   ledIsOn      = false;    // true or false
char   grade        = 'A';      // a single character
String teamName     = "GearUp"; // a line of text

void setup() {
  Serial.begin(9600);            // open the channel to the computer
  pinMode(blinkPin, OUTPUT);     // we will control this pin

  Serial.println("=== Lesson 1: Data Types ===");
  Serial.print("Team: ");        Serial.println(teamName);
  Serial.print("Grade: ");       Serial.println(grade);
  Serial.print("Battery (V): "); Serial.println(batteryVolts);
  Serial.print("Big number: ");  Serial.println(bigNumber);

  // Why types matter: integer math throws away the decimal part!
  int a = 7, b = 2;
  Serial.print("7 / 2 as int   = "); Serial.println(a / b);      // 3
  Serial.print("7 / 2 as float = "); Serial.println(7.0 / 2.0);  // 3.50
}

void loop() {
  ledIsOn = !ledIsOn;                  // flip true to false, false to true
  digitalWrite(blinkPin, ledIsOn);     // turn the LED on or off
  blinkCount = blinkCount + 1;         // count the blinks

  Serial.print("Blink #");
  Serial.print(blinkCount);
  Serial.print("  LED is ");
  Serial.println(ledIsOn ? "ON" : "OFF");

  delay(500);
}
