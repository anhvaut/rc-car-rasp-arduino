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
    //mode = 0;
     
    //carControlledByVoice();
    carControlledBySerial();
    
    //avoidObject();
    //computeObjectDistanceInCentimet (180);

    //  For testing   
    //  digitalWrite(IN1, HIGH);  
    //  digitalWrite(IN2, LOW);   
    //      
    //  digitalWrite(IN4, LOW);  
    //  digitalWrite(IN3, HIGH); 
   
}

void carControlledBySerial()
{
  
   //Check data read from Serial is available (it could be bluetooth)
   voice ="";

   
  if(Serial.available())
  {
     
     dataSerial = Serial.read(); //Conduct a serial read
  }
   
   
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

  
}

void carControlledByVoice()
{

   voice ="";

   
   while(Serial.available())
   {
     //Serial.println("state");
     delay(10); //Delay added to make thing stable
     char c = Serial.read(); //Conduct a serial read
     if (c == '#') {break;} //Exit the loop when the # is detected after the word
     voice += c; //Shorthand for voice = voice + c

     //Serial.println("voice:" + voice);
     Serial.println("c:" + dataSerial);
   }
   //Serial.flush();
   
    if (voice.length() > 0) {
    Serial.println("Finish:" + voice);
    
    if(voice.indexOf("*đi thẳng") != -1 || 
       voice.indexOf("*đi tới") != -1 ||
       voice.indexOf("*thẳng") != -1 ||
       voice.indexOf("*tới") != -1 ||
       voice.indexOf("*forward") != -1 ||
       voice.indexOf("*10") != -1)
       {
          moveForward();
          delay(1000);
          carStop();
       }
    else if(voice.indexOf("*đi lui")!=-1 || 
       voice.indexOf("*lui") !=-1 ||
       voice.indexOf("*backward") != -1 ||
       voice.indexOf("*back") != -1 ||
       voice.indexOf("*11") != -1)
       {
          moveBackward();
          delay(1000);
          carStop();
          
       }
    else if(voice.indexOf("*quẹo trái") != -1 || 
       voice.indexOf("*turn left") != -1 ||
       voice.indexOf("*left") != -1 || 
       voice.indexOf("*13") != -1)
       {
          turnLeft();
          delay(1000);
          carStop();
       }
    else if(voice.indexOf("*quẹo phải") != -1 || 
       voice.indexOf("*turn right") != -1 ||
       voice.indexOf("*right") !=-1 || 
       voice.indexOf("*14") !=-1)
       {
          turnLeft();
          delay(1000);
          carStop();
       }
    else if(voice.indexOf("*dừng lại") != -1 || 
       voice.indexOf("*stop") != -1 ||
       voice.indexOf("*dừng") != -1 ||
       voice.indexOf("*15") != -1 ) 
       {
          carStop();
          delay(1000);
          carStop();
       }

    voice ="";
  }
  
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

  Serial.println("**** Di Thang");

   analogWrite(ENB, speedOfCar);  
   analogWrite(ENA, speedOfCar);  
}

void moveBackward()
{
     digitalWrite(IN1, LOW);  
     digitalWrite(IN2, HIGH);   
      
     digitalWrite(IN4, HIGH); 
     digitalWrite(IN3, LOW);   

     Serial.println("**** Di lui");

     analogWrite(ENB, speedOfCar);  
     analogWrite(ENA, speedOfCar);  
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
  * 
  * 
  */
int objectDistance_cm (byte angle)
{
    robotHeadServo.write(angle);
    delay(500);
    unsigned long duration; // biến đo thời gian
    int distance;           // biến lưu khoảng cách
    
    /* Phát xung từ chân trig */
    digitalWrite(trig,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration = pulseIn(echo,HIGH);  
    // Tính khoảng cách đến vật.
    distance = int(duration/2/29.412);
    
    /* In kết quả ra Serial Monitor */
    //Serial.print(distance);
    //Serial.println("cm");
    //delay(200);
  return distance;
}

void avoidObject()
{
  int allow_distance = 50;
  int turn_back_time = 1000;
  moveForward();

  //delay(10);
  int front_distance=objectDistance_cm (90);
  int left_distance;
  int right_distance;
  int max_distance;
  
  if (front_distance > allow_distance)
    {
      moveForward();
      delay(10);
    }
    if (front_distance <= allow_distance)
    {    
      moveBackward();
      delay(300);
      //robotMover(inR1,inR2,inL1,inL2,0);
      left_distance = objectDistance_cm (180); //đo khoảng cách bên trái
      Serial.println("left: ");    
      Serial.println(left_distance);
      //delay (3000);
      right_distance = objectDistance_cm (0); //đo khoảng cách bên phải
      Serial.println("right: ");
      Serial.println(right_distance);
      Serial.println("front: ");
      Serial.println(front_distance);
      //delay (3000);
      max_distance = max(left_distance,right_distance);// so sánh giá trị lớn nhất với khoảng cách bên phải (gán bằng cái lớn nhất)
      if  (max_distance==left_distance)
      {
        turnLeft();
        delay (turn_back_time/2);// Nếu bên trái là khoảng cách lớn nhất thì rẽ trái
      }
      else
      {
        if  (max_distance==right_distance)
        {
          turnRight();
          delay (turn_back_time/2);
        }
      }  
    }
  
}






