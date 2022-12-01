//**********************
//Выполнил ученимк 6В класса
//Тихоступ Роман

//Машина с ультразвуковым датчиком HC-SR04
//Происходит опрос датчика и если дистанция меньше minDist или равно 0, (0 из за оссобеностей библиотеки NewPing
//если расстояние с датчика больше максимального, почему-то выдается расстояние 0 см) то машина останавливается, 
//разворачивается налево и продолжает движение с опросом датчика.
//**********************

#include <NewPing.h>

//Пины к моему драйверу двигателей
#define Rf 11
#define Rb 13
#define Lf 5
#define Lb 6

//Пины к HC-SR04
#define trig 2
#define echo 3

//Минимальная дистанция для датчика
#define minDist 15

byte speed = 110;
int dist = 0;

NewPing sonar(trig, echo, 250);

void setup() {
  pinMode(Rf, OUTPUT);
  pinMode(Rb, OUTPUT);
  pinMode(Lf, OUTPUT);
  pinMode(Lb, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("Start");
}
//by Dirk Sarodnik
void loop() {
  CalcDist();
  if(dist <= minDist && dist != 0){
    Serial.println(dist);
    Serial.println("Left");
    Serial.println();
    
    stop();
    delay(300);
    
    backward();
    delay(700);
    
    left();
    delay(350);
    
    stop();
    
  } else {
    Serial.println(dist);
    Serial.println("Forward");
    Serial.println();
    forward();
  }
}

void stop(){
  analogWrite(Rf, 0);
  analogWrite(Rb, 0);
  analogWrite(Lf, 0);
  analogWrite(Lb, 0);
}

void backward(){
  analogWrite(Rf, 0);
  analogWrite(Rb, speed);
  analogWrite(Lf, 0);
  analogWrite(Lb, speed);
}

void forward(){
  analogWrite(Rf, speed);
  analogWrite(Rb, 0);
  analogWrite(Lf, speed);
  analogWrite(Lb, 0);
}

void left(){
  analogWrite(Rf, speed);
  analogWrite(Rb, 0);
  analogWrite(Lf, 0);
  analogWrite(Lb, speed);
}


void CalcDist(){
  dist = sonar.ping_cm();
}
