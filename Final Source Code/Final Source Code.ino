#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

#define INA 5
#define INB 6 
#define INC 12 
#define IND 13
#define EN1 8
#define EN2 9
#define frontLight1 2
#define frontLight2 3
#define backLight 4
#define horn 7

char command= 'S';
char prevCommand= 'A';
int velocity=130;
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
  pinMode(frontLight1,OUTPUT);
  pinMode(frontLight2,OUTPUT);
  pinMode(backLight,OUTPUT);
  pinMode(horn,OUTPUT);
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

void carVelocity(int speedA=130,int speedB=130){
  analogWrite(EN1,speedA);
  analogWrite(EN2,speedB);
}

void loop() 
{ 

  if (mySerial.available()>0){
    timer1=millis();
    prevCommand=command;
    command=mySerial.read();
//Serial.println(command);
    if(command!=prevCommand){
      switch(command){
        case 'F':
          digitalWrite(backLight,LOW);
          aFor();
          bFor();
          break;
          
        case 'B':
          aBac();
          bBac();
          digitalWrite(backLight,HIGH);
          break;

        case 'L':
          digitalWrite(backLight,LOW);
          aBac();
          bFor();
          break;

        case 'R':
          digitalWrite(backLight,LOW);
          aFor();
          bBac();
          break;

        case 'S':
          aStop();
          bStop();
          break;

        case 'I':     //FR
          digitalWrite(backLight,LOW);
          aFor();
          bStop();
          break;

        case 'J':     //BR
          digitalWrite(backLight,HIGH);
          aBac();
          bStop();
          break;

        case 'G':     //FL
          digitalWrite(backLight,LOW);
          aStop();
          bFor();
          break;

        case 'H':     //BL
          digitalWrite(backLight,HIGH);
          aStop();
          bBac();
          break;

        case 'W':     //FrontLight ON
           digitalWrite(frontLight1,HIGH);
           digitalWrite(frontLight2,HIGH);
           break;

        case 'w':     //FrontLight OFF
          digitalWrite(frontLight1,LOW);
          digitalWrite(frontLight2,LOW);
          break;

        case 'U':     //BackLight ON
          digitalWrite(backLight,HIGH);
          break;

        case 'u':     //BackLight OFF
          digitalWrite(backLight,LOW);
          break;

        case 'V':
          digitalWrite(horn,HIGH);
          break;

        case 'v':
          digitalWrite(horn,LOW);
          break;

        case 'X':
          digitalWrite(frontLight1,HIGH);
          digitalWrite(frontLight2,HIGH);
          digitalWrite(backLight,HIGH);
          digitalWrite(horn,HIGH);
          break;

        case 'x':
          digitalWrite(frontLight1,LOW);
          digitalWrite(frontLight2,LOW);
          digitalWrite(backLight,LOW);
          digitalWrite(horn,LOW);
          break;
                    
        case 'D':     //Everything OFF
          aStop();
          bStop();
          digitalWrite(frontLight1,LOW);
          digitalWrite(frontLight2,LOW);
          digitalWrite(backLight,LOW);
          digitalWrite(horn,LOW);
          break;

        default:
          if(command=='q'){
            velocity=255;
            carVelocity(velocity-60,velocity);
          }
          else {
            if((command >=48)&&(command <53)){
              velocity=130;
              carVelocity(velocity,velocity+50);
            }
            
            else if((command >=53) && (command <=57)){
              velocity=(command-48)*25;
              carVelocity(velocity-25,velocity+30);
            }
          }
      }
    }
  }

   else{
    timer0=millis();
    if((timer0-timer1)>500){
      aStop();
      bStop();
      digitalWrite(frontLight1,LOW);
      digitalWrite(frontLight2,LOW);
      digitalWrite(backLight,LOW);
      digitalWrite(horn,LOW);
    }
   }
}
