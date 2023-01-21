// Arduino入門編⑦ ジョイスティックでLEDの点灯強度を制御
// https://burariweb.info
 
 const int Left_X_PIN = 34;  // ジョイスティック左X軸方向をアナログピンA0に入力
 const int Right_X_PIN = 35;  // ジョイスティック右X軸方向をアナログピンA1に入力
//  const int SW_PIN = 2;  // センタースイッチをデジタルピンD2に入力
//  const int SW_PINR = 7;  // センタースイッチをデジタルピンD11に入力
 
 const int Xmin_LED = 33;   // 左LED：デジタルピン3
 const int Xmax_LED = 25;   // 右LED：デジタルピン5
 const int Ymin_LED = 26;   // 下LED：デジタルピン9
 const int Ymax_LED = 27;  // 上LED：デジタルピン10

 const int PWMCH1 = 0;  // 上LED：デジタルピン10
 const int PWMCH2 = 1;  // 上LED：デジタルピン10
 const int PWMCH3 = 2;  // 上LED：デジタルピン10
 const int PWMCH4 = 3;  // 上LED：デジタルピン10
//  const int SW_LED = 5;    // スイッチ判定LED：デジタルピン12
//  const int SW_LEDR = 6;    // スイッチ判定LED：デジタルピン13

 
  int Left_X_POS ;            // ジョイスティック左X軸方向の読み取り値の変数を整数型に
  int Right_X_POS ;            // ジョイスティック右X軸方向の読み取り値の変数を整数型に
//  int SW_POS ;           // センタースイッチの読み取り値の変数を整数型に
//  int SW_POSR ;           // センタースイッチの読み取り値の変数を整数型に
 float OFFSET = 0.1;  // センター付近のオフセット値を5％に設定
 int DUTY ;             // ディーティ比用変数
 const int Dmax = 150;    // 最大のデューティ比

 void setup(){
 
   pinMode(Left_X_PIN, ANALOG);          // A0ピンを入力に(省略可)
   pinMode(Right_X_PIN, ANALOG);          // A1ピンを入力に(省略可)
  //  pinMode(SW_PIN, INPUT_PULLUP);  // D2ピンをプルアップして入力に
  //  pinMode(SW_PINR, INPUT_PULLUP);  // D2ピンをプルアップして入力に
 
  //  pinMode(Xmin_LED, OUTPUT) ;     //
  //  pinMode(Xmax_LED, OUTPUT) ;     // それぞれのピンを出力に設定
  //  pinMode(Ymin_LED, OUTPUT) ;     //
  //  pinMode(Ymin_LED, OUTPUT) ;     //

   ledcSetup(PWMCH1, 7812.5, 8);
   ledcSetup(PWMCH2, 7812.5, 8);
   ledcSetup(PWMCH3, 7812.5, 8);
   ledcSetup(PWMCH4, 7812.5, 8);
   ledcAttachPin(Xmin_LED, PWMCH1);
   ledcAttachPin(Xmax_LED, PWMCH2);
   ledcAttachPin(Ymin_LED, PWMCH3);
   ledcAttachPin(Ymax_LED, PWMCH4);

  //  pinMode(SW_LED, OUTPUT);        // D12ピンを出力に
  //  pinMode(SW_LEDR, OUTPUT);        // D12ピンを出力に

 
   Serial.begin(9600);             // シリアル通信の開始
  
}
 
 
 void loop(){
 
   Left_X_POS = analogRead(Left_X_PIN);     // X軸方向のアナログ値を読み取る
   Right_X_POS = analogRead(Right_X_PIN);     // Y軸方向のアナログ値を読み取る
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
 
   if((Left_X_POS > 512-512*OFFSET) && (Left_X_POS < 512+512*OFFSET)){  // X軸方向のセンター(512)の前後OFFSET分はLEDを消灯
     ledcWrite(PWMCH1, 0);
     ledcWrite(PWMCH2, 0);
   }
 
   if((Right_X_POS > 512-512*OFFSET) && (Right_X_POS < 512+512*OFFSET)){  // Y軸方向のセンター(512)の前後OFFSET分はLEDを消灯
     ledcWrite(PWMCH3, 0);
     ledcWrite(PWMCH4, 0);
   }
  
 
   if(Left_X_POS <= 512-512*OFFSET){                      // スティックを左に倒したときの動作
     DUTY = map(Left_X_POS,512-512*OFFSET,0,0,Dmax);       // デューティー比を0~255の範囲に調整
     ledcWrite(PWMCH1, DUTY);
     ledcWrite(PWMCH2, 0);
   }
   else if(Left_X_POS >= 512+512*OFFSET){                 // スティックを下に倒したときの動作
     DUTY = map(Left_X_POS,512+512*OFFSET,1023,0,Dmax);    // デューティー比を0~255の範囲に調整
     ledcWrite(PWMCH2, DUTY);
     ledcWrite(PWMCH1, 0);
   }
 
 
   if(Right_X_POS <= 512-512*OFFSET){                      // スティックを上に倒したときの動作
     DUTY = map(Right_X_POS,512-512*OFFSET,0,0,Dmax);       // デューティー比を0~255の範囲に調整
     ledcWrite(PWMCH3, DUTY);
     ledcWrite(PWMCH4, 0);
   }
   else if(Right_X_POS >= 512+512*OFFSET){                 // スティックを下に倒したときの動作
     DUTY = map(Right_X_POS,512+512*OFFSET,1023,0,Dmax);    // デューティー比を0~255の範囲に調整
     ledcWrite(PWMCH4, DUTY);
     ledcWrite(PWMCH3, 0);
   }
  
  
   Serial.print("X: ");     // シリアルモニタにそれぞれの値を出力
   Serial.print(Left_X_POS);
   Serial.print("  Y: ");
   Serial.print(Right_X_POS);
   Serial.print("  DUTY: ");
   Serial.println(DUTY);
  //  Serial.print("  SW: ");
  //  Serial.println(SW_POS);
 
//   delay(100);
  
}
