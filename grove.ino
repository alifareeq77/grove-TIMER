#define TRG 8
#define ECH 11
#include <LiquidCrystal.h>

LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
bool trg = true; // initiale value for the timer
int m1 = 0, m2 = 0, s1 = 0, s2 = 0;
int toogle = 1;
bool mode_1 = true;
bool mode_2 = false;
bool mode_3 = false;
void display_timer() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("time: ");
  lcd.print(m1);
  lcd.print(m2);
  lcd.print(":");
  lcd.print(s2);
  lcd.print(s1);

}

void run_sensor() {
  int counter = 1 ;
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
  //--------------------------------
  if (distance > 70 && mode_1 == true) {
    while (counter != 3 && trg == true) {
      Serial.print("counter: ");
      Serial.println(counter);
      duration = pulseIn(ECH, HIGH);
      distance = duration * 0.034 / 2;
      Serial.println("increamenting");
      counter++;
      s1++;
      timer_func();
      display_timer();
      delay(1000);
    }
    if (counter == 3) {
      Serial.print("switchin trigger");
      trg = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("timer paused");
      delay(2000);
    }
  }
}

void timer_func() {
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
void select_mode() {
  // push buttons
}
void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  //--- setting up sensor---
  pinMode(TRG, OUTPUT);
  pinMode(ECH, INPUT);
  //------------------------
  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("select mode");
  while (mode_1 == false && mode_2 == false && mode_3 == false) {

    select_mode();
  }
}

// case check if distance is > 100cm  && pause


void loop() {

  while (s1 <= 10 && trg == true) {
    s1++;
    run_sensor();
    timer_func();
    delay(1000);
    display_timer();

  }
  if (trg == false && mode_1 == true) {
    run_sensor();
    lcd.setCursor(1, 1);
    if (distance < 70 && mode_1 == true) {
      int c = 0;
      while (distance < 70) {
        c++;
        delay(1000);
        Serial.println(c);
        if (c < 3) {
          run_sensor();
        }
        if (c == 3) {
          trg = true;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("continue");
          delay(2000);
          break;
        }
      }
    }
  }
}
