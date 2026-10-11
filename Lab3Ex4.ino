/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Fade/
*/

int led = 3;         // the PWM pin the LED is attached to
int brightness = 0;  // how bright the LED is
int fadeAmount = 5;  // how many points to fade the LED by
int interval=100;
long prevTime=0;

char s[1000];
char c;
int idx=0;
int number=0;
int cif=0;

// the setup routine runs once when you press reset:
void setup() {

  Serial.begin(9600);
  // declare pin 3 to be an output:
  pinMode(led, OUTPUT);
}


// the loop routine runs over and over again forever:
void loop() {

   unsigned long curentTime=millis();

  // set the brightness of pin 9:
  analogWrite(led, brightness);
  
  while(Serial.available()>0)
  {
    c=Serial.read();
    s[idx++]=c;
  }

  if(idx>0 && c=='\n')
  {
    s[idx]=0;
    
    for(int i=0; i<idx; i++)
    {
      if(s[i] != '\n' && s[i] != '\r')
      {
        cif=s[i]-'0';
        number=number*10+cif;
      }
    }
    
    interval = 1000/ number;
    idx=0;
  }

  number=0;

  if(curentTime-prevTime>interval)
  {
    // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
     prevTime=curentTime;
  }
  
}