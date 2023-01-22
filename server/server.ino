#include <WiFiUdp.h>
#include "WiFi.h"

const char * ssid = "ESP32UDP";             // SSID
const char * password = "12345678";         // password

static const int Remote_Port = 9000;        // Destination port
static const int Org_Port = 9000;           // Source port

WiFiUDP UDP;

// PWM出力関係
const int Xmin_LED = 33;   // 左LED：デジタルピン3
const int Xmax_LED = 25;   // 右LED：デジタルピン5
const int Ymin_LED = 26;   // 下LED：デジタルピン9
const int Ymax_LED = 27;  // 上LED：デジタルピン10
const int PWMCH1 = 0;  // 上LED：デジタルピン10
const int PWMCH2 = 1;  // 上LED：デジタルピン10
const int PWMCH3 = 2;  // 上LED：デジタルピン10
const int PWMCH4 = 3;  // 上LED：デジタルピン10
int Left_X_POS ;            // ジョイスティック左X軸方向の読み取り値の変数を整数型に
int Right_X_POS ;            // ジョイスティック右X軸方向の読み取り値の変数を整数型に
float OFFSET = 0.1;  // センター付近のオフセット値を5％に設定
int DUTY ;             // ディーティ比用変数
const int Dmax = 150;    // 最大のデューティ比

void setup()
{
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  delay(1000);

  Serial.print("AP IP address: ");            //    192.168.4.1
  Serial.println(WiFi.softAPIP());

  UDP.begin(Org_Port);
  Serial.println("Server OK");

  // PWM出力関係
  ledcSetup(PWMCH1, 7812.5, 8);
  ledcSetup(PWMCH2, 7812.5, 8);
  ledcSetup(PWMCH3, 7812.5, 8);
  ledcSetup(PWMCH4, 7812.5, 8);
  ledcAttachPin(Xmin_LED, PWMCH1);
  ledcAttachPin(Xmax_LED, PWMCH2);
  ledcAttachPin(Ymin_LED, PWMCH3);
  ledcAttachPin(Ymax_LED, PWMCH4);
}

void loop()
{
  char rv_data[4] = {0,0,0,0};
  // int test = 0;
  // String rv_data_st = "";

  if (UDP.parsePacket() > 0)
    {
      UDP.read(rv_data , 4);
      Serial.print("Recieve : ");
      Serial.println(rv_data);
      UDP.flush();
      Serial.println(String(rv_data).toInt());

      // PWM出力関係
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
    }
  // rv_data_st = String(rv_data);
  // test = rv_data_st.toInt();
  
}
