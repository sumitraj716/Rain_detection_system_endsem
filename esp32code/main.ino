#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>
#include <SPIFFS.h>
#include <FS.h>

// WiFi credentials
const char* ssid = "Your wifi ssid";
const char* password = "Your wifi password";

// Hardware pins
const int rainSensorPin = 34;
const int lightPin = 15;
const int servoPin = 18;

WebServer server(80);
Servo myServo;

int rainValue = 0;
bool lightManualState = false;

int manualServoAngle = -1;   // -1 = auto mode, 0/90 = manual mode


String logs = "";

void log(String message) {
  Serial.println(message);
  logs += message + "<br>";
  if (logs.length() > 3000) logs = logs.substring(1000);  // Keep logs trimmed
}

void handleLogs() {
  server.send(200, "text/html", "<html><body><h2>ESP32 Logs</h2>" + logs + "</body></html>");
}

void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.begin(ssid, password);
  log("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); log(".");
  }
  log("\n✅ Connected! IP: " + WiFi.localIP().toString());

  pinMode(lightPin, OUTPUT);
  digitalWrite(lightPin, LOW);

  myServo.setPeriodHertz(50);
  myServo.attach(servoPin, 500, 2400); // 0.5ms to 2.4ms pulse width
  myServo.write(0);
  manualServoAngle = 0;

  if (!SPIFFS.begin(true)) {
    log("❌ SPIFFS Mount Failed");
    return;
  }

  // Serve static files
  server.on("/", HTTP_GET, []() {
    File file = SPIFFS.open("/index.html", "r");
    server.streamFile(file, "text/html");
    file.close();
  });

  server.on("/style.css", HTTP_GET, []() {
    File file = SPIFFS.open("/style.css", "r");
    server.streamFile(file, "text/css");
    file.close();
  });

  server.on("/script.js", HTTP_GET, []() {
    File file = SPIFFS.open("/script.js", "r");
    server.streamFile(file, "application/javascript");
    file.close();
  });

  server.on("/sounds/rain.mp3", HTTP_GET, []() {
    File file = SPIFFS.open("/sounds/rain.mp3", "r");
    server.streamFile(file, "audio/mpeg");
    file.close();
  });

  // Logs endpoints
  server.on("/logs", handleLogs);

  server.on("/downloadLogs", HTTP_GET, []() {
    File file = SPIFFS.open("/logs.txt", FILE_WRITE);
    if (!file) {
      server.send(500, "text/plain", "Failed to open file");
      return;
    }
    file.print(logs);
    file.close();

    file = SPIFFS.open("/logs.txt", FILE_READ);
    server.streamFile(file, "text/plain");
    file.close();
  });

  server.on("/rain", HTTP_GET, []() {
    String status = (rainValue < 2000) ? "Rain Detected" : "No Rain";
    String json = "{";
    json += "\"rain\":" + String(rainValue) + ",";
    json += "\"status\":\"" + status + "\",";
    json += "\"temperature\":\"28.6\",";
    json += "\"humidity\":\"55\"";
    json += "}";
    server.send(200, "application/json", json);
  });

  server.on("/toggleLight", HTTP_POST, []() {
    if (server.hasArg("state")) {
      String state = server.arg("state");
      lightManualState = (state == "on");
      digitalWrite(lightPin, lightManualState ? HIGH : LOW);
      log("🟡 Light manually toggled to: " + state);
    }
    server.send(200, "text/plain", "OK");
  });

  server.on("/toggleServo", HTTP_POST, []() {
  if (server.hasArg("angle")) {
    manualServoAngle = server.arg("angle").toInt(); // 0 or 90
    myServo.write(manualServoAngle);
    log("🔧 Servo manually moved to: " + String(manualServoAngle));
  }
  server.send(200, "text/plain", "OK");
});

  server.on("/resetServo", HTTP_POST, []() {
  manualServoAngle = -1;
  log("🔄 Servo returned to auto mode.");
  server.send(200, "text/plain", "OK");
});



  server.begin();
  log("🚀 Web server started!");
}

void loop() {
  server.handleClient();

  rainValue = analogRead(rainSensorPin);
  log("🌧 Rain Sensor Value: " + String(rainValue));

  // Auto Light Control (only if not manually overridden)
  if (!lightManualState && rainValue < 2000) {
    digitalWrite(lightPin, HIGH);
  } else if (!lightManualState) {
    digitalWrite(lightPin, LOW);
  }

  // Servo Control
  if (manualServoAngle == -1) {  // Auto mode
    if (rainValue < 2000) {
      myServo.write(90);
      log("Rain detected -- automove - 90");
    } else {
      myServo.write(0);
      log("Rain not detected -- automove - 0");
    }
  }

  delay(1000);
}
