#include <Arduino.h>
#include<WiFi.h>
#define WIFI_CONNECTION_TIMEOUT 15
const char *ssid="Son";
const char *password="77687768";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password); // lệnh bắt đầu ghép nối wifi với 2 thông số ssid và password
  int loop=0;
  bool recheck_connect_fail=false; // biến kiểm tra kết nối của wifi có thất bại không
  while(WiFi.status()!= WL_CONNECTED) // WiFi.status(): trạng thái của kết nối wifi
  {
    delay(500);
    Serial.print(".");
    loop++;
    if((WiFi.status()==WL_NO_SSID_AVAIL) ||(WiFi.status()==WL_CONNECT_FAILED)|| (WiFi.status()>WL_DISCONNECTED) )
    {
      // WL_NO_SSID_AVAIL: kiểm tra có mã SSID phù hợp không
      // WL_CONNECT_FAILED: kiểm tra kết nối có bị lỗi không
      // WL_DISCONNECTED: kiểm tra có bị mất kết nối không
      recheck_connect_fail=true; // nếu có thì biến báo lỗi sẽ nhận true
      break;
    }
    else
    {
      if(loop>(WIFI_CONNECTION_TIMEOUT))
      {
        recheck_connect_fail=true;
        break;
      }
    }
  }
  if(recheck_connect_fail)// kiểm tra xem biến báo lỗi có đúng hay không
  {
    Serial.println("WiFi network connection failed !!!"); // nếu đúng thì xuất ra dòng báo kết nối thất bại
  }
  else
  {
    Serial.println("Connected to the WiFi network !!!"); // nếu không thì xuất ra dòng đã kết nối
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}