/*
  RobotCar-UltrasonicSensor

  超音波距離センサーで距離を測る

  2020年7月3日作成
  坂本 元
*/


// 超音波距離センサのVCCピンを  5Vに接続
// 超音波距離センサのTrigピンを Arduinoのデジタルピン12に接続
// 超音波距離センサのEchoピンを Arduinoのデジタルピン11に接続
// 超音波距離センサのGndピンを  GNDに接続
const int TRIG_PIN = 12;       // 超音波距離センサのTrigピンを接続しているピン
const int ECHO_PIN = 11;       // 超音波距離センサのEchoピンを接続しているピン
const int PULSE_TIMEOUT = 150000;  // タイムアウト0.15[s]


void setup() {
  // 超音波センサー
  pinMode(TRIG_PIN, OUTPUT);    // TRIG_PINをデジタル出力に設定
  pinMode(ECHO_PIN, INPUT);     // ECHO_PINをデジタル入力に設定

  // シリアルモニタ用
  Serial.begin(9600);           // シリアル通信初期化、通信速度9600bps
}


void loop() {
  float distance = ultrasonicSensorRead();    // 超音波距離センサから測定距離を読み取る

  // シリアルモニタに表示する
  Serial.print(distance);                     // シリアル通信で距離データを出力
  Serial.println("[cm]");
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
