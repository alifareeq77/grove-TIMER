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
TM1637 ts1637(CLK, DIO);
int m1 = 0, m2 = 0, s1 = 0, s2 = 0;
int toogle = 1;

void display_timer(int a, int b, int c, int d, int t) {
  ts1637.display(0, a);
  ts1637.display(1, b);
  ts1637.point(t);
  ts1637.display(2, c);
  ts1637.display(3, d);

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
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
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

void timer_func(int m11, int m22, int s22, int s11, int toogle) {
  // first digit
  if (m2 > 9) {
    m1++;
    m2 = 0;
  }
  //second digit
  if (s2 == 5 && s1 > 9) {
    m2++;
    s2 = 0;
    s1 = 0;
  }
  // third digit
  if (s1 > 9) {
    s2++;
    s1 = 0;
  }
  if (s1 % 2 == 0) {
    toogle = 0;
  } else {
    toogle = 1;
  }
}
void setup() {
  // --- setting up the timer--- 
  ts1637.init();
  ts1637.point(1); // set the two dots to be on
  ts1637.set(2);
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

  display_timer(m1, m2, s2, s1, toogle);
  while (s1 <= 10 && trg == true) {
    s1++;
    run_sensor();
    timer_func(m1, m2, s2, s1, toogle);
    delay(1000);
    display_timer(m1, m2, s2, s1, toogle);
  }
  run_sensor();

}
