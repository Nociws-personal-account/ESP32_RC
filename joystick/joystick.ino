// Arduino入門編⑦ ジョイスティックでLEDの点灯強度を制御
// https://burariweb.info
 
 const int X_PIN = 34;  // ジョイスティック左X軸方向をアナログピンA0に入力
 const int Y_PIN = 35;  // ジョイスティック右X軸方向をアナログピンA1に入力
//  const int SW_PIN = 2;  // センタースイッチをデジタルピンD2に入力
//  const int SW_PINR = 7;  // センタースイッチをデジタルピンD11に入力
 
//  const int Xmin_LED = 3;   // 左LED：デジタルピン3
//  const int Xmax_LED = 11;   // 右LED：デジタルピン5
//  const int Ymin_LED = 9;   // 下LED：デジタルピン9
//  const int Ymax_LED = 10;  // 上LED：デジタルピン10
//  const int SW_LED = 5;    // スイッチ判定LED：デジタルピン12
//  const int SW_LEDR = 6;    // スイッチ判定LED：デジタルピン13

//  const int Dmax = 150;    // 最大のデューティ比
 
//  int X_POS ;            // X軸方向の読み取り値の変数を整数型に
//  int Y_POS ;            // Y軸方向の読み取り値の変数を整数型に
//  int SW_POS ;           // センタースイッチの読み取り値の変数を整数型に
//  int SW_POSR ;           // センタースイッチの読み取り値の変数を整数型に
//  float OFFSET = 0.1;  // センター付近のオフセット値を5％に設定
//  int DUTY ;             // ディーティ比用変数
 
 void setup(){
 
   pinMode(X_PIN, ANALOG);          // A0ピンを入力に(省略可)
   pinMode(Y_PIN, ANALOG);          // A1ピンを入力に(省略可)
  //  pinMode(SW_PIN, INPUT_PULLUP);  // D2ピンをプルアップして入力に
  //  pinMode(SW_PINR, INPUT_PULLUP);  // D2ピンをプルアップして入力に
 
  //  pinMode(Xmin_LED, OUTPUT) ;     //
  //  pinMode(Xmax_LED, OUTPUT) ;     // それぞれのピンを出力に設定
  //  pinMode(Ymin_LED, OUTPUT) ;     //
  //  pinMode(Ymin_LED, OUTPUT) ;     //
  //  pinMode(SW_LED, OUTPUT);        // D12ピンを出力に
  //  pinMode(SW_LEDR, OUTPUT);        // D12ピンを出力に
 
   Serial.begin(9600);             // シリアル通信の開始
  
}
 
 
 void loop(){
 
   X_POS = analogRead(X_PIN);     // X軸方向のアナログ値を読み取る
   Y_POS = analogRead(Y_PIN);     // Y軸方向のアナログ値を読み取る
  //  SW_POS = digitalRead(SW_PIN);  // センタースイッチの状態を読み取る
  //  SW_POSR = digitalRead(SW_PINR);  // センタースイッチの状態を読み取る
 
  //  if(SW_POS == 0){
  //    digitalWrite(SW_LED, HIGH);  // スイッチが押されるとLEDを点灯
  //  } else{                        // 押されていない場合は消灯させる
  //    digitalWrite(SW_LED, LOW);
  //  }

  //  if(SW_POSR == 0){
  //    digitalWrite(SW_LEDR, HIGH);  // スイッチが押されるとLEDを点灯
  //  } else{                        // 押されていない場合は消灯させる
  //    digitalWrite(SW_LEDR, LOW);
  //  }
 
  //  if((X_POS > 512-512*OFFSET) && (X_POS < 512+512*OFFSET)){  // X軸方向のセンター(512)の前後OFFSET分はLEDを消灯
  //    analogWrite(Xmin_LED, 0);
  //    analogWrite(Xmax_LED, 0);
  //  }
 
  //  if((Y_POS > 512-512*OFFSET) && (Y_POS < 512+512*OFFSET)){  // Y軸方向のセンター(512)の前後OFFSET分はLEDを消灯
  //    analogWrite(Ymin_LED, 0);
  //    analogWrite(Ymax_LED, 0);
  //  }
  
 
  //  if(X_POS <= 512-512*OFFSET){                      // スティックを左に倒したときの動作
  //    DUTY = map(X_POS,512-512*OFFSET,0,0,Dmax);       // デューティー比を0~255の範囲に調整
  //    analogWrite(Xmin_LED, DUTY);
  //    analogWrite(Xmax_LED, 0);
  //  }
  //  else if(X_POS >= 512+512*OFFSET){                 // スティックを下に倒したときの動作
  //    DUTY = map(X_POS,512+512*OFFSET,1023,0,Dmax);    // デューティー比を0~255の範囲に調整
  //    analogWrite(Xmax_LED, DUTY);
  //    analogWrite(Xmin_LED, 0);
  //  }
 
 
  //  if(Y_POS <= 512-512*OFFSET){                      // スティックを上に倒したときの動作
  //    DUTY = map(Y_POS,512-512*OFFSET,0,0,Dmax);       // デューティー比を0~255の範囲に調整
  //    analogWrite(Ymin_LED, DUTY);
  //    analogWrite(Ymax_LED, 0);
  //  }
  //  else if(Y_POS >= 512+512*OFFSET){                 // スティックを下に倒したときの動作
  //    DUTY = map(Y_POS,512+512*OFFSET,1023,0,Dmax);    // デューティー比を0~255の範囲に調整
  //    analogWrite(Ymax_LED, DUTY);
  //    analogWrite(Ymin_LED, 0);
  //  }
  
  
   Serial.print("X: ");     // シリアルモニタにそれぞれの値を出力
   Serial.print(X_POS);
   Serial.print("  Y: ");
   Serial.println(Y_POS);
  //  Serial.print("  SW: ");
  //  Serial.println(SW_POS);
 
//   delay(100);
  
}
