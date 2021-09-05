#include <LiquidCrystal.h>
#include <Wire.h>
#include <TEA5767N.h>

LiquidCrystal lcd(10, 9, 5, 4, 3, 2);
TEA5767N radio = TEA5767N();
double frequency = 94.30;
int sup = A2;
int sdown = 13;
int bup = 7;
int bdown = 6;
int mute = 8;
boolean flagMute = false;
int a = 0;
int supVal;
int bupVal;
int muteVal;
int sdownVal;
int bdownVal;
int sig;

void setup()
{ 
  pinMode(sup, INPUT);
  pinMode(sdown, INPUT);
  pinMode(mute, INPUT);
  Wire.begin();

  lcd.begin(16, 2);
  lcd.print("POWER ON");
  delay(2500);
  radio.selectFrequency(frequency); // pick your own frequency
  freqPrint();
  Serial.print("Signal level: ");
  Serial.println(radio.getSignalLevel());
  button();
  //Serial.println(frequency);  
}
void button()
{
  while (0 < 1)
  {
    sig = radio.getSignalLevel();
    supVal = digitalRead(sup);
    muteVal = digitalRead(mute);
    sdownVal = digitalRead(sdown);
    bupVal = digitalRead(bup);
    bdownVal = digitalRead(bdown);
    if(supVal == LOW)
    {
      frequency = frequency + 0.1;
      delay(1000);
      if(frequency >= 108.00)
        frequency = 87.50;
      freqPrint();
      radio.selectFrequency(frequency);
    }
    if(bupVal == LOW)
    {
      frequency = frequency + 1;
      if(frequency >= 108.00)
        frequency = 87.50;
      freqPrint();
      delay(100);
      radio.selectFrequency(frequency);
    }
    if(sdownVal == LOW)
    {
      frequency = frequency - 0.1;
      if(frequency < 87.50)
        frequency = 108.00;
      freqPrint();
      delay(100);
      radio.selectFrequency(frequency);
    }
    if(bdownVal == LOW)
    {
      frequency = frequency - 1;
      if(frequency <= 87.50)
        frequency = 108.00;
      freqPrint();
      delay(100);
      radio.selectFrequency(frequency);
    }
    if(muteVal == LOW)
    {
      if(flagMute == false)
      {
        radio.mute();
        flagMute = true;
        lcd.setCursor(0,0);
        lcd.print("MUTED         ");
      }
      else if(flagMute == true)
      {
        radio.turnTheSoundBackOn();
        flagMute = false;
        freqPrint();
      }
      else 
        continue;
    }
    if((radio.getSignalLevel() != sig)) //&& ((upVal == HIGH) || (downVal == HIGH)))
      {
        delay(1000);
        lcd.setCursor(0, 1);
        lcd.print("Sig Strength: ");  
        lcd.setCursor(14, 1);
        lcd.print("   "); 
        lcd.setCursor(14, 1); 
        sig = radio.getSignalLevel();
        lcd.print(sig);
      }
  }
}

void loop() {}

void freqPrint()
{
  lcd.setCursor(0, 0);
  lcd.print("Freq: ");
  lcd.setCursor(6, 0);
  lcd.print(frequency);
  if(frequency <= 99.99)
  {
    lcd.setCursor(11, 0);
    lcd.print(" ");
  }
}
