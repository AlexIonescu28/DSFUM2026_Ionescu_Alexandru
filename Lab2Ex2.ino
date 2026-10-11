void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  //Nu am reusit sa termin la laborator asa ca am continuat acasa cu 4 led-uri
}
int interval=1000;
long prevTime=0;
int i=0;
void loop() {
  // put your main code here, to run repeatedly:
  
  unsigned long currentTime = millis();
  displayNumber(i);
  if(currentTime-prevTime>1000)
  {
    i++;
    prevTime=currentTime;
  }

  if(i>=16)
  {
    i=0;
  }
     
   
  
}

void displayNumber(int number)
{
  int copyNumber=number;
  for (int p = 10; p <= 13; p++) {
    digitalWrite(p, LOW);
  }
  
  int i=0;
  while(copyNumber!=0)
  {
    if(copyNumber%2==1)
    {
      digitalWrite(13-i,HIGH);
    }
    else{
      digitalWrite(13-i,LOW);
    }

    i++;
    copyNumber=copyNumber/2;
  }

}
