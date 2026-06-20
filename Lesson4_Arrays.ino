/*
  Lesson 4 - Arrays
  GearUp Robotics - Arduino & C++ Starter Lab

  Goal: store many values in ONE variable (an array) and
  step through them with a loop. The LED will blink "SOS"
  in Morse code.
  Hardware: just your Arduino board + USB cable.
*/

const int led = LED_BUILTIN;

// An array: many values lined up inside one variable.
// 1 = short blink (a dot), 3 = long blink (a dash).
int sos[] = {1, 1, 1,  3, 3, 3,  1, 1, 1};

// Count how many items are in the array.
int sosLength = sizeof(sos) / sizeof(sos[0]);

const int unit = 200;   // base time in milliseconds

void blinkUnits(int units) {
  digitalWrite(led, HIGH);
  delay(units * unit);          // a bigger number = a longer blink
  digitalWrite(led, LOW);
  delay(unit);                  // short gap between blinks
}

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  Serial.println("=== Lesson 4: Arrays ===");
  Serial.print("The array has ");
  Serial.print(sosLength);
  Serial.println(" items.");
}

void loop() {
  Serial.println("Sending S O S ...");

  // Visit every item by its index (0, 1, 2, ...).
  for (int i = 0; i < sosLength; i++) {
    Serial.print("index ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(sos[i]);
    blinkUnits(sos[i]);
  }

  delay(2000);   // pause before repeating
}
