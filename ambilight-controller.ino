#include <math.h>

const int GREEN = 3;
const int RED = 5;
const int BLUE = 9;

const int tempPot = A0;
const int dimPot = A1;

float dimFactor;
int colorTemp;

float redAmount;
float greenAmount;
float blueAmount;

void setup() {
  Serial.begin(9600);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);

  pinMode(tempPot, INPUT);
  pinMode(dimPot, INPUT);
}

void loop() {
  //Read both potentiometers
  dimFactor = analogRead(dimPot)/1023.0;        //The .0 is to wake-up the compiler to make this a float-division instead of an int-division :)
  colorTemp = (analogRead(tempPot)*4+1000);
  
  //debug
  Serial.print("colorTemp: ");
  Serial.print(colorTemp);
  Serial.print("; dimFactor: ");
  Serial.println(dimFactor);
  
  colorTemp = colorTemp/100;

  //Calculate Red
  if(colorTemp<=66) {
    redAmount = 255;  
  }
  else {
    redAmount = colorTemp - 60;
    redAmount = 329.698727446 * pow(redAmount, -0.1332047592);
    if(redAmount<0) { redAmount = 0; }
    if(redAmount>255) { redAmount = 255; }
  }

  //Calculate Green
  if(colorTemp<=66) {
    greenAmount = colorTemp;
    greenAmount = 99.4708025861 * log(greenAmount) - 161.1195681661;
    if(greenAmount<0) { greenAmount = 0; }
    if(greenAmount>255) { greenAmount = 255; }
  }
  else {
    greenAmount = colorTemp - 60;
    greenAmount = 288.1221695283 * pow(greenAmount, -0.0755148492);
    if(greenAmount<0) { greenAmount = 0; }
    if(greenAmount>255) { greenAmount = 255; }
  }

  //Calculate Blue
  if(colorTemp>=66) {
    blueAmount = 255;
  }
  else {
    if(colorTemp<=19) {
      blueAmount = 0;
    }
    else {
      blueAmount = colorTemp - 10;
      blueAmount = 138.5177312231 * log(blueAmount) - 305.0447927307;
      if(blueAmount<0) { blueAmount = 0; }
      if(blueAmount>255) { blueAmount = 255; }
    }
  }

  //Combine the calculated color values with the dimming factor:
  redAmount = redAmount * dimFactor;
  greenAmount = greenAmount * dimFactor;
  blueAmount = blueAmount * dimFactor;

  //Round the float values to ints so they can be analogWrite'd
  int redOut = round(redAmount);
  int greenOut = round(greenAmount);
  int blueOut = round(blueAmount);

  //Output to the LED-strip
  analogWrite(RED, redOut);
  analogWrite(GREEN, greenOut);
  analogWrite(BLUE, blueOut);
}
