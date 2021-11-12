#include<Keypad.h>
#include<LiquidCrystal.h>
#include<Servo.h>

Servo motor1, motor2, motor3, motor4;
int red1 = 13, yellow1 = 12, green1 = 20;
int red2 = 21, yellow2 = 42, green2 = 43;
int red3 = 44, yellow3 = 45, green3 = 46;
int red4 = 51, yellow4 = 52, green4 = 53;
int motorStatus1 = 0, motorStatus2 = 0, motorStatus3 = 0, motorStatus4 = 0;
int pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;
int trigPin1 = 34, trigPin2 = 35, trigPin3 = 36, trigPin4 = 37;
int echoPin1 = 38, echoPin2 = 39, echoPin3 = 40, echoPin4 = 41;
int distance1, distance2, distance3, distance4;
long duration1, duration2, duration3, duration4;
const byte ROWS = 4;
const byte COLS = 4;
int pirPin1 = 2, pirPin2 = 28, pirPin3 = 29, pirPin4 = 30;
int pirStat1 = 0, pirStat2 = 0, pirStat3 = 0, pirStat4 = 0;
char lane = 0;
bool p = false;
String pass = "";
const int buzzer1 = 9, buzzer2 = 31, buzzer3 = 32, buzzer4 = 33;
char  keys[ROWS][COLS] = {
  {'7', '8', '9', 'A'},
  {'4', '5', '6', 'B'},
  {'1', '2', '3', 'C'},
  {'*', '0', '#', 'D'}
};

