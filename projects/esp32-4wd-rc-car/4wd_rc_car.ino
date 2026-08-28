#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

// ---------------- MOTOR PINS ----------------
#define LF 27   // Left Forward
#define LB 26   // Left Backward
#define RF 25   // Right Forward
#define RB 33   // Right Backward

// ---------------- WiFi (HOTSPOT MODE) ----------------
const char* ssid = "RC_CAR";
const char* password = "123456789";

WebServer server(80);
WebSocketsServer ws(81);

// ---------------- MOTOR FUNCTIONS ----------------

void stop_car() {
  digitalWrite(LF, LOW);
  digitalWrite(LB, LOW);
  digitalWrite(RF, LOW);
  digitalWrite(RB, LOW);
}

// FORWARD
void forward() {
  // Left side forward
  digitalWrite(LF, HIGH);
  digitalWrite(LB, LOW);

  // Right side REVERSED
  digitalWrite(RF, LOW);
  digitalWrite(RB, HIGH);
}

// BACKWARD
void backward() {
  // Left side backward
  digitalWrite(LF, LOW);
  digitalWrite(LB, HIGH);

  // Right side REVERSED
  digitalWrite(RF, HIGH);
  digitalWrite(RB, LOW);
}

// LEFT TURN
void left() {
  // Left side forward
  digitalWrite(LF, HIGH);
  digitalWrite(LB, LOW);

  // Right side backward
  digitalWrite(RF, HIGH);
  digitalWrite(RB, LOW);
}

// RIGHT TURN
void right() {
    // Left side backward
  digitalWrite(LF, LOW);
  digitalWrite(LB, HIGH);

  // Right side forward
  digitalWrite(RF, LOW);
  digitalWrite(RB, HIGH);

}
// ---------------- WEBSOCKET HANDLER ----------------

void handle_ws(uint8_t num, WStype_t type, uint8_t * payload, size_t len) {

  switch (type) {

    case WStype_TEXT: {
      String cmd = String((char*)payload);

      if (cmd == "forward") forward();
      else if (cmd == "backward") backward();
      else if (cmd == "left") left();
      else if (cmd == "right") right();
      else stop_car();

      break;
    }

    case WStype_DISCONNECTED:
      stop_car();
      break;

    default:
      break;
  }
}

// ---------------- WEB PAGE ----------------
String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>ESP32 RC</title>

<style>
body{
  background:#111;
  color:white;
  display:flex;
  justify-content:center;
  align-items:center;
  height:100vh;
  margin:0;
  font-family:Arial;
}

.controller{
  display:grid;
  grid-template-columns:100px 100px 100px;
  grid-template-rows:100px 100px 100px;
  gap:15px;
}

button{
  font-size:40px;
  border:none;
  border-radius:15px;
  background:#00aaff;
  color:white;
  touch-action:none;
}
</style>
</head>

<body>

<div class="controller">

  <div></div>
  <button id="up">⬆️</button>
  <div></div>

  <button id="left">⬅️</button>
  <div></div>
  <button id="right">➡️</button>

  <div></div>
  <button id="down">⬇️</button>
  <div></div>

</div>

<script>

let ws = new WebSocket("ws://" + location.hostname + ":81/");

function send(cmd){
  if(ws.readyState === 1){
    ws.send(cmd);
  }
}

// HOLD BUTTON LOGIC (IMPORTANT FIX)
function bind(btn, cmd){

  btn.addEventListener("touchstart", e=>{
    e.preventDefault();
    send(cmd);
  });

  btn.addEventListener("touchend", e=>{
    e.preventDefault();
    send("stop");
  });

  btn.addEventListener("mousedown", ()=>{
    send(cmd);
  });

  btn.addEventListener("mouseup", ()=>{
    send("stop");
  });

  btn.addEventListener("mouseleave", ()=>{
    send("stop");
  });
}

bind(document.getElementById("up"), "forward");
bind(document.getElementById("down"), "backward");
bind(document.getElementById("left"), "left");
bind(document.getElementById("right"), "right");

</script>

</body>
</html>
)rawliteral";
// ---------------- HANDLERS ----------------

void handle_root() {
  server.send(200, "text/html", page);
}

// ---------------- SETUP ----------------

void setup() {
  Serial.begin(115200);
  delay(2000);   // IMPORTANT (prevents missing Serial output)

  Serial.println("\nBOOTING ESP32...");

  // Motor pins
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);

  stop_car();

  // ---------------- HOTSPOT MODE FIX ----------------
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  WiFi.setSleep(false);

  Serial.println("WiFi Hotspot Started");
  Serial.print("SSID: ");
  Serial.println(ssid);

  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
  // ---------------- HTTP (ONLY FOR PAGE) ----------------
  server.on("/", handle_root);
  server.begin();
  Serial.println("HTTP Server Started");

  // ---------------- WEBSOCKET ----------------
  ws.begin();
  ws.onEvent(handle_ws);
  Serial.println("WebSocket Started");


}

// ---------------- LOOP ----------------

void loop() {
  server.handleClient();  // webpage only
  ws.loop();              // real-time control
}
