#include <Arduino.h>
//khai báo thư viện để kết nối wifi cho esp32 webserver
#include <WiFi.h>
#include<DHT.h>
#include<HTTPClient.h>
#include<string.h>
#define DHTTYPE DHT11
//khai báo chân sử dụng led
const int led1 = 26;
const int led2 = 27;
const int DHTPin= 12;
const char *ssid = "Son";
const char *password = "77687768";
//Tạo một web server tại cổng 80 - cổng mặc định cho esp32 webserver
WiFiServer webServer(80);

String led1Status = "OFF";
String led2Status = "OFF";

String header;
DHT dht(DHTPin, DHTTYPE);
String UrlThingspeak = "https://api.thingspeak.com/update?api_key=98J3KWOSVPMSG6F3";
 
String httpGETRequest(const char* Url);
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT11 to Thingspeak!"));
  delay(300);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  // Set outputs to LOW
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  delay(10);
  bool recheck_connect_fail=false;
  Serial.print("Connecting to wifi");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    if(WiFi.status()==WL_CONNECT_FAILED||WiFi.status()==WL_NO_SSID_AVAIL||WiFi.status()>WL_DISCONNECTED)
    {
      recheck_connect_fail=true;
      break;
    }
  }
  if(recheck_connect_fail)
  {
    Serial.println("CONNECTION NETWORK FAILED !!!");
  }
  else{
    Serial.println("SUCCESSED CONNECTION !!!");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  //khởi tạo webserver
  webServer.begin();
}

void loop() {
  WiFiClient webClient = webServer.available(); // nếu có client kết nối với esp32 webserver

  if (webClient)
  {
    //khoi tao gia tri ban dau cho time
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New web Client");
    //biến lưu giá trị response
    String currentLine = "";
    //nếu có client connect và không quá thời gian time out
    while (webClient.connected() && currentTime - previousTime <= timeoutTime)
    {
      //đọc giá trị timer tại thời điểm hiện tại
      currentTime = millis();
      //nếu client còn kết nối
      if (webClient.available())
      {
        //đọc giá trị truyền từ client theo từng byte kiểu char
        delay(1000);
        float T=dht.readTemperature();
        float h=dht.readHumidity();
        if (isnan(h) || isnan(T)) 
        {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
    }
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.println(" %");
    Serial.print(F("Temperature: "));
    Serial.print(T);
    Serial.println(" oC");
    char para[50];
    sprintf(para,"&field1=%6.2f&field2=%6.2f",T,h);
    String Url = UrlThingspeak + String(para);
    httpGETRequest(Url.c_str());
        char information = webClient.read();
        Serial.write(information);
        header += information; // lưu giá trị vào Header
        if (information == '\n') //Nếu đọc được kí tự xuống dòng (hết chuỗi truyền tới)
        {
          if (currentLine.length() == 0)
          {
            //esp32 webserver response
            // HTTP headers luôn luôn bắt đầu với code HTTP (ví d HTTP/1.1 200 OK)
            webClient.println("HTTP/1.1 200 OK");
            webClient.println("Content-type:text/html"); // sau đó là kiểu nội dụng mà client gửi tới, ví dụ này là html
            webClient.println("Connection: close"); // kiểu kết nối ở đây là close. Nghĩa là không giữ kết nối sau khi nhận bản tin
            webClient.println();

            // nếu trong file header có giá trị
            if (header.indexOf("GET /led1/on") >= 0)
            {
              Serial.println("Led1 on");
              led1Status = "on";
              digitalWrite(led1, HIGH);
            }
            else if (header.indexOf("GET /led1/off") >= 0)
            {
              Serial.println("Led1 off");
              led1Status = "off";
              digitalWrite(led1, LOW);
            }
            else if (header.indexOf("GET /led2/on") >= 0)
            {
              Serial.println("Led2 on");
              led2Status = "on";
              digitalWrite(led2, HIGH);
            }
            else if (header.indexOf("GET /led2/off") >= 0)
            {
              Serial.println("Led2 off");
              led2Status = "off";
              digitalWrite(led2, LOW);
            }
            // Response trang HTML của esp32 webserver
            webClient.println("<!DOCTYPE html><html>");
            webClient.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            //thêm font-awesome
            webClient.println("<link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css\">");
            // code CSS cho web
            //css cho toan bo trang
            webClient.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto;color:red;background-color:rgb(240, 240, 128); }");
            //css cho nut nhan
            webClient.println(".button { background-color: #4CAF50; border: none; color: white; position:relative; rigth:500px; padding: 16px 40px;");
            webClient.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            webClient.println(".button2 {background-color: #5e0101; position:relative; rigth:500px; }</style></head>");
            // Web Page Heading H1 with CSS
            webClient.println("<body><h1 style=\"color:Tomato;text-align:center;\">Smart house</h1>");

            // Web Page Heading H2
            webClient.print("<h2 style=\"text-align:left;color: red;\"><u> Link trans to watch temperature and humidity: </u>");
            webClient.println("<a href=\"https://thingspeak.com/channels\">https://thingspeak.com/channels</a></h2>");
            webClient.println("<h3 style=\"color:#077a39; text-align: center;\"><i class=\"fa fa-home\" aria-hidden=\"true\"></i></h3>");


            // Display current state, and ON/OFF buttons for Led1
            webClient.println("<p>Led1 - State " + led1Status + "</p>");
            // If the Led1Status is off, it displays the ON button
            if (led1Status == "off")
            {
              //khởi tạo một nút nhấn có đường dẫn đích là /led1/on
              webClient.println("<p><a href=\"/led1/on\"><button class=\"button\">ON</button></a></p>");
            }
            else
            {
              //khởi tạo một nút nhấn có đường dẫn đích là /led1/off
              webClient.println("<p><a href=\"/led1/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for Led2
            webClient.println("<p>Led2 - State " + led2Status + "</p>");
            // If the led2 is off, it displays the ON button
            if (led2Status == "off")
            {
              //khởi tạo một nút nhấn có đường dẫn đích là /led2/on
              webClient.println("<p><a href=\"/led2/on\"><button class=\"button\">ON</button></a></p>");
            }
            else
            {
              //khởi tạo một nút nhấn có đường dẫn đích là /led2/on
              webClient.println("<p><a href=\"/led2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            webClient.println("</body></html>");

            // The HTTP response ends with another blank line
            webClient.println();
            // Break out of the while loop
            break;
          }
          else
          {
            currentLine = "";
          }
        }
        else if (information != '\r')   //nếu giá trị gửi tới khác xuống duòng
        {
          currentLine += information;     //lưu giá trị vào biến
        }
      }
    }
    // Xoá header để sử dụng cho lần tới
    header = "";
    // ngắt kết nối với client trên esp32 webserver
    webClient.stop();
    Serial.println("Client disconnected.");
    Serial.println("");

  }
}
String httpGETRequest(const char* Url)
{
  HTTPClient http;
  http.begin(Url);
  int responseCode = http.GET();
  String responseBody = "{}";
  if(responseCode > 0)
  {
    Serial.print("responseCode:");
    Serial.println(responseCode);
    responseBody = http.getString();
  }
  else
  {
    Serial.print("Error Code: ");
    Serial.println(responseCode);
  }
  http.end();
  return responseBody;
}