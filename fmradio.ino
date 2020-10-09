// TEA5767 Example
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <Wire.h>
#include <TEA5767N.h>

Adafruit_7segment matrix = Adafruit_7segment();
TEA5767N radio = TEA5767N();
double frequency = 104.00;
int up = 7;
int down = 6;
int mute = 8;
boolean flagMute = false;
int a = 0;

void setup()
{ 
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(mute, INPUT);
  Wire.begin();
  Serial.begin(9600);
  radio.selectFrequency(frequency); // pick your own frequency
  //matrixSetup();
  //freqPrint(frequency);
  Serial.println(frequency);  
}

void loop()
{
  int upVal = digitalRead(up);
  int muteVal = digitalRead(mute);
  int downVal = digitalRead(down);
  //if(muteVal == LOW)
    //Serial.println("mute pressed");
  if(upVal == LOW)
    {
      frequency = frequency + 0.1;
      if(frequency > 108.00)
      {  
        frequency = 87.50;
      }
      //freqPrint(frequency);
      Serial.println(frequency);
    }
    if(downVal == LOW)
    {
      frequency = frequency - 0.1;
      if(frequency < 87.50)
      {
        frequency = 108.00;
      }
      //freqPrint(frequency);
      Serial.println(frequency);
      delay(1000);
    }
    else
      radio.selectFrequency(frequency);
/** Mute button not installed
    if(muteVal == LOW)
    {
      Serial.print(flagMute);
      if(flagMute == true)
      {
        radio.turnTheSoundBackOn();
        flagMute = false;
        //matrix.print(freq);
      }
      else
      {
        radio.mute();
        flagMute = true;
        //matrix.print("MUTE");
      }
      //matrix.writeDisplay();
    }
    **/
}


/**
 * Last digit, writeDigitNum(location, number)
 * Second last, writeDigitNum(location, number, true)
 * Third last, writeDigitNum(location, number)
 * Fourth, writeDigitNum(location, number)
 */
void freqPrint(double inFreq)
{
   inFreq = inFreq * 10;
   a = (int)inFreq;
   matrix.writeDigitNum(4, a%10, false); 
   a = a/10;
   matrix.writeDigitNum(3, a%10, true);
   a = a/10;
   matrix.writeDigitNum(1, a%10, false);
   a = a/10;
   if(a == 0)
    matrix.writeDisplay();
   else
   {
    matrix.writeDigitNum(0, a%10, false);
    a = a/10;
    matrix.writeDisplay();
   }
}

void matrixSetup()
{
  matrix.begin(0x70);
  matrix.setBrightness(1);
  matrix.writeDisplay();
}
