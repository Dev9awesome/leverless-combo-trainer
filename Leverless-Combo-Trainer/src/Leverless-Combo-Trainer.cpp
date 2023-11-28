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

void setup() {
  Serial.begin(9600);
  ledMatrix.begin();
  ledMatrix.show();

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
