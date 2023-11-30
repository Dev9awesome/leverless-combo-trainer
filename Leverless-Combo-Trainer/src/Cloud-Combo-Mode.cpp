/* 
 * Author: Dev Patel and Jaxen Lindsey
 * Date: November 28th, 2023
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "neomatrix.h"
#include "neopixel.h"


// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(DISABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

//Directional buttons
int leftPin = D0;
int downPin = D1;
int rightPin = D2;
int upPin = D3;
//Attack buttons
int Apin = D4;
int Bpin = D5;
int Cpin = D6;

int ledPin = D7; 
Adafruit_NeoMatrix ledMatrix = Adafruit_NeoMatrix(8, 8, ledPin,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE);


int leftSequence[32];
int rightSequence[32];
int downSequence[32];
int upSequence[32];
int ASequence[32];
int BSequence[32];
int CSequence[32];

void stringToIntArrParser(char webInput[128], int outArray[32]){
  int clearingArray[32] = {-1};
  outArray = clearingArray;

  char intStringHolder[5] = {"", "", "", "", '\0'};
  //'!' is the sentinel value. All web inputs should
  int currentOutIndex = 0;
  int currentHolderIndex = 0;
  for(int i = 0; webInput[i] != '!', i++){
    //if the next character is a space, then the int can be put into the out array.
    if(webInput[i] == ' '){
      outArray[currentOutIndex] = stoi(intStringHolder);
      //reset the holder for current string.
      currentHolderIndex = 0;
      intStringHolder = "";
      currentOutIndex++;
    }
    //Adds the next character to the holder
    else{
      intStringHolder[currentHolderIndex] = webInput[i];
      currentHolderIndex++;
    }
      
  }

}

void setLeft(char in[128]){
  stringToIntArrParser(in, leftSequence);
}
void setRight(char in[128]){
  stringToIntArrParser(in, rightSequence);
}
void setDown(char in[128]){
  stringToIntArrParser(in, downSequence);
}
void setUp(char in[128]){
  stringToIntArrParser(in, upSequence);
}
void setA(char in[128]){
  stringToIntArrParser(in, ASequence);
}
void setB(char in[128]){
  stringToIntArrParser(in, BSequence);
}
void setC(char in[128]){
  stringToIntArrParser(in, CSequence);
}



void setup() {
  Serial.begin(9600);
  ledMatrix.begin();
  ledMatrix.show();

  // Particle.variable("LeftCombo", leftSequence);
  // Particle.variable("RightCombo", rightSequence);
  // Particle.variable("DownCombo", downSequence);
  // Particle.variable("upCombo", upSequence);
  // Particle.variable("ACombo", ASequence);
  // Particle.variable("BCombo", BSequence);
  // Particle.variable("CCombo", CSequence);

  Particle.function("LeftCombo", setLeft);
  Particle.function("RightCombo", setRight);
  Particle.function("DownCombo", setDown);
  Particle.function("upCombo", setUp);
  Particle.function("ACombo", setA);
  Particle.function("BCombo", setB);
  Particle.function("CCombo", setC);

  ledMatrix.drawPixel(0, 0, ledMatrix.Color(128, 0, 0));

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
  // Log.info("Sending Hello World to the cloud!");
  // Particle.publish("Hello world!");
  // delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!
}
