void setup ()
{
  pinMode(4,OUTPUT); // pinul pentru latch (blocare)
  pinMode(7,OUTPUT); // pin pentru sincronizarea ceasului
  pinMode(8,OUTPUT); // pin pentru transmiterea datelor
}

byte ZERO = 0b11111111;
byte ONE = 0b11110011;
byte TWO = 0b00100101;
byte THREE = 0b01100001;
byte FOUR = 0b11010001;
byte FIVE = 0b01001001;
byte SIX = 0b00001001;
byte SEVEN = 0b11100011;
byte EIGHT = 0b00000001;
byte NINE = 0b01000001;

byte Numbers[]={0b11111111,0b11110011, 0b00100101,0b01100001, 0b11010001,0b01001001,0b00001001,0b11100011,0b00000001,0b01000001};

void loop()
{

   for(int i=0;i<10;i++)
   {
       afiseazaValoare(Numbers[i], 0b10000000); 
       delay(1000);
   }

 
}
 
void afiseazaValoare(byte valoare, byte segment)
{
  digitalWrite(4,LOW);
  shiftOut(8, 7, LSBFIRST, valoare);
  shiftOut(8, 7, LSBFIRST, segment);
  digitalWrite(4,HIGH);
}