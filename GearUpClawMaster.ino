/* ============================================================
   GearUp Claw Master  -  FTC Team #31242 (GearUp)
   ESP32 + PCA9685 WiFi-controlled robot arm

   Phone joins WiFi "GearUp-Arm" (pass 12345678)
   Open http://192.168.4.1 and drag the sliders.

   Channels:
     CH0  Lower / shoulder  MG995   (inverted in code)
     CH1  Arm / elbow       MG995
     CH2  Claw              MG995
     CH3  Base              MG996R  continuous rotation
   ============================================================ */

#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_PWMServoDriver.h>
#include "html.h"          // web page lives in its own file

// ---------- WiFi access point ----------
const char* AP_SSID = "GearUp-Arm";
const char* AP_PASS = "12345678";

// ---------- Hardware objects ----------
Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);
WebServer server(80);

// ---------- Servo timing ----------
// 50 Hz = 20 ms per frame = 4096 ticks, so 1 tick is about 4.88 us
#define PWM_FREQ      50
#define SERVO_MIN_US  500    // 0.5 ms -> 0 deg   (102 ticks)
#define SERVO_MAX_US  2500   // 2.5 ms -> 180 deg (512 ticks)

// ---------- Channel map ----------
#define CH_LOWER  0
#define CH_ARM    1
#define CH_CLAW   2
#define CH_BASE   3          // continuous rotation: 90 = STOP

// ---------- Continuous base tuning ----------
#define BASE_STOP      90    // creeping? try 89 or 91
#define BASE_DEADBAND  6     // 84..96 all count as STOP

// Last value sent to each joint: Lower, Arm, Claw, Base
int angles[4] = {90, 90, 90, 90};

// ---------- Team logo (served at /logo) ----------
// Replace this line with the full LOGO_DATA array from your original file.
const uint8_t LOGO_DATA[] PROGMEM = { 0xFF, 0xD8 /* ...rest of logo... */ };
const int LOGO_LEN = sizeof(LOGO_DATA);

// Angle (0-180) -> PCA9685 ticks
int degreesToTicks(int deg) {
  deg = constrain(deg, 0, 180);
  long us = map(deg, 0, 180, SERVO_MIN_US, SERVO_MAX_US);
  return (int)(us * 4096L / 20000L);
}

// Send an angle to one channel
void setServo(uint8_t ch, int deg) {
  pca.setPWM(ch, 0, degreesToTicks(deg));
}

// Continuous base: sets SPEED + DIRECTION, not an angle
//   90 = stop, below 90 = one way, above 90 = the other way
void setBase(int v) {
  v = constrain(v, 0, 180);
  if (abs(v - BASE_STOP) <= BASE_DEADBAND) v = BASE_STOP;  // snap to a true stop
  setServo(CH_BASE, v);
}

// ---------- Web routes ----------
// GET /  -> control page
void handleRoot() {
  server.send_P(200, "text/html", MAIN_page);
}

// GET /logo -> team logo JPEG
void handleLogo() {
  server.send_P(200, "image/jpeg", (const char*)LOGO_DATA, LOGO_LEN);
}

// GET /set?servo=NAME&angle=VALUE -> move one joint
void handleSet() {
  if (!server.hasArg("servo") || !server.hasArg("angle")) {
    server.send(400, "text/plain", "missing servo or angle");
    return;
  }
  String name = server.arg("servo");
  int angle = constrain(server.arg("angle").toInt(), 0, 180);

  if      (name == "Base")  { angles[3] = angle; setBase(angle); }                 // speed + direction
  else if (name == "Lower") { angles[0] = angle; setServo(CH_LOWER, 180 - angle); } // inverted
  else if (name == "Arm")   { angles[1] = angle; setServo(CH_ARM,  angle); }
  else if (name == "Claw")  { angles[2] = angle; setServo(CH_CLAW, angle); }
  else { server.send(400, "text/plain", "unknown servo"); return; }

  Serial.printf("[SET] %s -> %d\n", name.c_str(), angle);
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);            // SDA = 21, SCL = 22
  pca.begin();
  pca.setPWMFreq(PWM_FREQ);
  delay(10);

  // Center the positional joints, stop the base
  setServo(CH_LOWER, 180 - 90);
  setServo(CH_ARM,   90);
  setServo(CH_CLAW,  90);
  setBase(BASE_STOP);

  WiFi.softAP(AP_SSID, AP_PASS);
  Serial.print("AP up. Open http://");
  Serial.println(WiFi.softAPIP());   // 192.168.4.1

  server.on("/",     handleRoot);
  server.on("/logo", handleLogo);
  server.on("/set",  handleSet);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();          // answer phone requests
}
File 2: html.h
#ifndef HTML_H
#define HTML_H

