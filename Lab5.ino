void setup() {
  Serial.begin(9600);
  pinMode(4,OUTPUT); 
  pinMode(7,OUTPUT); 
  pinMode(8,OUTPUT); 
}

byte Numbers[]={0b00000001,0b11110011, 0b00100101,0b01100001, 0b11010001,0b01001001,0b00001001,0b11100011,0b00000001,0b01000001};
char s[1000];
char c;
int idx=0;
char comand[100];
char hour[100];

void loop() {
  while(Serial.available()>0)
  {
    c=Serial.read();
    s[idx++]=c;
  }

  if(idx>0 && c=='\n')
  {
    s[idx] = '\0';
    parseComand(s, comand, hour);
    idx = 0;
  }

  if (comand[0] != '\0') {
    execute(comand, hour, Numbers);
  }
}

void afiseazaValoare(byte valoare, byte segment)
{
  digitalWrite(4,LOW);
  shiftOut(8, 7, LSBFIRST, valoare);
  shiftOut(8, 7, LSBFIRST, segment);
  digitalWrite(4,HIGH);
}

void parseComand(char s[1000], char comand[100], char hour[100])
{
  comand[0] = '\0';
  hour[0] = '\0';

  if (strncmp(s, "alarm clock", 11) == 0) {
    strcpy(comand, "alarm clock");
    sscanf(s + 11, "%s", hour);
  } 
  else if (strncmp(s, "alarm stopwatch", 15) == 0) {
    strcpy(comand, "alarm stopwatch");
  } 
  else if (strncmp(s, "clock", 5) == 0) {
    strcpy(comand, "clock");
    sscanf(s + 6, "%s", hour);
  } 
  else if (strncmp(s, "stopwatch", 9) == 0) {
    strcpy(comand, "stopwatch");
    sscanf(s + 9, "%s", hour);
  }
}

void execute(char comand[100], char hour[100], byte Numbers[])
{
   if(strcmp(comand,"clock")==0 && strcmp(hour,"12:00")==0)
   {
      afiseazaValoare(Numbers[1], 0b00010000); 
    
      afiseazaValoare(Numbers[2], 0b00100000); 
      
      afiseazaValoare(Numbers[0], 0b01000000); 
      
      afiseazaValoare(Numbers[0], 0b10000000);
   }

   if(strcmp(comand,"clock")==0 && strcmp(hour,"\n")==0)
   {
      

   }
}