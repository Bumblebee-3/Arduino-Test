

/*---------- [LIBRARIES] ----------*/

#include <Servo.h>

/*---------- [-/LIBRARIES\-] ----------*/


Servo myservo;

/*---------- [VARIABLES] ----------*/

//Pin Variables
const int trigPin = 3;//UltraSonic Sensor pin (output)
const int echoPin = 9;//UltraSonic Sensor pin (input)
const int buzz = 7;//buzzer pin (output)
const int servo = 6;//servo data pin (output)



//Other Variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int cm;
int pos = 0;// Servo Position pins

/*---------- [-/VARIABLES\-] ----------*/


/*---------- [FUNCTIONS] ----------*/

/*----- [Rings] -----*/

//ring one (not very close)
void ring1(){
  digitalWrite(buzz,HIGH);
  delay(1000);
  digitalWrite(buzz,LOW);
  delay(1000);
}

//ring 2 (close)
void ring2(){
  digitalWrite(buzz,HIGH);
  delay(500);
  digitalWrite(buzz,LOW);
  delay(500);
  digitalWrite(buzz,HIGH);
  delay(500);
  digitalWrite(buzz,LOW);
  delay(500);
}

//ring 3 (very close)
void ring3(){
  digitalWrite(buzz,HIGH);
  delay(2000);
}

//no tone (not in danger)
void notone(){
  digitalWrite(buzz,LOW);
}

/*----- [Rings] -----*/


//sensor code
void sensor(){
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  cm = distance;
  /*---------- [CONDITIONS] ----------*/

  //checking if distance is lesser than 80 but also greater than 50 
  if (cm<=80 && cm>50){
    ring1();
  }

  //checking if distance is lesser than 50 but also greater than 30 
  else if (cm<=50 && cm>30) {
    ring2();
  }

  //checking if distance is lesser than 30
  else if (cm<=30){
    ring3();
  }
  else {
    notone();
  }
  /*---------- [CONDITIONS] ----------*/
}

//main code (servo motor)
void initialize(){
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    sensor();
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    sensor();
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

// void setup code in a function
void setupCode(){
  //attaching servo 
  myservo.attach(servo);
  //Declaring the pin modes (Input or Output)
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzz,OUTPUT);
  digitalWrite(buzz,LOW);
}

/*---------- [FUNCTIONS] ----------*/



/*---------- [VOID SETUP]-(Runs only once i.e. at the starting of the program) ----------*/

void setup() { 
  setupCode();
  Serial.begin(9600);
}

/*---------- [VOID SETUP]-(Runs only once i.e. at the starting of the program) ----------*/


/*---------- [VOID LOOP] - {Main Code} (runs throughout) ----------*/

void loop(){
  initialize();// Motor / main code callback
  sensor();//Sensor callback
}

/*---------- [VOID LOOP] - {Main Code} (runs throughout) ----------*/
