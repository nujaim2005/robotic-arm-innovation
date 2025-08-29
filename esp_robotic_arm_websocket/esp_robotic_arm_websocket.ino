#include <ESP32Servo.h>
#include <WiFi.h>
#include <WebSocketsServer.h>

const char* ssid = "Mayur 5g";
const char* password = "pass1234";

WebSocketsServer webSocket = WebSocketsServer(80);

static const int servoPin1 = 12; 
static const int servoPin2 = 14; 
static const int servoPin3 = 27; 
static const int servoPin4 = 26;
static const int servoPin5 = 25; 
static const int servoPin6 = 33;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int angle1 = 90;
int angle2 = 90;
int angle3 = 90;
int angle4 = 90;
int angle5 = 90;
int angle6 = 90;

int angle1new;
int angle2new, angle3new, angle4new, angle5new, angle6new;

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_TEXT:
      {
        String msg = (char*)payload;
        angle1new = msg.substring(0, msg.indexOf(',')).toInt();
        msg = msg.substring(msg.indexOf(',') + 1);
        angle2new = msg.substring(0, msg.indexOf(',')).toInt();
        msg = msg.substring(msg.indexOf(',') + 1);
        angle3new = msg.substring(0, msg.indexOf(',')).toInt();
        msg = msg.substring(msg.indexOf(',') + 1);
        angle4new = msg.substring(0, msg.indexOf(',')).toInt();
        msg = msg.substring(msg.indexOf(',') + 1);
        angle5new = msg.substring(0, msg.indexOf(',')).toInt();
        msg = msg.substring(msg.indexOf(',') + 1);
        angle6new = msg.toInt();
        
        if (angle2new <= 5) { 
          angle2new = 5;
        }
        if (angle6new >= 90) {
          angle6new = 90;
        }

        Serial.print("angle1: ");
        Serial.println(angle1new);
        Serial.print("angle2: ");
        Serial.println(angle2new);
        Serial.print("angle3: ");
        Serial.println(angle3new);
        Serial.print("angle4: ");
        Serial.println(angle4new);
        Serial.print("angle5: ");
        Serial.println(angle5new);
        Serial.print("angle6: ");
        Serial.println(angle6new);

        Serial.print("\nMoving Servo 1");
        moveServoLinear(servo1, angle1, angle1new);
        angle1 = angle1new;
        Serial.print("\nMoving Servo 2");
        moveServoLinear(servo2, angle2, angle2new);
        angle2 = angle2new;
        Serial.print("\nMoving Servo 3");
        moveServoLinear(servo3, angle3, angle3new);
        angle3 = angle3new;
        Serial.print("\nMoving Servo 4");
        moveServoLinear(servo4, angle4, angle4new);
        angle4 = angle4new;
        Serial.print("\nMoving Servo 5");
        moveServoLinear(servo5, angle5, angle5new);
        angle5 = angle5new;
        Serial.print("\nMoving Servo 6");
        moveServoLinear(servo6, angle6, angle6new);
        angle6 = angle6new;
        Serial.println();
        Serial.println("------done------");
        webSocket.sendTXT(num, "done");

        // Parse the received payload if needed
        // Process the data received from Python
        // Example: digitalWrite(LED_BUILTIN, payload[0] == '1' ? HIGH : LOW);
        break;
      }
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
  }
}

void moveServoLinear(Servo& servo, int currentAngle, int targetAngle) {
  if (currentAngle == targetAngle) {
    servo.write(targetAngle);
    return;
  }
  int step = (targetAngle > currentAngle) ? 1 : -1;
  for (int angle = currentAngle; angle != targetAngle; angle += step) {
    if (angle % 10 == 0)
      Serial.print(".");
    servo.write(angle);
    delay(8); // Adjust delay as needed
  }
  servo.write(targetAngle);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);
  servo5.attach(servoPin5);
  servo6.attach(servoPin6);

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
}