const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>GearUp Claw Master</title>
<style>
  body{margin:0;font-family:Arial,sans-serif;background:#111;color:#eee;text-align:center}
  header{padding:16px 0 4px}
  header img{height:64px}
  h1{font-size:22px;color:#c9a84c;margin:8px 0}
  .card{background:#1c1c1c;margin:12px auto;padding:14px;border-radius:12px;max-width:420px}
  .card h2{margin:0 0 4px;font-size:17px}
  .val{font-size:15px;color:#c9a84c;margin-bottom:6px}
  .hint{font-size:12px;color:#888}
  input[type=range]{width:90%;height:32px}
  button{background:#c9a84c;color:#111;border:0;border-radius:8px;padding:12px 28px;font-size:16px;margin:12px}
  #st{color:#aaa;font-size:14px;padding-bottom:24px}
</style>
</head>
<body>
<header>
  <img src="/logo" alt="GearUp" onerror="this.style.display='none'">
  <h1>GearUp Claw Master</h1>
</header>

<div class="card">
  <h2>Base (360°)</h2>
  <div class="val" id="vBase">Stopped</div>
  <input type="range" id="sBase" min="0" max="180" value="90"
         oninput="baseMove(this.value)"
         onmouseup="baseStop()" ontouchend="baseStop()" onchange="baseStop()">
  <div class="hint">Hold off-center to spin. Let go to stop.</div>
</div>

<div class="card">
  <h2>Lower (shoulder)</h2>
  <div class="val" id="vLower">90°</div>
  <input type="range" id="sLower" min="0" max="180" value="90" oninput="move('Lower', this.value)">
</div>

<div class="card">
  <h2>Arm (elbow)</h2>
  <div class="val" id="vArm">90°</div>
  <input type="range" id="sArm" min="0" max="180" value="90" oninput="move('Arm', this.value)">
</div>

<div class="card">
  <h2>Claw</h2>
  <div class="val" id="vClaw">90°</div>
  <input type="range" id="sClaw" min="0" max="180" value="90" oninput="move('Claw', this.value)">
</div>

<button onclick="centerAll()">Center All</button>
<div id="st">Ready</div>

<script>
  // One request per joint at a time. If the slider moves while a request
  // is in flight, remember only the newest value and send it next,
  // so the final position (and the base STOP) is never lost.
  var busy = {}, waiting = {};

  function send(name, val) {
    if (busy[name]) { waiting[name] = val; return; }
    busy[name] = true;
    fetch('/set?servo=' + name + '&angle=' + val)
      .then(function (r) {
        document.getElementById('st').textContent = r.ok ? (name + ' → ' + val) : 'Error';
      })
      .catch(function () {
        document.getElementById('st').textContent = 'Connection lost';
      })
      .finally(function () {
        busy[name] = false;
        if (waiting[name] !== undefined) {
          var v = waiting[name]; delete waiting[name]; send(name, v);
        }
      });
  }

  function move(name, val) {
    document.getElementById('v' + name).innerHTML = val + '°';
    send(name, val);
  }

  function baseLabel(v) {
    v = parseInt(v);
    if (Math.abs(v - 90) <= 6) return 'Stopped';
    return v < 90 ? 'Spinning left' : 'Spinning right';
  }

  function baseMove(v) {
    document.getElementById('vBase').textContent = baseLabel(v);
    send('Base', v);
  }

  function baseStop() {
    document.getElementById('sBase').value = 90;
    baseMove(90);
  }

  function centerAll() {
    ['Lower', 'Arm', 'Claw'].forEach(function (n) {
      document.getElementById('s' + n).value = 90;
      move(n, 90);
    });
    baseStop();
  }
</script>
</body>
</html>
)rawliteral";

#endif
