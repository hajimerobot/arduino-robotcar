/*
  RobotCar-Auto

  自動走行するロボットカー
  ロボットカーを、前進、後退、右回転、左回転、の順に動かす。

  2020年7月3日作成
  坂本 元
*/


#include <Servo.h>     // サーボライブラリ用のヘッダファイル

const int SERVO_PIN_RIGHT = 9;  // 右タイヤのサーボを接続しているピン
const int SERVO_PIN_LEFT = 10;  // 左タイヤのサーボを接続しているピン

Servo servo_right;      // 右タイヤのサーボの変数宣言
Servo servo_left;       // 左タイヤのサーボの変数宣言

/*
360度回転するサーボモータGeekservoはPWM信号によって、回転速度と回転方向が制御されます。
1500マイクロ秒のPWM信号はモータが停止します。
600-1500マイクロ秒のPWM信号はモータが正方向に回転します。PWM信号が1500マイクロ秒から離れるほど、回転速度は大きくなります。
1500-2400マイクロ秒のPWM信号はモータが逆方向に回転します。PWM信号が1500マイクロ秒から離れるほど、回転速度は大きくなります。
*/

const int servo_stop = 1500;        // 停止のPWM信号（右タイヤ）（左タイヤ）[マイクロ秒]
const int servo_forward_r = 1100;   // 前進のPWM信号（右タイヤ）[マイクロ秒]
const int servo_forward_l = 1880;   //1900// 前進のPWM信号（左タイヤ）[マイクロ秒]
const int servo_backward_r = 1880;  //1900// 後退のPWM信号（右タイヤ）[マイクロ秒]
const int servo_backward_l = 1100;  // 後退のPWM信号（左タイヤ）[マイクロ秒]
const int servo_right_r = 1880;  //1900// 右回転のPWM信号（右タイヤ）[マイクロ秒]
const int servo_right_l = 1880;  //1900// 右回転のPWM信号（左タイヤ）[マイクロ秒]
const int servo_left_r = 1100;  // 左回転のPWM信号（右タイヤ）[マイクロ秒]
const int servo_left_l = 1100;  // 左回転のPWM信号（左タイヤ）[マイクロ秒]


void setup() {
  // サーボモータ
  servo_right.attach(SERVO_PIN_RIGHT);  // SERVO_PIN_RIGHTピンをサーボのPWM信号に設定
  servo_right.writeMicroseconds(1500);  // 1500マイクロ秒のPWM信号を出力する（初期値は回転停止）
  servo_left.attach(SERVO_PIN_LEFT);    // SERVO_PIN_LEFTピンをサーボのPWM信号に設定
  servo_left.writeMicroseconds(1500);   // 1500マイクロ秒のPWM信号を出力する（初期値は回転停止）
}


void loop() {
  // 急な動作の切替をさけるために、動作の間に停止（servo_stop）を入れている
  // 停止
  servo_right.writeMicroseconds(servo_stop);   // 停止のPWM信号を出力する（右タイヤ）
  servo_left.writeMicroseconds(servo_stop);    // 停止のPWM信号を出力する（左タイヤ）
  delay(5000);    // 5秒待つ

  // 前進
  servo_right.writeMicroseconds(servo_forward_r);  // 前進のPWM信号を出力する（右タイヤ）
  servo_left.writeMicroseconds(servo_forward_l);   // 前進のPWM信号を出力する（左タイヤ）
  delay(3000);    // 3秒待つ

  // 停止
  servo_right.writeMicroseconds(servo_stop);   // 停止のPWM信号を出力する（右タイヤ）
  servo_left.writeMicroseconds(servo_stop);    // 停止のPWM信号を出力する（左タイヤ）
  delay(1000);    // 1秒待つ

  // 後退
  servo_right.writeMicroseconds(servo_backward_r);   // 後退のPWM信号を出力する（右タイヤ）
  servo_left.writeMicroseconds(servo_backward_l);    // 後退のPWM信号を出力する（左タイヤ）
  delay(3000);    // 3秒待つ

  // 停止
  servo_right.writeMicroseconds(servo_stop);   // 停止のPWM信号を出力する（右タイヤ）
  servo_left.writeMicroseconds(servo_stop);    // 停止のPWM信号を出力する（左タイヤ）
  delay(1000);    // 1秒待つ

  // 右回転
  servo_right.writeMicroseconds(servo_right_r);  // 右回転のPWM信号を出力する（右タイヤ）
  servo_left.writeMicroseconds(servo_right_l);   // 右回転のPWM信号を出力する（左タイヤ）
  delay(3000);    // 3秒待つ

  // 停止
  servo_right.writeMicroseconds(servo_stop);   // 停止のPWM信号を出力する（右タイヤ）
  servo_left.writeMicroseconds(servo_stop);    // 停止のPWM信号を出力する（左タイヤ）
  delay(1000);    // 1秒待つ

  // 左回転
  servo_right.writeMicroseconds(servo_left_r);   // 左回転のPWM信号を出力する（右タイヤ）
  servo_left.writeMicroseconds(servo_left_l);    // 左回転のPWM信号を出力する（左タイヤ）
  delay(3000);    // 3秒待つ   
}
