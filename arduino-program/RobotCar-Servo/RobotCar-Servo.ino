/*
  RobotCar-Servo

  ポテンショメータのツマミを回して、サーボモータのPWM信号を変える

  2020年7月3日作成
  坂本 元
*/


#include <Servo.h>      // サーボライブラリ用のヘッダファイル

const int SERVO_PIN_RIGHT = 9;  // 右タイヤのサーボを接続しているピン
const int SERVO_PIN_LEFT = 10;  // 左タイヤのサーボを接続しているピン

Servo servo_right;      // 右タイヤのサーボの変数宣言
Servo servo_left;       // 左タイヤのサーボの変数宣言

int potentio1;          // ポテンショメータ１の読み取り値
int potentio2;          // ポテンショメータ２の読み取り値
int servo_right_pwm;    // サーボのPWM信号（右タイヤ）[マイクロ秒]
int servo_left_pwm;     // サーボのPWM信号（左タイヤ）[マイクロ秒]

/*
360度回転するサーボモータGeekservoはPWM信号によって、回転速度と回転方向が制御されます。
1500マイクロ秒のPWM信号はモータが停止します。
600-1500マイクロ秒のPWM信号はモータが正方向に回転します。PWM信号が1500マイクロ秒から離れるほど、回転速度は大きくなります。
1500-2400マイクロ秒のPWM信号はモータが逆方向に回転します。PWM信号が1500マイクロ秒から離れるほど、回転速度は大きくなります。
*/


void setup() {
  // サーボモータ
  servo_right.attach(SERVO_PIN_RIGHT);  // SERVO_PIN_RIGHTピンをサーボのPWM信号に設定
  servo_right.writeMicroseconds(1500);  // 1500マイクロ秒のPWM信号を出力する（初期値は回転停止）
  servo_left.attach(SERVO_PIN_LEFT);    // SERVO_PIN_LEFTピンをサーボのPWM信号に設定
  servo_left.writeMicroseconds(1500);   // 1500マイクロ秒のPWM信号を出力する（初期値は回転停止）

  // シリアルモニタ用
  Serial.begin(9600);                   // シリアル通信初期化、通信速度9600bps
}


void loop() {
  potentio1 = analogRead(A0);   // A0ピンの電圧をアナログ入力（0～1023）
  potentio2 = analogRead(A1);   // A1ピンの電圧をアナログ入力（0～1023）

  // アナログ入力0～1023をPWM信号の600～2400に換算
  servo_right_pwm = map(potentio1, 0, 1023, 600, 2400);   // 右タイヤ
  servo_left_pwm = map(potentio2, 0, 1023, 600, 2400);    // 左タイヤ

  servo_right.writeMicroseconds(servo_right_pwm);   // PWM信号を出力する（右タイヤ）[マイクロ秒]
  servo_left.writeMicroseconds(servo_left_pwm);     // PWM信号を出力する（左タイヤ）[マイクロ秒]

  delay(20);    // 20ミリ秒待つ（PWM信号一周期以上）

  // シリアルモニタに表示する
  Serial.print(potentio1);        // シリアル通信でポテンショメータ１を出力
  Serial.print(", ");
  Serial.print(servo_right_pwm);  // シリアル通信でPWM信号を出力（右タイヤ）
  Serial.print("[us], ");
  Serial.print(potentio2);        // シリアル通信でポテンショメータ２を出力
  Serial.print(", ");
  Serial.print(servo_left_pwm);   // シリアル通信でPWM信号を出力（左タイヤ）
  Serial.println("[us]");
}
