#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

#define INA 5
#define INB 6 
#define INC 12 
#define IND 13
#define EN1 8
#define EN2 9
#define frontLight 7
#define backLight 4

char command= 'S';
char prevCommand= 'A';
int velocity=0;
unsigned long timer0=2000;
unsigned long timer1=0;

void setup() 
{ 
  pinMode(INA, OUTPUT ); 
  pinMode(INB, OUTPUT ); 
  pinMode(INC, OUTPUT ); 
  pinMode(IND, OUTPUT ); 
  pinMode(EN1, OUTPUT); 
  pinMode(EN2, OUTPUT);
  pinMode(frontLight,OUTPUT);
  pinMode(backLight,OUTPUT);
  mySerial.begin(9600);
  Serial.begin(9600);
}

void aFor() ///Motor A forward direction 
{ 
  digitalWrite(INA,LOW); 
  digitalWrite(INB,HIGH); 
}

void aBac() ///Motor A backward direction 
{ 
  digitalWrite(INA,HIGH); 
  digitalWrite(INB,LOW); 
}
void bFor() ///Motor B forward direction 
{ 
  digitalWrite(INC,LOW); 
  digitalWrite(IND,HIGH); 
}
void bBac() ///Motor B backward direction 
{ 
  digitalWrite(INC,HIGH); 
  digitalWrite(IND,LOW); 
}
void aStop() 
{ 
  digitalWrite(INA,LOW); 
  digitalWrite(INB,LOW); 
} 
void bStop() 
{ 
  digitalWrite(INC,LOW); 
  digitalWrite(IND,LOW); 
}

void carVelocity(int speedA,int speedB){
  analogWrite(EN1,speedA);
  analogWrite(EN2,speedB);
}

void loop() 
{ 
  aFor();
  bFor();
  carVelocity(130,255);
}
