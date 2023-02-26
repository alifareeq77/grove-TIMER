#include "TM1637.h"

#define TRG 4
#define ECH 7
#define RED 8
#define GRN 2
#define CLK 12
#define DIO 10
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
bool trg = true; // initiale value for the timer 
TM1637 tm1637(CLK, DIO);
int h1 = 0, h2 = 0, m1 = 0, m2 = 0;
int toogle = 1;

void display_timer(int a, int b, int c, int d, int t) {
  tm1637.display(0, a);
  tm1637.display(1, b);
  tm1637.point(t);
  tm1637.display(2, c);
  tm1637.display(3, d);

}

void run_sensor() {
  // Clears the trigPin condition
  digitalWrite(TRG, LOW);
  delayMicroseconds(2);
  //------------------------------
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(TRG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRG, LOW);
  //-------------------------------
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECH, HIGH);
  //-------------------------------
  // Calculating the distance
  //distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  distance= 190;
  //-------------------------------
  // Displays the distance and the state of timer on the Serial Monitor [for debugging purpos]

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.println(trg);
  //--------------------------------
  if (distance > 10) {
    digitalWrite(RED, HIGH);
    digitalWrite(GRN, trg);

  }
  if (distance < 10) {
    trg = !trg;
    digitalWrite(GRN, trg);
    digitalWrite(RED, LOW);
    delay(2000);
  }
}

void timer_func(int h11, int h22, int m22, int m11, int toogle) {
  // first digit
  if (h2 > 9) {
    h1++;
    h2 = 0;
  }
  //second digit
  if (m2 == 5 && m1 > 9) {
    h2++;
    m2 = 0;
    m1 = 0;
  }
  // third digit
  if (m1 > 9) {
    m2++;
    m1 = 0;
  }
  if (m1 % 2 == 0) {
    toogle = 0;
  } else {
    toogle = 1;
  }
}
void setup() {
  // --- setting up the timer--- 
  tm1637.init();
  tm1637.point(1);
  tm1637.set(2);
  //----------------------------

  //--- setting up sensor---
  pinMode(RED, OUTPUT);
  pinMode(GRN, OUTPUT);
  pinMode(TRG, OUTPUT);
  pinMode(ECH, INPUT);
  //------------------------
  Serial.begin(9600);
}

void loop() {

  display_timer(h1, h2, m2, m1, toogle);
  while (m1 <= 10 && trg == true) {
    m1++;
    run_sensor();
    timer_func(h1, h2, m2, m1, toogle);
    delay(1000);
    display_timer(h1, h2, m2, m1, toogle);
    Serial.println(m1);
  }
  run_sensor();

}
