#include <Servo.h>

Servo enemy1; 
int enemy1_location[] = {250, 330};
Servo enemy2; //512 is the potentiometer area's halfway point
int enemy2_location[] = {472, 552};
Servo enemy3; 
int enemy3_location[] = {730, 770};

// INPUT: Potentiometer should be connected to 5V and GND
int potPin = A3; // Potentiometer output connected to analog pin 3
int potVal = 0; // Variable to store the input from the potentiometer
int buttonPin = 7;


bool running = true; //flag used to continue the program
bool enemy1_on; 
bool enemy2_on; 
bool enemy3_on;

int randNumber;
int buttonState;

int timer = 2000;

void setup()
{
  Serial.begin(9600); //baud output
  startup_motors();
  pinMode(buttonPin, INPUT);

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));

}

// Main program
void loop()
{
  if(running){ //continue running
    // print a random number from 1 to 3
    randNumber = random(3)+1;
    //Serial.println(randNumber);

    //This code is only for testing. 
    potVal = analogRead(potPin);   // read the potentiometer value at the input pin
    //Serial.println(potVal); //literally just print the value out
    delay(1);

    if(timer == 0){
      extendServo(randNumber, potVal);
      timer = 2000;
    }else{
      timer--;
    }

    retractServo(determineArea(potVal));
    if(potVal == 0 ){
      running = false;
    }
  }
  buttonPush();
}

void startup_motors(){
  //Servo motor attaching
  enemy1.attach(2);
  enemy2.attach(3);
  enemy3.attach(4);
  //set position back to 0
  enemy1.write(0);
  enemy2.write(0);
  enemy3.write(0);
  //write flags
  enemy1_on = false;
  enemy2_on = false;
  enemy3_on = false;
}

void buttonPush(){
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    Serial.println("BUTTON PUSHED");
  }else{
    Serial.println("BUTTON NOT PUSHED");
  }
}

void extendServo(int num, int potVal){
  int currPos = determineArea(potVal);
  if(num == 1 && !enemy1_on && currPos != 1){
    //servo 1
    Serial.println("Enemy 1 Extend");
    enemy1.write(180);
    enemy1_on = true;
  }else if(num == 2 && !enemy2_on && currPos != 2){
    //servo 2
    Serial.println("Enemy 2 Extend");
    enemy2.write(180);
    enemy2_on = true;
  }else if(num == 3 && !enemy3_on && currPos != 3){
    //servo 3
    Serial.println("Enemy 3 Extend");
    enemy3.write(180);
    enemy3_on = true;
  }else{
    //Serial.println(num);
  }
}

void retractServo(int position){
  if(enemy1_on && position == 1){
    enemy1.write(0);
    enemy1_on = false;
    Serial.println("Enemy 1 hit");
  }else if(enemy2_on && position == 2){
    enemy2.write(0);
    enemy2_on = false;
    Serial.println("Enemy 2 hit");
  }else if(enemy3_on && position == 3){
    enemy3.write(0);
    enemy3_on = false;
    Serial.println("Enemy 3 hit");
  }
}

int determineArea(int potVal){
  if(potVal > enemy1_location[0] && potVal < enemy1_location[1]){
    return 1;
  }else if (potVal > enemy2_location[0] && potVal < enemy2_location[1]){
    return 2;
  }else if (potVal > enemy3_location[0] && potVal < enemy3_location[1]){
    return 3;
  }else{
    return 0;
  }
}