void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

char s[1000];
char c;
int idx=0;
long previousMillis = 0;
int ledState = LOW; 
long interval = 1000;
bool blink=false;
void loop() {

  unsigned long currentMillis = millis();
  
  if(blink==true)
  {
    if(currentMillis - previousMillis > interval) {

           previousMillis = currentMillis; 
           if (ledState == LOW)
              ledState = HIGH;
           else
               ledState = LOW;

          digitalWrite(LED_BUILTIN, ledState);
      }
  }

  while(Serial.available()>0)
  {
    c=Serial.read();
    s[idx++]=c;
  }

  if(idx>0 && c=='\n')
  {
    s[idx]=0;
    Serial.print("Am primit:");
    Serial.println(s);
    if(s[0]=='1')
    {
      Serial.println("Pornit");
      digitalWrite(LED_BUILTIN, HIGH); 
      blink=false;
    }

     if(s[0]=='2')
    {
      Serial.println("Oprit");
      digitalWrite(LED_BUILTIN, LOW); 
      blink=false;
    }

     if(s[0]=='3')
    {
      Serial.println("Blink");
      blink=true;
    }

    idx=0;
  }

}