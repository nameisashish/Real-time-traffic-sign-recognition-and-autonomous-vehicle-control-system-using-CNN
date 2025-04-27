#define enA 10    // Enable1 L298 Pin enA
#define in1 9     // Motor1 L298 Pin in1
#define in2 8     // Motor1 L298 Pin in2
#define in3 7     // Motor2 L298 Pin in3
#define in4 6     // Motor2 L298 Pin in4
#define enB 5     // Enable2 L298 Pin enB

#define L_S A0    // IR sensor Left
#define R_S A1    // IR sensor Right

void setup() {
  Serial.begin(115200);  // High baud rate for fast communication
  pinMode(R_S, INPUT);   // IR sensor Right as input
  pinMode(L_S, INPUT);   // IR sensor Left as input

  pinMode(enA, OUTPUT);  // L298 Pin enA as output
  pinMode(in1, OUTPUT);  // L298 Pin in1 as output
  pinMode(in2, OUTPUT);  // L298 Pin in2 as output
  pinMode(in3, OUTPUT);  // L298 Pin in3 as output
  pinMode(in4, OUTPUT);  // L298 Pin in4 as output
  pinMode(enB, OUTPUT);  // L298 Pin enB as output

  analogWrite(enA, 120); // Initial speed set to a realistic cruising value
  analogWrite(enB, 120);
  ahead();               // Start moving forward
  Serial.println("Setup complete, starting normal speed at PWM 120");
}

void loop() {
  // Check for serial commands first for priority
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case 'A':  // No passing or No entry
        stop();
        Serial.println("Command A: Stopped indefinitely");
        while (true); // Stop indefinitely
        break;
      case 'P':  // Stop
        stop();
        Serial.println("Command P: Stopped");
        break; // Python handles 5-second delay
      case 'L':  // Children crossing
        setSpeed(60);
        ahead();
        Serial.println("Command L: Reduced speed to PWM 60 (Children)");
        break;
      case 'D':  // Speed Limit 20 or 30
        if (Serial.available() > 0) {
          char subCommand = Serial.read();
          if (subCommand == '2') {
            setSpeed(70);  // Speed limit 20
            Serial.println("Command D2: Speed limit 20, PWM 70");
          } else {
            setSpeed(80);  // Speed limit 30
            Serial.println("Command D3: Speed limit 30, PWM 80");
          }
        } else {
          setSpeed(80); // Default to 30
          Serial.println("Command D: Default speed limit 30, PWM 80");
        }
        ahead();
        break;
      case 'I':  // Speed Limit 60, 70, 80, 100, 120
        if (Serial.available() > 0) {
          char speed = Serial.read();
          if (speed == '6') {
            setSpeed(120);     // Speed limit 60
            Serial.println("Command I6: Speed limit 60, PWM 120");
          } else if (speed == '7') {
            setSpeed(140);     // Speed limit 70
            Serial.println("Command I7: Speed limit 70, PWM 140");
          } else if (speed == '8') {
            setSpeed(160);     // Speed limit 80
            Serial.println("Command I8: Speed limit 80, PWM 160");
          } else if (speed == '1') {
            setSpeed(200);     // Speed limit 100
            Serial.println("Command I1: Speed limit 100, PWM 200");
          } else if (speed == '2') {
            setSpeed(255);     // Speed limit 120
            Serial.println("Command I2: Speed limit 120, PWM 255");
          } else {
            setSpeed(200);     // Default to 100
            Serial.println("Command I: Default speed limit 100, PWM 200");
          }
        } else {
          setSpeed(200); // Default to 100
          Serial.println("Command I: Default speed limit 100, PWM 200");
        }
        ahead();
        break;
      case 'C':  // Continue driving
        setSpeed(120); // Normal cruising speed
        ahead();
        Serial.println("Command C: Normal speed, PWM 120");
        break;
      default:
        Serial.println("Unknown command received");
        break;
    }
    // Clear buffer to prevent lag
    while (Serial.available() > 0) Serial.read();
  } else {
    // Line-following logic when no serial command
    int leftSensor = digitalRead(L_S);
    int rightSensor = digitalRead(R_S);

    if (leftSensor == LOW && rightSensor == LOW) {
      ahead();
    } else if (leftSensor == HIGH && rightSensor == LOW) {
      turnRightSlow();
    } else if (leftSensor == LOW && rightSensor == HIGH) {
      turnLeftSlow();
    } else {
      stop();
    }
  }
}

void ahead() {
  digitalWrite(in1, HIGH);  // Left Motor forward
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);   // Right Motor forward
  digitalWrite(in4, HIGH);
}

void turnRightSlow() {
  digitalWrite(in1, HIGH);  // Left Motor forward
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);   // Right Motor stop
  digitalWrite(in4, LOW);
}

void turnLeftSlow() {
  digitalWrite(in1, LOW);   // Left Motor stop
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);   // Right Motor forward
  digitalWrite(in4, HIGH);
}

void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void setSpeed(int speed) {
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}