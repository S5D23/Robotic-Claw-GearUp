/*
  Lesson 3 - Conditions & Operators
  GearUp Robotics - Arduino & C++ Starter Lab

  Goal: make the program DECIDE what to do using if/else
  and logic. Type a number into the Serial Monitor and the
  board will sort it for you.
  Hardware: just your Arduino board + USB cable.
  Tip: in the Serial Monitor, set the line ending to "Newline".
*/

const int led = LED_BUILTIN;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  Serial.println("=== Lesson 3: Conditions ===");
  Serial.println("Type a whole number and press Enter.");
}

void loop() {
  if (Serial.available() > 0) {         // did the user send something?
    int number = Serial.parseInt();     // read it as an integer

    Serial.print("You sent: ");
    Serial.println(number);

    // if / else if / else: only ONE branch runs.
    if (number > 0) {
      Serial.println("-> positive");
    } else if (number < 0) {
      Serial.println("-> negative");
    } else {
      Serial.println("-> zero");
    }

    // % is the modulo operator: the remainder after dividing.
    if (number % 2 == 0) {
      Serial.println("-> even");
    } else {
      Serial.println("-> odd");
    }

    // && means AND, || means OR, ! means NOT.
    bool inRange = (number >= 1 && number <= 100);
    if (inRange && number % 2 == 0) {
      Serial.println("-> even AND between 1 and 100: blinking!");
      for (int i = 0; i < 3; i++) {
        digitalWrite(led, HIGH); delay(120);
        digitalWrite(led, LOW);  delay(120);
      }
    }
    Serial.println();
  }
}
