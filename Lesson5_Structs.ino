/*
  Lesson 5 - Structs
  GearUp Robotics - Arduino & C++ Starter Lab

  Goal: bundle related information into your OWN data type.
  We'll describe the joints of a robot arm - the kind of
  thing you build for real on a GearUp robot.
  Hardware: just your Arduino board + USB cable.
*/

// A struct groups related values under one name.
struct Joint {
  String name;      // what the joint is called
  int    minAngle;  // lowest safe angle
  int    maxAngle;  // highest safe angle
  int    angle;     // where it is right now
};

// An array of structs: four joints, like a real claw arm.
Joint arm[] = {
  {"Base",     0,  180,  90},
  {"Shoulder", 15, 165,  90},
  {"Elbow",    0,  180,  45},
  {"Claw",     30, 110,  30}
};
int jointCount = sizeof(arm) / sizeof(arm[0]);

// A function that takes a struct and checks one of its fields.
bool isSafe(Joint j) {
  return (j.angle >= j.minAngle && j.angle <= j.maxAngle);
}

void report() {
  for (int i = 0; i < jointCount; i++) {
    Serial.print(arm[i].name);          // read a field with a dot
    Serial.print(": ");
    Serial.print(arm[i].angle);
    Serial.print(" deg  -> ");
    Serial.println(isSafe(arm[i]) ? "OK" : "OUT OF RANGE!");
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  Serial.println("=== Lesson 5: Structs ===");

  report();

  // Change one field, then check again.
  Serial.println("Opening the claw to 200 degrees...");
  arm[3].angle = 200;                   // index 3 is the Claw
  report();
}

void loop() {
  // Nothing here - everything ran once in setup().
}
