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

// Directional buttons
int leftPin = D0;
int downPin = D1;
int rightPin = D2;
int upPin = D3;
// Attack buttons
int Apin = D4;
int Bpin = D5;
int Cpin = D6;

int ledPin = D7;
Adafruit_NeoMatrix ledMatrix = Adafruit_NeoMatrix(8, 8, ledPin,
                                                  NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT +
                                                      NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE);

int currLeft = 0, currRight = 0, currDown = 0, currUp = 0, currA = 0, currB = 0, currC = 0;
bool leftState = false, rightState = false, downState = false, upState = false, AState = false, BState = false, CState = false;

int leftSequence[32] = {-1};
int rightSequence[32] = {-1};
int downSequence[32] = {-1};
int upSequence[32] = {-1};
int ASequence[32] = {-1};
int BSequence[32] = {-1};
int CSequence[32] = {-1};

void stringToIntArrParser(char webInput[128], int outArray[32])
{
  int clearingArray[32] = {-1};
  outArray = clearingArray;

  char intStringHolder[5] = {"", "", "", "", '\0'};
  //'!' is the sentinel value. All web inputs should
  int currentOutIndex = 0;
  int currentHolderIndex = 0;
  for (int i = 0; webInput[i] != '!', i++)
  {
    // if the next character is a space, then the int can be put into the out array.
    if (webInput[i] == ' ')
    {
      outArray[currentOutIndex] = stoi(intStringHolder);
      // reset the holder for current string.
      currentHolderIndex = 0;
      intStringHolder = "";
      currentOutIndex++;
    }
    // Adds the next character to the holder
    else
    {
      intStringHolder[currentHolderIndex] = webInput[i];
      currentHolderIndex++;
    }
  }
}

void setLeft(char in[128])
{
  stringToIntArrParser(in, leftSequence);
}
void setRight(char in[128])
{
  stringToIntArrParser(in, rightSequence);
}
void setDown(char in[128])
{
  stringToIntArrParser(in, downSequence);
}
void setUp(char in[128])
{
  stringToIntArrParser(in, upSequence);
}
void setA(char in[128])
{
  stringToIntArrParser(in, ASequence);
}
void setB(char in[128])
{
  stringToIntArrParser(in, BSequence);
}
void setC(char in[128])
{
  stringToIntArrParser(in, CSequence);
}

void setup()
{
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
void loop()
{

  // Left Button Loop logic to read array and cause LED outputs
  // Left LED is at (0, 1) 
  int leftTimer = leftSequence[currLeft];

  if (leftTimer != -1 && leftTimer >= millis())
  {
    if (leftState)
    {
      ledMatrix.drawPixel(0, 1, ledMatrix.Color(0, 0, 0));
    }
    else
    {
      ledMatrix.drawPixel(0, 1, ledMatrix.Color(128, 0, 0));
    }
    leftState = -leftState;
    currLeft++;
  }
  else if (leftTime == -1)
  {
    // TODO: Check if redrawing every frame is cringe
    ledMatrix.drawPixel(0, 1, ledMatrix.Color(128, 0, 0));
  }

  // Right Button
  // Right LED is at (1, 1) 
  int rightTimer = rightSequence[currRight];

  if (rightTimer != -1 && rightTimer >= millis())
  {
    if (rightState)
    {
      ledMatrix.drawPixel(1, 1, ledMatrix.Color(0, 0, 0));
    }
    else
    {
      ledMatrix.drawPixel(1, 1, ledMatrix.Color(128, 0, 0));
    }
    rightState = -rightState;
    currLeft++;
  }
  else if (rightTime == -1)
  {
    // TODO: Check if redrawing every frame is cringe
    ledMatrix.drawPixel(1, 1, ledMatrix.Color(128, 0, 0));
  }

  // Down Button
  // Down LED is at (2, 1) 
  int downTimer = downSequence[currDown];

  if (downTimer != -1 && downTimer >= millis())
  {
    if (downState)
    {
      ledMatrix.drawPixel(2, 1, ledMatrix.Color(0, 0, 0));
    }
    else
    {
      ledMatrix.drawPixel(2, 1 ledMatrix.Color(128, 0, 0));
    }
    downState = -downState;
    currUp++;
  }
  else if (downTimer == -1)
  {
    // TODO: Check if redrawing every frame is cringe
    ledMatrix.drawPixel(2, 1, ledMatrix.Color(128, 0, 0));
  }

  // Up Button
  // Up LED is at (3, 1) 
  int upTimer = upSequence[currUp];

  if (upTimer != -1 && upTimer >= millis())
  {
    if (upState)
    {
      ledMatrix.drawPixel(3, 1, ledMatrix.Color(0, 0, 0));
    }
    else
    {
      ledMatrix.drawPixel(3, 1, ledMatrix.Color(128, 0, 0));
    }
    upState = -upState;
    currUp++;
  }
  else if (upTimer == -1)
  {
    // TODO: Check if redrawing every frame is cringe
    ledMatrix.drawPixel(3, 1, ledMatrix.Color(128, 0, 0));
  }

  // A Button
  // A-LED is at (4, 1) 
  int ATimer = ASequence[currA];

  if (ATimer != -1 && ATimer >= millis())
  {
    if (AState)
    {
      ledMatrix.drawPixel(4, 1, ledMatrix.Color(0, 0, 0));
    }
    else
    {
      ledMatrix.drawPixel(4, 1, ledMatrix.Color(128, 0, 0));
    }
    AState = -AState;
    currA++;
  }
  else if (ATimer == -1)
  {
    // TODO: Check if redrawing every frame is cringe
    ledMatrix.drawPixel(4, 1, ledMatrix.Color(128, 0, 0));
  }

  // B Button
  //B-LED is at (5, 1) 
  int BTimer = BSequence[currB];

  if (BTimer != -1 && BTimer >= millis())
  {
    if (BState)
    {
      ledMatrix.drawPixel(5, 1, ledMatrix.Color(0, 0, 0));
    }
    else
    {
      ledMatrix.drawPixel(5, 1, ledMatrix.Color(128, 0, 0));
    }
    BState = -BState;
    currB++;
  }
  else if (BTimer == -1)
  {
    // TODO: Check if redrawing every frame is cringe
    ledMatrix.drawPixel(5, 1, ledMatrix.Color(128, 0, 0));
  }

  // C Button
  // C-LED is at (6, 1) 
  int CTimer = CSequence[currC];

  if (CTimer != -1 && CTimer >= millis())
  {
    if (CState)
    {
      ledMatrix.drawPixel(6, 1, ledMatrix.Color(0, 0, 0));
    }
    else
    {
      ledMatrix.drawPixel(6, 1, ledMatrix.Color(128, 0, 0));
    }
    CState = -CState;
    currC++;
  }
  else if (CTimer == -1)
  {
    // TODO: Check if redrawing every frame is cringe
    ledMatrix.drawPixel(6, 1, ledMatrix.Color(128, 0, 0));
  }
}
