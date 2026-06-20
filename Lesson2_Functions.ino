/*
  Lesson 2 - Functions & Loops
  GearUp Robotics - Arduino & C++ Starter Lab

  Goal: package code into reusable functions, and repeat
  actions with for-loops and while-loops.
  Hardware: just your Arduino board + USB cable.
*/

const int led = LED_BUILTIN;

// A function with PARAMETERS but no return value (void).
void blink(int times, int speedMs) {
  for (int i = 0; i < times; i++) {    // for-loop: repeat 'times' times
    digitalWrite(led, HIGH);
    delay(speedMs);
    digitalWrite(led, LOW);
    delay(speedMs);
  }
}

// A function that RETURNS a value back to whoever called it.
int addUp(int from, int to) {
  int total = 0;                       // 'total' only exists inside here (scope)
  for (int n = from; n <= to; n++) {
    total += n;                        // shorthand for total = total + n
  }
  return total;
}

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  Serial.println("=== Lesson 2: Functions & Loops ===");

  // Call the SAME function with different inputs.
  Serial.println("Three slow blinks...");
  blink(3, 400);

  Serial.println("Five fast blinks...");
  blink(5, 100);

  // Use a returned value.
  int sum = addUp(1, 10);
  Serial.print("1 + 2 + ... + 10 = ");
  Serial.println(sum);
}

void loop() {
  // A while-loop runs as long as its condition stays true.
  int countdown = 3;
  while (countdown > 0) {
    Serial.print("Launching in ");
    Serial.println(countdown);
    blink(1, 150);
    countdown--;                       // count down by one
    delay(700);
  }
  Serial.println("Liftoff! (pausing 3s)");
  delay(3000);
}
