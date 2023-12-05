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
int leftPin = D1;
int downPin = D2;
int rightPin = D3;
int upPin = D4;
//Attack buttons
int Apin = D5;
int Bpin = D6;
int Cpin = D7;

int ledPin = D0; 
Adafruit_NeoMatrix ledMatrix = Adafruit_NeoMatrix(8, 8, ledPin,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE);

void changeLED(int pin){
  int ledPos = -1;
  if(pin == leftPin){
    ledPos = 0;
  }
  else if(pin == downPin){
    ledPos = 1;
  }
  
  else if(pin == rightPin){
    ledPos = 2;
  }
  
  else if(pin == upPin){
    ledPos = 3;
  }
  
  else if(pin == Apin){
    ledPos = 5;
  }
  
  else if(pin == Bpin){
    ledPos = 6;
  }

  else if(pin == Cpin){
    ledPos = 7;
  }
  
  if(digitalRead(pin)){
    ledMatrix.drawPixel(ledPos, 0, ledMatrix.Color(128, 0, 0));
    ledMatrix.show();
  }
  else{
    ledMatrix.drawPixel(ledPos, 0, ledMatrix.Color(0, 0, 0));
    ledMatrix.show();
  }


}

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  ledMatrix.begin();
  ledMatrix.show();
  pinMode(leftPin, INPUT_PULLDOWN);
  pinMode(downPin, INPUT_PULLDOWN);
  pinMode(rightPin, INPUT_PULLDOWN);
  pinMode(upPin, INPUT_PULLDOWN);
  pinMode(Apin, INPUT_PULLDOWN);
  pinMode(Bpin, INPUT_PULLDOWN);
  pinMode(Cpin, INPUT_PULLDOWN);

  // ledMatrix.drawPixel(0, 0, ledMatrix.Color(128, 0, 0));

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  ledMatrix.show();
  // ledMatrix.drawPixel(4, 4, ledMatrix.Color(128, 0, 0));
  changeLED(leftPin);
  changeLED(downPin);
  changeLED(rightPin);
  changeLED(upPin);
  changeLED(Apin);
  changeLED(Bpin);
  changeLED(Cpin);

  
}
