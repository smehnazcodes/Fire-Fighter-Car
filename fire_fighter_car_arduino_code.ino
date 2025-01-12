//Arduino Bluetooth Controlled Car//
//Bluetooth TX pin goes to Arduino Digital 0 (RX)
//Bluetooth RX pin goes to Arduino Digital 1 (TX)
//Servo 1 = 10
//Servo 2 = 9


#include <AFMotor.h>
#include <Servo.h> 

Servo fireServo;
int angle=90;
int flamePinRight = 2;
int flamePinLeft = 13;
int Flame1;
int Flame2;

int buzzer = A3;

int RELAY_PIN = 10;

//initial motors pin
AF_DCMotor motor1(1); 
AF_DCMotor motor2(2); 
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);


char command; 

void setup() 
{ 
  pinMode(buzzer, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(flamePinRight, INPUT); 
   pinMode(flamePinLeft, INPUT);      
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  fireServo.attach(9);
  fireServo.write(90);
  
}

void loop(){

 
  
  
  
  if(Serial.available() > 0){ 
    command = Serial.read(); 
    Stop(); //initialize with motors stoped
    //Change pin mode only if new command is different from previous.   
    Serial.println(command);
    switch(command){
    case 'F':  
      forward();
      break;
    case 'B':  
       back();
      break;
    case 'L':  
      left();
      break;
    case 'R':
      right();
      break;
    case 'W':
      servoLeft();
      break;
    case 'U':
      servoRight();
      break;
     case 'V':
     
      pump();
      break;
    }
  }
  flameDetect(); 
}

void pump (){
  digitalWrite(RELAY_PIN, LOW);
    delay(200);
     digitalWrite(RELAY_PIN, HIGH);
   
  
}

void servoLeft(){
  
    angle = angle +10;
    fireServo.write(angle);
  
  
  
}

void servoRight(){
  
    angle = angle -10;
    fireServo.write(angle);
   
  
}

void forward()
{
  motor1.setSpeed(150); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(150); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(150);//Define maximum velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(150);//Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}

void back()
{
  motor1.setSpeed(150); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(150); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(150); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(150); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

void left()
{
  motor1.setSpeed(0); //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release the button
  motor2.setSpeed(0); //Define minimum velocity
  motor2.run(RELEASE); //rotate the motor clockwise
  motor3.setSpeed(150); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(150); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
}

void right()
{
  motor1.setSpeed(150); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(150); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(0); //Define minimum velocity
  motor3.run(RELEASE); //stop the motor when release the button
  motor4.setSpeed(0); //Define minimum velocity
  motor4.run(RELEASE); //stop the motor when release the button
} 

void Stop()
{
  motor1.setSpeed(0); //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release the button
  motor2.setSpeed(0); //Define minimum velocity
  motor2.run(RELEASE); //rotate the motor clockwise
  motor3.setSpeed(0); //Define minimum velocity
  motor3.run(RELEASE); //stop the motor when release the button
  motor4.setSpeed(0); //Define minimum velocity
  motor4.run(RELEASE); //stop the motor when release the button
}

void flameDetect() {
  
  Flame1 = digitalRead(flamePinRight);
  
  Flame2 = digitalRead(flamePinLeft);
  
  
  if (Flame1== 0)
  {
    Serial.println("Fire!!!");
    //lcd.setCursor(0,0);
    //lcd.print("Fire Detected");
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(1000); // ...for 1 sec.
    noTone(buzzer); // Stop sound...
    delay(1000); // ...for 1se
   
  }
  else
  {
    Serial.println("No worries");
    //lcd.setCursor(0,0);
    //lcd.print("No worries");
   
  }

  if (Flame2== 0)
  {
    Serial.println("Fire!!!");
    //lcd.setCursor(0,1);
    //lcd.print("Fire Detected");
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(1000); // ...for 1 sec.
    noTone(buzzer); // Stop sound...
    delay(1000); // ...for 1sec.
   
  }
  else
  {
    Serial.println("No worries");
    //lcd.setCursor(0,1);
    //lcd.print("No worries");
   
  }
  
}
