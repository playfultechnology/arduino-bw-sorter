/**
 *
 * See https://www.makerbuying.com/docs/snar39
 */


#include <Servo.h>

#define White false    //白色
#define Black true     //黑色

#define Back      58      //归位
#define Transfer  0   //送出
//#define Back      40      //归位
//#define Transfer  0     //送出

//#define Black_Deg   45   //白色盘位置
//#define Middle_Deg  90  //中间位置
//#define White_Deg   143 //黑色盘位置
#define Black_Deg   60   //白色盘位置
#define Middle_Deg  95  //中间位置
#define White_Deg   125//黑色盘位置

Servo Colour,Arm;     //Colour是颜色分拣舵，Arm为传送舵
bool OFF_ON_flag=false;

int i;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);  //LED灯
  pinMode(A0, INPUT);    //颜色输入口
   pinMode(2, INPUT);    //启停按键输入口
  Arm.attach(11);       //初始化舵机
  Colour.attach(12);    //初始化舵机
  
  digitalWrite(13, LOW);
  
  Serial.begin(9600); 
  Serial.println("Robot ready..."); 

  Arm.write(Back);
  Colour.write(Middle_Deg);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(2)==true)
  {
    delay(5);
    if(digitalRead(2)==true)
    {
         OFF_ON_flag= !OFF_ON_flag;
         while(digitalRead(2)==true);
     }
     
  }
  if( OFF_ON_flag==true)
  {
    Trans();
    
    digitalWrite(13,HIGH);
    
    if(digitalRead(A0) == Black)
    {
      for(i=Middle_Deg;i>Black_Deg;i--)
      {
        Colour.write(i);
        delay(3);
      }
      Serial.println("This is Black...");
      delay(50);
    }
    else 
    {
      for(i=Middle_Deg;i<White_Deg;i++)
      {
        Colour.write(i);
        delay(3);
      }
    }      
    Serial.println("This is White...");
    delay(50);
    digitalWrite(13,LOW);
    Serial.println("----------------------");
  }else
  {
      Arm.write(Back);
      Colour.write(Middle_Deg);
    }
}

void Trans()
{
  Colour.write(Middle_Deg);
  delay(50);
  Arm.write(Back);
  delay(50);
  //Arm.write(Transfer);
  for(i=Back;i>Transfer;i--)
  {
    
    Arm.write(i);
    delay(3);
  }
  //delay(1000);
  for(i=Transfer;i<Back;i++)
  {
    Arm.write(i);
    delay(3);
  }
  //Arm.write(Back);
  Serial.println("Transfer OK..."); 
}
