
// INPUT: Potentiometer should be connected to 5V and GND
int potPin = A3; // Potentiometer output connected to analog pin 3
int potVal = 0; // Variable to store the input from the potentiometer

bool running = true; //flag used to continue the program

void setup()
{
  Serial.begin(9600); //baud output
}

// Main program
void loop()
{
  if(running){ //continue running
    potVal = analogRead(potPin);   // read the potentiometer value at the input pin

    Serial.println(potVal); //literally just print the value out
    delay(1);

    if(potVal == 0 ){
      running = false;
    }
  }
}