LiquidCrystal lcd(22, 23, 24, 25, 26, 27);
byte  rowPins[ROWS] = {3, 4, 5, 6};
byte colPins[COLS] = {7, 8, 10, 11};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(pirPin1, INPUT);
  pinMode(pirPin2, INPUT);
  pinMode(pirPin3, INPUT);
  pinMode(pirPin4, INPUT);

  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(buzzer3, OUTPUT);
  pinMode(buzzer4, OUTPUT);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.clear();

  Serial.begin(9600);
  Serial.println("Enter Password");
  lcd.clear();

  motor1.attach(47);
  motor2.attach(48);
  motor3.attach(49);
  motor4.attach(50);

  pinMode(red1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(red3, OUTPUT);
  pinMode(red4, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(yellow3, OUTPUT);
  pinMode(yellow4, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(green3, OUTPUT);
  pinMode(green4, OUTPUT);
}

void loop() {

  char key = keypad.getKey();

  if (key ) {

    Serial.print(key);
    pass = pass + key;

    if (key == '#') {

      if (pass == "4121#")
      {
        p = true;
        pass = "";
        lcd.clear();
        lcd.print("Welcome");
        Serial.println();
        Serial.println("Correct password");
        delay(100);
      }

      else {
        pass = "";
        p = false;
        Serial.println();
        Serial.println("Wrong Password! Please enter again");
        delay(100);
      }
    }
  }
  if (p)
  {
    if (key)
      lane = key;

    if (lane == '1') {

      lcd.clear();
      lcd.print("Lane 1 open");
      Serial.println("lane 1 open");
      digitalWrite(green1, HIGH);
      digitalWrite(yellow1, LOW);
      digitalWrite(red1, LOW);
      digitalWrite(green2, LOW);
      digitalWrite(yellow2, LOW);
      digitalWrite(red2, HIGH);
      digitalWrite(green3, LOW);
      digitalWrite(yellow3, LOW);
      digitalWrite(red3, HIGH);
      digitalWrite(green4, LOW);
      digitalWrite(yellow4, LOW);
      digitalWrite(red4, HIGH);

      pirStat2 = digitalRead(pirPin2);
      pirStat3 = digitalRead(pirPin3);
      pirStat4 = digitalRead(pirPin4);

      if (pirStat2 == HIGH) {

        digitalWrite(trigPin2, LOW);
        delay(2);
        digitalWrite(trigPin2, HIGH);
        delay(10);
        digitalWrite(trigPin2, LOW);

        duration2 = pulseIn(echoPin2, HIGH);
        distance2 = (duration2 * 0.034) / 2;

        Serial.println("Lane 2 car Distance(cm)=");
        Serial.println(distance2);

        if (distance2 <= 300) {
          if (motorStatus2 == 0) {
            motorStatus2 = 1;
            for (pos2 = 0; pos2 <= 90; pos2 = pos2 + 20)
            {
              motor2.write(pos2);
              delay(10);
            }
          }
        }

        else if (distance2 > 300 && distance2 <= 500) {

          if (motorStatus2 == 1) {
            motorStatus2 = 0;
            for (pos2 = 90; pos2 >= 0; pos2 = pos2 - 10)
            {
              motor2.write(pos2);
              delay(10);
            }
          }

          tone(buzzer2, 1000);
          delay(50);
          noTone(buzzer2);
          delay(10);

        }

        else {
          if (motorStatus2 == 1) {
            motorStatus2 = 0;
            for (pos2 = 90; pos2 >= 0; pos2 = pos2 - 10)
            {
              motor2.write(pos2);
              delay(10);
            }
          }
        }
      }

      else {
        noTone(buzzer2);
        delay(10);
      }

      if (pirStat3 == HIGH) {

        digitalWrite(trigPin3, LOW);
        delay(2);
        digitalWrite(trigPin3, HIGH);
        delay(10);
        digitalWrite(trigPin3, LOW);

        duration3 = pulseIn(echoPin3, HIGH);
        distance3 = (duration3 * 0.034) / 2;

        Serial.println("Lane 3 car Distance(cm)=");
        Serial.println(distance3);

        if (distance3 <= 300) {
          if (motorStatus3 == 0) {
            motorStatus3 = 1;
            for (pos3 = 0; pos3 <= 90; pos3 = pos3 + 20)
            {
              motor3.write(pos3);
              delay(10);
            }
          }
        }

        else if (distance3 > 300 && distance3 <= 500) {

          if (motorStatus3 == 1) {
            motorStatus3 = 0;
            for (pos3 = 90; pos3 >= 0; pos3 = pos3 - 10)
            {
              motor3.write(pos3);
              delay(10);
            }
          }

          tone(buzzer3, 1000);
          delay(50);
          noTone(buzzer3);
          delay(10);

        }

        else {
          if (motorStatus3 == 1) {
            motorStatus3 = 0;
            for (pos3 = 90; pos3 >= 0; pos3 = pos3 - 10)
            {
              motor3.write(pos3);
              delay(10);
            }
          }
        }
      }

      else {
        noTone(buzzer3);
        delay(10);
      }

      if (pirStat4 == HIGH) {

        digitalWrite(trigPin4, LOW);
        delay(2);
        digitalWrite(trigPin4, HIGH);
        delay(10);
        digitalWrite(trigPin4, LOW);

        duration4 = pulseIn(echoPin4, HIGH);
        distance4 = (duration4 * 0.034) / 2;

        Serial.println("Lane 4 car Distance(cm)=");
        Serial.println(distance4);

        if (distance4 <= 300) {
          if (motorStatus4 == 0) {
            motorStatus4 = 1;
            for (pos4 = 0; pos4 <= 90; pos4 = pos4 + 20)
            {
              motor4.write(pos4);
              delay(10);
            }
          }
        }

        else if (distance4 > 300 && distance4 <= 500) {

          if (motorStatus4 == 1) {
            motorStatus4 = 0;
            for (pos4 = 90; pos4 >= 0; pos4 = pos4 - 10)
            {
              motor4.write(pos4);
              delay(10);
            }
          }

          tone(buzzer4, 1000);
          delay(50);
          noTone(buzzer4);
          delay(10);

        }

        else {
          if (motorStatus4 == 1) {
            motorStatus4 = 0;
            for (pos4 = 90; pos4 >= 0; pos4 = pos4 - 10)
            {
              motor4.write(pos4);
              delay(10);
            }
          }
        }
      }
      else {
        noTone(buzzer4);
        delay(10);
      }
    }

    else if (lane == '2')
    {
      lcd.clear();
      lcd.print("Lane 2 open");
      Serial.println("Lane 2 open");
      digitalWrite(green1, LOW);
      digitalWrite(yellow1, LOW);
      digitalWrite(red1, HIGH);
      digitalWrite(green2, HIGH);
      digitalWrite(yellow2, LOW);
      digitalWrite(red2, LOW);
      digitalWrite(green3, LOW);
      digitalWrite(yellow3, LOW);
      digitalWrite(red3, HIGH);
      digitalWrite(green4, LOW);
      digitalWrite(yellow4, LOW);
      digitalWrite(red4, HIGH);

      pirStat1 = digitalRead(pirPin1);
      pirStat3 = digitalRead(pirPin3);
      pirStat4 = digitalRead(pirPin4);

      if (pirStat1 == HIGH) {

        digitalWrite(trigPin1, LOW);
        delay(2);
        digitalWrite(trigPin1, HIGH);
        delay(10);
        digitalWrite(trigPin1, LOW);

        duration1 = pulseIn(echoPin1, HIGH);
        distance1 = (duration1 * 0.034) / 2;

        Serial.println("Lane 1 car Distance(cm)=");
        Serial.println(distance1);

        if (distance1 <= 300) {
          if (motorStatus1 == 0) {
            motorStatus1 = 1;
            for (pos1 = 0; pos1 <= 90; pos1 = pos1 + 20)
            {
              motor1.write(pos1);
              delay(10);
            }
          }
        }

        else if (distance1 > 300 && distance1 <= 500) {

          if (motorStatus1 == 1) {
            motorStatus1 = 0;
            for (pos1 = 90; pos1 >= 0; pos1 = pos1 - 10)
            {
              motor1.write(pos1);
              delay(10);
            }
          }

          tone(buzzer1, 1000);
          delay(50);
          noTone(buzzer1);
          delay(10);
        }

        else {
          if (motorStatus1 == 1) {
            motorStatus1 = 0;
            for (pos1 = 90; pos1 >= 0; pos1 = pos1 - 10)
            {
              motor1.write(pos1);
              delay(10);
            }
          }
        }
      }

      else {
        noTone(buzzer1);
        delay(10);
      }

      if (pirStat3 == HIGH) {

        digitalWrite(trigPin3, LOW);
        delay(2);
        digitalWrite(trigPin3, HIGH);
        delay(10);
        digitalWrite(trigPin3, LOW);

        duration3 = pulseIn(echoPin3, HIGH);
        distance3 = (duration3 * 0.034) / 2;

        Serial.println("Lane 3 car Distance(cm)=");
        Serial.println(distance3);

        if (distance3 <= 300) {
          if (motorStatus3 == 0) {
            motorStatus3 = 1;
            for (pos3 = 0; pos3 <= 90; pos3 = pos3 + 20)
            {
              motor3.write(pos3);
              delay(10);
            }
          }
        }

        else if (distance3 > 300 && distance3 <= 500) {

          if (motorStatus3 == 1) {
            motorStatus3 = 0;
            for (pos3 = 90; pos3 >= 0; pos3 = pos3 - 10)
            {
              motor3.write(pos3);
              delay(10);
            }
          }

          tone(buzzer3, 1000);
          delay(50);
          noTone(buzzer3);
          delay(10);
        }

        else {
          if (motorStatus3 == 1) {
            motorStatus3 = 0;
            for (pos3 = 90; pos3 >= 0; pos3 = pos3 - 10)
            {
              motor3.write(pos3);
              delay(10);
            }
          }
        }
      }

      else {
        noTone(buzzer3);
        delay(10);
      }

      if (pirStat4 == HIGH) {

        digitalWrite(trigPin4, LOW);
        delay(2);
        digitalWrite(trigPin4, HIGH);
        delay(10);
        digitalWrite(trigPin4, LOW);

        duration4 = pulseIn(echoPin4, HIGH);
        distance4 = (duration4 * 0.034) / 2;

        Serial.println("Lane 4 car Distance(cm)=");
        Serial.println(distance4);

        if (distance4 <= 300) {
          if (motorStatus4 == 0) {
            motorStatus4 = 1;
            for (pos4 = 0; pos4 <= 90; pos4 = pos4 + 20)
            {
              motor4.write(pos4);
              delay(10);
            }
          }
        }

        else if (distance4 > 300 && distance4 <= 500) {

          if (motorStatus4 == 1) {
            motorStatus4 = 0;
            for (pos4 = 90; pos4 >= 0; pos4 = pos4 - 10)
            {
              motor4.write(pos4);
              delay(10);
            }
          }

          tone(buzzer4, 1000);
          delay(50);
          noTone(buzzer4);
          delay(10);
        }

        else {
          if (motorStatus4 == 1) {
            motorStatus4 = 0;
            for (pos4 = 90; pos4 >= 0; pos4 = pos4 - 10)
            {
              motor4.write(pos4);
              delay(10);
            }
          }
        }
      }

      else {
        noTone(buzzer4);
        delay(10);
      }
    }

    else if (lane == '3')
    {
      lcd.clear();
      lcd.print("Lane 3 open");
      Serial.println("Lane 3 open");
      digitalWrite(green1, LOW);
      digitalWrite(yellow1, LOW);
      digitalWrite(red1, HIGH);
      digitalWrite(green2, LOW);
      digitalWrite(yellow2, LOW);
      digitalWrite(red2, HIGH);
      digitalWrite(green3, HIGH);
      digitalWrite(yellow3, LOW);
      digitalWrite(red3, LOW);
      digitalWrite(green4, LOW);
      digitalWrite(yellow4, LOW);
      digitalWrite(red4, HIGH);

      pirStat2 = digitalRead(pirPin2);
      pirStat1 = digitalRead(pirPin1);
      pirStat4 = digitalRead(pirPin4);

      if (pirStat2 == HIGH) {

        digitalWrite(trigPin2, LOW);
        delay(2);
        digitalWrite(trigPin2, HIGH);
        delay(10);
        digitalWrite(trigPin2, LOW);

        duration2 = pulseIn(echoPin2, HIGH);
        distance2 = (duration2 * 0.034) / 2;

        Serial.println("Lane 2 car Distance(cm)=");
        Serial.println(distance2);

        if (distance2 <= 300) {
          if (motorStatus2 == 0) {
            motorStatus2 = 1;
            for (pos2 = 0; pos2 <= 90; pos2 = pos2 + 20)
            {
              motor2.write(pos2);
              delay(10);
            }
          }
        }

        else if (distance2 > 300 && distance2 <= 500) {

          if (motorStatus2 == 1) {
            motorStatus2 = 0;
            for (pos2 = 90; pos2 >= 0; pos2 = pos2 - 10)
            {
              motor2.write(pos2);
              delay(10);
            }
          }

          tone(buzzer2, 1000);
          delay(50);
          noTone(buzzer2);
          delay(10);
        }

        else {
          if (motorStatus2 == 1) {
            motorStatus2 = 0;
            for (pos2 = 90; pos2 >= 0; pos2 = pos2 - 10)
            {
              motor2.write(pos2);
              delay(10);
            }
          }
        }
      }

      else {
        noTone(buzzer2);
        delay(10);
      }

      if (pirStat1 == HIGH) {

        digitalWrite(trigPin1, LOW);
        delay(2);
        digitalWrite(trigPin1, HIGH);
        delay(10);
        digitalWrite(trigPin1, LOW);

        duration1 = pulseIn(echoPin1, HIGH);
        distance1 = (duration1 * 0.034) / 2;

        Serial.println("Lane 1 car Distance(cm)=");
        Serial.println(distance1);

        if (distance1 <= 300) {
          if (motorStatus1 == 0) {
            motorStatus1 = 1;
            for (pos1 = 0; pos1 <= 90; pos1 = pos1 + 20)
            {
              motor1.write(pos1);
              delay(10);
            }
          }
        }

        else if (distance1 > 300 && distance1 <= 500) {

          if (motorStatus1 == 1) {
            motorStatus1 = 0;
            for (pos1 = 90; pos1 >= 0; pos1 = pos1 - 10)
            {
              motor1.write(pos1);
              delay(10);
            }
          }

          tone(buzzer1, 1000);
          delay(50);
          noTone(buzzer1);
          delay(10);
        }

        else {
          if (motorStatus1 == 1) {
            motorStatus1 = 0;
            for (pos1 = 90; pos1 >= 0; pos1 = pos1 - 10)
            {
              motor1.write(pos1);
              delay(10);
            }
          }
        }
      }

      else {
        noTone(buzzer1);
        delay(10);
      }

      if (pirStat4 == HIGH) {

        digitalWrite(trigPin4, LOW);
        delay(2);
        digitalWrite(trigPin4, HIGH);
        delay(10);
        digitalWrite(trigPin4, LOW);

        duration4 = pulseIn(echoPin4, HIGH);
        distance4 = (duration4 * 0.034) / 2;

        Serial.println("Lane 4 car Distance(cm)=");
        Serial.println(distance4);

        if (distance4 <= 300) {
          if (motorStatus4 == 0) {
            motorStatus4 = 1;
            for (pos4 = 0; pos4 <= 90; pos4 = pos4 + 20)
            {
              motor4.write(pos4);
              delay(10);
            }
          }
        }

        else if (distance4 > 300 && distance4 <= 500) {

          if (motorStatus4 == 1) {
            motorStatus4 = 0;
            for (pos4 = 90; pos4 >= 0; pos4 = pos4 - 10)
            {
              motor4.write(pos4);
              delay(10);
            }
          }

          tone(buzzer4, 1000);
          delay(50);
          noTone(buzzer4);
          delay(10);
        }

        else {
          if (motorStatus4 == 1) {
            motorStatus4 = 0;
            for (pos4 = 90; pos4 >= 0; pos4 = pos4 - 10)
            {
              motor4.write(pos4);
              delay(10);
            }
          }
        }
      }

      else {
        noTone(buzzer4);
        delay(10);
      }
    }

    else if (lane == '4')
    {
      lcd.clear();
      lcd.print("Lane 4 open");
      Serial.println("Lane 4 open");
      digitalWrite(green1, LOW);
      digitalWrite(yellow1, LOW);
      digitalWrite(red1, HIGH);
      digitalWrite(green2, LOW);
      digitalWrite(yellow2, LOW);
      digitalWrite(red2, HIGH);
      digitalWrite(green3, LOW);
      digitalWrite(yellow3, LOW);
      digitalWrite(red3, HIGH);
      digitalWrite(green4, HIGH);
      digitalWrite(yellow4, LOW);
      digitalWrite(red4, LOW);

      pirStat2 = digitalRead(pirPin2);
      pirStat3 = digitalRead(pirPin3);
      pirStat1 = digitalRead(pirPin1);

      if (pirStat2 == HIGH) {

        digitalWrite(trigPin2, LOW);
        delay(2);
        digitalWrite(trigPin2, HIGH);
        delay(10);
        digitalWrite(trigPin2, LOW);

        duration2 = pulseIn(echoPin2, HIGH);
        distance2 = (duration2 * 0.034) / 2;

        Serial.println("Lane 2 car Distance(cm)=");
        Serial.println(distance2);

        if (distance2 <= 300) {
          if (motorStatus2 == 0) {
            motorStatus2 = 1;
            for (pos2 = 0; pos2 <= 90; pos2 = pos2 + 20)
            {
              motor2.write(pos2);
              delay(10);
            }
          }
        }

        else if (distance2 > 300 && distance2 <= 500) {

          if (motorStatus2 == 1) {
            motorStatus2 = 0;
            for (pos2 = 90; pos2 >= 0; pos2 = pos2 - 10)
            {
              motor2.write(pos2);
              delay(10);
            }
          }

          tone(buzzer2, 1000);
          delay(50);
          noTone(buzzer2);
          delay(10);
        }

        else {
          if (motorStatus2 == 1) {
            motorStatus2 = 0;
            for (pos2 = 90; pos2 >= 0; pos2 = pos2 - 10)
            {
              motor2.write(pos2);
              delay(10);
            }
          }
        }
      }

      else {
        noTone(buzzer2);
        delay(10);
      }

      if (pirStat3 == HIGH) {

        digitalWrite(trigPin3, LOW);
        delay(2);
        digitalWrite(trigPin3, HIGH);
        delay(10);
        digitalWrite(trigPin3, LOW);

        duration3 = pulseIn(echoPin3, HIGH);
        distance3 = (duration3 * 0.034) / 2;

        Serial.println("Lane 3 car Distance(cm)=");
        Serial.println(distance3);

        if (distance3 <= 300) {
          if (motorStatus3 == 0) {
            motorStatus3 = 1;
            for (pos3 = 0; pos3 <= 90; pos3 = pos3 + 20)
            {
              motor3.write(pos3);
              delay(10);
            }
          }
        }

        else if (distance3 > 300 && distance3 <= 500) {

          if (motorStatus3 == 1) {
            motorStatus3 = 0;
            for (pos3 = 90; pos3 >= 0; pos3 = pos3 - 10)
            {
              motor3.write(pos3);
              delay(10);
            }
          }

          tone(buzzer3, 1000);
          delay(50);
          noTone(buzzer3);
          delay(10);
        }

        else {
          if (motorStatus3 == 1) {
            motorStatus3 = 0;
            for (pos3 = 90; pos3 >= 0; pos3 = pos3 - 10)
            {
              motor3.write(pos3);
              delay(10);
            }
          }
        }
      }

      else {
        noTone(buzzer3);
        delay(10);
      }

      if (pirStat1 == HIGH) {

        digitalWrite(trigPin1, LOW);
        delay(2);
        digitalWrite(trigPin1, HIGH);
        delay(10);
        digitalWrite(trigPin1, LOW);

        duration1 = pulseIn(echoPin1, HIGH);
        distance1 = (duration1 * 0.034) / 2;

        Serial.println("Lane 1 car Distance(cm)=");
        Serial.println(distance1);

        if (distance1 <= 300) {
          if (motorStatus1 == 0) {
            motorStatus1 = 1;
            for (pos1 = 0; pos1 <= 90; pos1 = pos1 + 20)
            {
              motor1.write(pos1);
              delay(10);
            }
          }
        }

        else if (distance1 > 300 && distance1 <= 500) {

          if (motorStatus1 == 1) {
            motorStatus1 = 0;
            for (pos1 = 90; pos1 >= 0; pos1 = pos1 - 10)
            {
              motor1.write(pos1);
              delay(10);
            }
          }

          tone(buzzer1, 1000);
          delay(50);
          noTone(buzzer1);
          delay(10);
        }

        else {
          if (motorStatus1 == 1) {
            motorStatus1 = 0;
            for (pos1 = 90; pos1 >= 0; pos1 = pos1 - 10)
            {
              motor1.write(pos1);
              delay(10);
            }
          }
        }
      }

      else {
        noTone(buzzer1);
        delay(10);
      }
    }

    else {
      Serial.println("Please enter a valid lane number");
    }
  }
}
