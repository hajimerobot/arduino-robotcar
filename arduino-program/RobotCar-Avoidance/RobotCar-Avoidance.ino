/*
  RobotCar-Avoidance

  障害物をよけて進むロボットカー

  超音波距離センサーで障害物までの距離を測り、
  障害物が真正面の近い距離にあるかどうかを判断する。
  近くにあるとき、ロボットカーは右回転し、障害物をよける。
  近くにないとき、ロボットカーは直進する。

  2020年7月3日作成
  坂本 元
*/


// include
#include <Servo.h>     // サーボライブラリ用のヘッダファイル

const int SERVO_PIN_RIGHT = 9;  // 右タイヤのサーボを接続しているピン
const int SERVO_PIN_LEFT = 10;  // 左タイヤのサーボを接続しているピン

// 超音波距離センサのVCCピンを  5Vに接続
// 超音波距離センサのTrigピンを Arduinoのデジタルピン12に接続
// 超音波距離センサのEchoピンを Arduinoのデジタルピン11に接続
// 超音波距離センサのGndピンを  GNDに接続
const int TRIG_PIN = 12;       // 超音波距離センサのTrigピンを接続しているピン
const int ECHO_PIN = 11;       // 超音波距離センサのEchoピンを接続しているピン
const int PULSE_TIMEOUT = 150000;  // タイムアウト0.15[s]

Servo servo_right;       // 右タイヤのサーボの変数宣言
Servo servo_left;        // 左タイヤのサーボの変数宣言

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

  // 超音波センサー
  pinMode(TRIG_PIN, OUTPUT);    // TRIG_PINをデジタル出力に設定
  pinMode(ECHO_PIN, INPUT);     // ECHO_PINをデジタル入力に設定

  // シリアルモニタ用
//  Serial.begin(9600);                 // シリアル通信初期化、通信速度9600bps
}


void loop() {
  float distance = ultrasonicSensorRead();    // 超音波距離センサから測定距離を読み取る

  if( distance >= 10 ) {
    // 前進
    servo_right.writeMicroseconds(servo_forward_r);   // 前進のPWM信号を出力する（右タイヤ）
    servo_left.writeMicroseconds(servo_forward_l);    // 前進のPWM信号を出力する（左タイヤ）
    delay(20);      // 20ミリ秒待つ（PWM一周期分）
  } 
  else  { // 測定距離が10cm未満
    // 右回転
    servo_right.writeMicroseconds(servo_right_r);   // 右回転のPWM信号を出力する（右タイヤ）
    servo_left.writeMicroseconds(servo_right_l);    // 右回転のPWM信号を出力する（左タイヤ）
    delay(1000);    // 1秒待つ（最低1秒間回転させる）  
  }

  // シリアルモニタに表示する
//  Serial.print(distance);                     // シリアル通信で距離データを出力
//  Serial.println("[cm]");
}


/* 
  超音波距離センサーで距離を測定する関数
  戻り値は、距離[cm]
*/
float ultrasonicSensorRead() {
  long duration = 0;      // 測定したパルス幅（マイクロ秒[us]）を記憶する変数
  float distance = 0;     // パルス幅から距離（センチ[cm]）を計算した値を記憶する変数

  // TRIG_PINに10usのパルスを出力する
  digitalWrite(TRIG_PIN, LOW);    // TRIG_PINをLOWにする
  delayMicroseconds(2);           // 2マイクロ秒待つ

  digitalWrite(TRIG_PIN, HIGH);   // TRIG_PINをHIGHにする
  delayMicroseconds(10);          // 10マイクロ秒待つ

  digitalWrite(TRIG_PIN, LOW);    // TRIG_PINをLOWにする
  delayMicroseconds(2);           // 2マイクロ秒待つ

  duration = pulseIn(ECHO_PIN, HIGH, PULSE_TIMEOUT);   // ECHO_PINのパルス幅を測定する(単位[μs])
  distance = duration*0.017;  //  パルス幅から距離（cm）を計算する
                              // 音速340[m/s]=34000[cm/s]、距離=速度x時間、
                              //  duration*1e-6*34000/2=duration*0.017（/2は往復のため）
  return distance;        // 測定した距離[cm]を返す
}
