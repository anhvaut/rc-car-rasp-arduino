#include <Servo.h>
#include <Wire.h> 

// Nho bo 2 chan 0 va 1 (chan bluetooth) ra roi dich, chu khong bi loi

//L298 dong co
#define ENA 6  //enable A on pin 6 (needs to be a pwm pin)
#define ENB 3  //enable B on pin 3 (needs to be a pwm pin)
#define IN3 5  //IN1 on pin 5 conrtols one side of bridge A
#define IN4 4  //IN2 on pin 4 controls other side of A
#define IN1 7  //IN3 on pin 7 conrtols one side of bridge B
#define IN2 8  //IN4 on pin 8 controls other side of B

Servo robotHeadServo;  // create servo object to control a servo
const int headServoPin = 9;     // chân trig của HC-SR05

const int trig = 12;     // chân trig của HC-SR05
const int echo = 13;     // chân echo của HC-SR05

String voice;
char dataSerial;
int speedOfCar=200,xung1=0;


void setup()
{
    
    initalizeMotorControl();
    initalizeBluetooth();

    //robotHeadServo.attach(headServoPin);
    Serial.begin(9600);     // giao tiếp Serial với baudrate 9600
}
 
void loop()
{

    carControlledBySerial();
   
}

void carControlledBySerial()
{
  
   //Check data read from Serial is available (it could be bluetooth)
   voice ="";

   
  if(Serial.available())
  {
     
     dataSerial = Serial.read(); //Conduct a serial read
   
   
      switch (dataSerial) 
      {
    
        // Read value from Bluetooth and setup speed
        case '0': speedOfCar=0;    break;
        case '1': speedOfCar=20;   break;
        case '3': speedOfCar=60;   break;
        case '4': speedOfCar=80;   break;
        case '5': speedOfCar=100;  break;
        case '6': speedOfCar=120;  break;
        case '7': speedOfCar=140;  break;
        case '8': speedOfCar=160;  break;
        case '9': speedOfCar=180;  break;
        case 'q': speedOfCar=200;  break;
        case 'F': moveForward(); break; 
        case 'B': moveBackward(); break; 
        case 'L': turnRight(); break;
        case 'R': turnLeft(); break;
        case 'G': moveForwardLeft(); break;
        case 'I': moveForwardRight(); break;
        case 'J': moveBackwardLeft(); break;
        case 'H': moveBackwardRight(); break;
        case 'S': carStop(); break;
      }    

//      Serial.println(dataSerial);


   }

  
}


/**
 * 
 * HS 05, giao tiep bluetooth
 */

 void initalizeBluetooth()
 {
   //set pin for HC-SR05
    pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu
 }
 

/**
 * Dieu khien mach dong co L298
 * 
 */

void initalizeMotorControl()
{
    //set all of the outputs for the motor control
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}
void moveForward()
{
  digitalWrite(IN1, HIGH);  
  digitalWrite(IN2, LOW);   
      
  digitalWrite(IN4, LOW);  
  digitalWrite(IN3, HIGH);  

  analogWrite(ENB, speedOfCar);  
  analogWrite(ENA, speedOfCar);  
  
  Serial.println("**** Di Thang");
  
}

void moveBackward()
{
     digitalWrite(IN1, LOW);  
     digitalWrite(IN2, HIGH);   
      
     digitalWrite(IN4, HIGH); 
     digitalWrite(IN3, LOW);   

     analogWrite(ENB, speedOfCar);  
     analogWrite(ENA, speedOfCar); 

     Serial.println("**** Di lui");
}

void turnRight()
{
     digitalWrite(IN1, HIGH);  
     digitalWrite(IN2, LOW);   
      
     digitalWrite(IN4, HIGH);  
     digitalWrite(IN3, LOW); 

     analogWrite(ENB, speedOfCar);  
     analogWrite(ENA, speedOfCar);   

     Serial.println("**** Queo phai");
}

void turnLeft()
{
     digitalWrite(IN1, LOW);  
     digitalWrite(IN2, HIGH);   
      
     digitalWrite(IN4, LOW);  
     digitalWrite(IN3, HIGH); 

     analogWrite(ENB, speedOfCar);  
     analogWrite(ENA, speedOfCar);   

     Serial.println("**** Queo trai");
}

void moveForwardLeft()
{
     digitalWrite(IN1, HIGH);  
     digitalWrite(IN2, LOW);   
      
     digitalWrite(IN4, LOW);  
     digitalWrite(IN3, HIGH);   

     analogWrite(ENB, speedOfCar/3*2);  
     analogWrite(ENA, speedOfCar);  
     

     Serial.println("**** Thang Trai");
}

void moveForwardRight()
{
     digitalWrite(IN1, HIGH);  
     digitalWrite(IN2, LOW);   
      
     digitalWrite(IN4, LOW);  
     digitalWrite(IN3, HIGH);   

     analogWrite(ENB, speedOfCar);  
     analogWrite(ENA, speedOfCar/3*2);  
    

     Serial.println("**** Thang Phai");
}

void moveBackwardRight()
{
     digitalWrite(IN1, LOW);  
     digitalWrite(IN2, HIGH);   
      
     digitalWrite(IN4, HIGH);  
     digitalWrite(IN3, LOW);   

     analogWrite(ENB, speedOfCar/3*2);  
     analogWrite(ENA, speedOfCar);  
  

     Serial.println("**** Lui phai");
}

void moveBackwardLeft()
{
     digitalWrite(IN1, LOW);  
     digitalWrite(IN2, HIGH);   
      
     digitalWrite(IN4, HIGH);  
     digitalWrite(IN3, LOW);   

     analogWrite(ENB, speedOfCar);  
     analogWrite(ENA, speedOfCar/3*2);  

     Serial.println("**** Lui trai");
}

void carStop()
{
     digitalWrite(IN1, LOW);  
     digitalWrite(IN2, LOW);   
      
     digitalWrite(IN4, LOW);  
     digitalWrite(IN3, LOW);   

     analogWrite(ENB, 0);  
     analogWrite(ENA, 0); 

     Serial.println("**** Dung");
}

/*************************************/




 
