#define humanHotSensor 4//定义人体传感器接D4
#define LED 6//led灯接D6
#define buzzer 2//蜂鸣器接D2
#include <U8glib.h>//关于oled屏幕引用函数的声明
int sb=0;                 //定义一个整形常量sb（名字不重要啦）
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);      //说明oled型号
#define ziti1 u8g.setFont(u8g_font_7x13)    //给这个字体取个新的名字

   
void setup() //初始化
{
  digitalWrite(LED,LOW);//让led灯不亮
  Serial.begin(9600);//设置波特率9600
  pinMode(humanHotSensor, INPUT);
  pinMode(LED,OUTPUT);
  pinMode(buzzer,OUTPUT);                      //定义人体红外，led和蜂鸣器三个口是输入还是输出
}

void loop(){
  sb=digitalRead(humanHotSensor);
  Serial.println(sb);                //在串口监视器里面打出人体红外感应到的值
  if (sb==1)           
  {
  digitalWrite(LED,HIGH);              //如果值为1（就是有人）那么输出高电压，led灯亮
  
  u8g.firstPage();           //在oled屏幕里面显示“Please get away！”并让蜂鸣器报警（设置了放空报警的频率，但是感觉不怎么像）
      do {
          ziti1;
          u8g.setPrintPos(10, 40);
          u8g.print("Please get away!");
          tone(buzzer, 500, 10);
         }while( u8g.nextPage() );
  
   }
  else                      //如果没人，led不亮，蜂鸣器也不响，屏幕不显示（其实显示了空格啦）
  {
    digitalWrite(LED,LOW);
    u8g.firstPage();
      do {
          ziti1;
          u8g.drawStr(10,10,"");       //这里用的在oled屏幕上显示的函数和上面的不一样，我只是想试试不同的函数而已

          }while( u8g.nextPage() );
  
  }

}



