//citim un triplet de forma pin,animatie,frecventa
//incepem cu fade-ul pe led-ul 8
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   for(int i=8;i<=13;i++)
   {
     pinMode(i,OUTPUT);
   }



}
char s[1000];
char animation[100]=;
char numberAsChar[10]=;
char c;
int idx=0;
int pin;
int frequency=0;




void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()>0)
  {
    c=Serial.read();
    s[idx++]=c;

  }
  
   if(idx>0 && c=='\n')
   {
      parseCommand(s,pin,animation,frequency);
      animation(pin,animation,frequency);
       
   }

  

}

int conversion(char numberAsChar[10])
{
  int result = 0;
  int i = 0;
  while (numberAsChar[i] != '\0')
  {
    result = result * 10 + (numberAsChar[i] - '0');
    i++;
  }
  return result;
}

void parseCommand(char s[1000], int &pin, char animation[100], int &frequency)
{  
  int length = strlen(s);
  char substr[100];
  int j = 0;
  int k = 0; 
  int i = 0;
  
  for(i = 0; i < length; i++)
  {
     if(s[i] == ',')
     {
        k++;
        substr[j] = '\0';
        
        if(k == 1)
        {
           pin = conversion(substr);
        }
        else{
           strcpy(animation, substr);     
        }
        j = 0;
     }
     else{
         substr[j] = s[i];
         j++;
     }
  }
  
  substr[j] = '\0';
  frequency = conversion(substr);
}

void animation(int pin, char animation[100], int frequency)
{
  if (pin < 8 || pin > 13) return;
  int idx = pin - 8;
  
  static unsigned long lastMillis[6] = {0, 0, 0, 0, 0, 0};
  static unsigned long lastMicros[6] = {0, 0, 0, 0, 0, 0};
  static int brightness[6] = {0, 0, 0, 0, 0, 0};
  static bool state[6] = {false, false, false, false, false, false};

  if (strcmp(animation, "on") == 0) {
    digitalWrite(pin, HIGH);
    brightness[idx] = 255;
  }
  else if (strcmp(animation, "off") == 0) {
    digitalWrite(pin, LOW);
    brightness[idx] = 0;
  }
  else if (strcmp(animation, "blink") == 0) {
    if (millis() - lastMillis[idx] >= (unsigned long)frequency) {
      lastMillis[idx] = millis();
      state[idx] = !state[idx];
      if (state[idx]) {
        digitalWrite(pin, HIGH);
      } else {
        digitalWrite(pin, LOW);
      }
    }
  }
  else if (strcmp(animation, "fadein") == 0 || strcmp(animation, "fadeout") == 0) {
    if (millis() - lastMillis[idx] >= (unsigned long)frequency) {
      lastMillis[idx] = millis();
      if (strcmp(animation, "fadein") == 0) {
        if (brightness[idx] < 255) brightness[idx]++;
      } else {
        if (brightness[idx] > 0) brightness[idx]--;
      }
    }
    
    unsigned long currentMicros = micros();
    unsigned long diff = currentMicros - lastMicros[idx];
    
    if (diff >= 2550) {
      lastMicros[idx] = currentMicros;
      diff = 0;
    }
    
    if (brightness[idx] == 0) {
      digitalWrite(pin, LOW);
    }
    else if (brightness[idx] == 255) {
      digitalWrite(pin, HIGH);
    }
    else {
      if (diff < (unsigned long)(brightness[idx] * 10)) {
        digitalWrite(pin, HIGH);
      } else {
        digitalWrite(pin, LOW);
      }
    }
  }
}
