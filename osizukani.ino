/*

    @file osizukani.ino
    @brief 第3回ソレコン応募作品 『おしずカニ v[ﾟ∀ﾟ]V』

    @author Kei Takagi
    @date 2016.2.9
    D2-D9...LED
    D10...ソレノイド
    A0...MIC
    A1...Level調整
    A2...DUMMY(ON/OFF)

    Copyright (c) 2016 Kei Takagi
    Released under the MIT license
    http://opensource.org/licenses/mit-license.php

*/



#define LEDMAX 8
int led[LEDMAX] = { 2, 3, 4, 5, 6, 7, 8, 9};

int ai, v0, v1, wk, i;
unsigned long wktime;
unsigned long time1;
unsigned long time2;

void setup()
{
  for (i = 0; i < LEDMAX; i++)pinMode(led[i], OUTPUT);
  pinMode(10, OUTPUT);
  // Serial.begin(9600);

  for (i = 0; i < LEDMAX ; i++) {
    digitalWrite(led[i], HIGH);
    delay(80);
    digitalWrite(led[i], LOW);
  }

  for (i = LEDMAX - 1 ; i >= 0; i--) {
    digitalWrite(led[i], HIGH);
    delay(80);
    digitalWrite(led[i], LOW);
  }

  wk = 0;
  wktime = 0;
  time1 = 0;
  time2 = 0;
  //Serial.println(analogRead(A1) );
  //Serial.println(analogRead(A2) );

  if ( analogRead(A1) > 900 &&  analogRead(A2) > 900 ) {
    for (i = 0; i < LEDMAX ; i++) {
      digitalWrite(led[i], HIGH);
    }
    digitalWrite(10, HIGH);
    delay(1000);
    digitalWrite(10, LOW);
    for (i = 0; i < LEDMAX ; i++) {
      digitalWrite(led[i], LOW);
    }
  }
}

// ソフトウェアリセット
void(*resetFunc)(void) = 0;

void loop()
{
  ai = constrain(analogRead(A0), 200, 1000);
  v0 = map(ai, 200, 1000, 0, LEDMAX - 1);
  v1 = map( analogRead(A1), 0, 1023,  LEDMAX - 1, 0);

  if (wktime > millis())resetFunc(); // 約50日すぎた場合ソフトウェアリセット
  wktime = millis() ;

  //Serial.println(v0);

  if ( v1 != wk) {
    wk = v1;
    time1 = wktime + 1000;//1秒間表示する
  }

  for (i = 0; i < LEDMAX; i++)digitalWrite(led[i], LOW);
  if ( wktime < time1 ) {
    digitalWrite(led[v1], HIGH);
  } else if ( 250 < ai) {
    i = 0;
    do {
      digitalWrite(led[i], HIGH);
      i++;
    } while (i <= v0);
    if ( time2 < wktime ) {
      if ( v1 <= v0 ) {
        digitalWrite(10, HIGH);
        delay(100);
        digitalWrite(10, LOW);
        time2 = wktime + 300;//うるさくても0.3秒間無視する
      }
    }
  }
}
