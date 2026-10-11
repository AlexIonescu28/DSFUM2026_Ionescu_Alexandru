void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  //Nu am reusit sa termin la laborator asa ca am continuat acasa cu 4 led-uri
}
char s[1000];
char c;
int idx=0;
int number=0;
int cif=0;
void loop() {
  // put your main code here, to run repeatedly:
   

  while(Serial.available()>0)
  {
    c=Serial.read();
    s[idx++]=c;
  }

  if(idx>0 && c=='\n')
  {
    s[idx]=0;
    Serial.print("Am primit:");
    
    cif=s[0]-'0';
    number=number*10+cif;

    if(strlen(s)>2)
    {
      cif=s[1]-'0';
      number=number*10+cif;
    }
    
    Serial.println(number);
    displayNumber(number);
    idx=0;
  }

   number=0;
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
