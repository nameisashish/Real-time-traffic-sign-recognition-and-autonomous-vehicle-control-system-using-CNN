#define enA 10  // Enable1 L298 Pin enA 
#define in1 9   // Motor1 L298 Pin in1 
#define in2 8   // Motor1 L298 Pin in2 
#define in3 7   // Motor2 L298 Pin in3 
#define in4 6   // Motor2 L298 Pin in4 
#define enB 5   // Enable2 L298 Pin enB 
#define L_S A0  // IR sensor Left
#define R_S A1  // IR sensor Right
#define echo A2    // Echo pin
#define trigger A3 // Trigger pin
#define servo A5

int Set = 20;
int distance_L, distance_F, distance_R; 

void setup() { // Put your setup code here, to run once
  Serial.begin(9600); // Start serial communication at 9600bps
  pinMode(R_S, INPUT);    // Declare IR sensor as input  
  pinMode(L_S, INPUT);    // Declare IR sensor as input
  pinMode(echo, INPUT);   // Declare ultrasonic sensor Echo pin as input
  pinMode(trigger, OUTPUT); // Declare ultrasonic sensor Trigger pin as Output  
  pinMode(enA, OUTPUT);   // Declare as output for L298 Pin enA 
  pinMode(in1, OUTPUT);   // Declare as output for L298 Pin in1 
  pinMode(in2, OUTPUT);   // Declare as output for L298 Pin in2 
  pinMode(in3, OUTPUT);   // Declare as output for L298 Pin in3   
  pinMode(in4, OUTPUT);   // Declare as output for L298 Pin in4 
  pinMode(enB, OUTPUT);   // Declare as output for L298 Pin enB 
  analogWrite(enA, 100);  // Write Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
  analogWrite(enB, 100);  // Write Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 
  pinMode(servo, OUTPUT);
  for (int angle = 70; angle <= 140; angle += 5) {
    servoPulse(servo, angle);  
  }
  for (int angle = 140; angle >= 0; angle -= 5) {
    servoPulse(servo, angle);  
  }
  for (int angle = 0; angle <= 70; angle += 5) {
    servoPulse(servo, angle);  
  }
  distance_F = Ultrasonic_read();
  delay(500);
}

void loop() {  
  //==============================================
  //     Line Follower and Obstacle Avoiding
  //==============================================  
  distance_F = Ultrasonic_read();
  Serial.print("D F="); Serial.println(distance_F);
  // If Right Sensor and Left Sensor are at White color then it will call forward function
  if ((digitalRead(R_S) == 0) && (digitalRead(L_S) == 0)) {
    if (distance_F > Set) {
      forword();
    } else {
      Check_side();
    }  
  }  
  // If Right Sensor is Black and Left Sensor is White then it will call turn Right function
  else if ((digitalRead(R_S) == 1) && (digitalRead(L_S) == 0)) {
    turnRight();
  }  
  // If Right Sensor is White and Left Sensor is Black then it will call turn Left function
  else if ((digitalRead(R_S) == 0) && (digitalRead(L_S) == 1)) {
    turnLeft();
  } 
  delay(10);
}

void servoPulse(int pin, int angle) {
  int pwm = (angle * 11) + 500; // Convert angle to microseconds
  digitalWrite(pin, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(pin, LOW);
  delay(50); // Refresh cycle of servo
}

//**********************Ultrasonic_read****************************
long Ultrasonic_read() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  long time = pulseIn(echo, HIGH);
  return time / 29 / 2;
}

void compareDistance() {
  if (distance_L > distance_R) {
    turnLeft();
    delay(600);
    forword();
    delay(700);
    turnRight();
    delay(600);
    forword();
    delay(700);
    turnRight();
    delay(600);
  } else {
    turnRight();
    delay(600);
    forword();
    delay(700);
    turnLeft();
    delay(600);
    forword();
    delay(700);  
    turnLeft();
    delay(600);
  }
}

void Check_side() {
  Stop();
  delay(100);
  for (int angle = 70; angle <= 140; angle += 5) {
    servoPulse(servo, angle);  
  }
  delay(300);
  distance_R = Ultrasonic_read();
  Serial.print("D R="); Serial.println(distance_R);
  delay(100);
  for (int angle = 140; angle >= 0; angle -= 5) {
    servoPulse(servo, angle);  
  }
  delay(500);
  distance_L = Ultrasonic_read();
  Serial.print("D L="); Serial.println(distance_L);
  delay(100);
  for (int angle = 0; angle <= 70; angle += 5) {
    servoPulse(servo, angle);  
  }
  delay(300);
  compareDistance();
}

void forword() {  // Move forward
  digitalWrite(in1, HIGH); // Left Motor forward
  digitalWrite(in2, LOW);  // Left Motor backward
  digitalWrite(in3, LOW);  // Right Motor forward
  digitalWrite(in4, HIGH); // Right Motor backward
}

void backword() { // Move backward
  digitalWrite(in1, LOW);  // Left Motor backward
  digitalWrite(in2, HIGH); // Left Motor forward
  digitalWrite(in3, HIGH); // Right Motor backward
  digitalWrite(in4, LOW);  // Right Motor forward
}

void turnRight() { // Turn right
  digitalWrite(in1, HIGH); // Left Motor forward
  digitalWrite(in2, LOW);  // Left Motor backward
  digitalWrite(in3, HIGH); // Right Motor backward
  digitalWrite(in4, LOW);  // Right Motor forward
}

void turnLeft() { // Turn left
  digitalWrite(in1, LOW);  // Left Motor backward
  digitalWrite(in2, HIGH); // Left Motor forward
  digitalWrite(in3, LOW);  // Right Motor forward
  digitalWrite(in4, HIGH); // Right Motor backward
}

void Stop() { // Stop
  digitalWrite(in1, LOW); // Left Motor backward
  digitalWrite(in2, LOW); // Left Motor forward
  digitalWrite(in3, LOW); // Right Motor forward
  digitalWrite(in4, LOW); // Right Motor backward
}