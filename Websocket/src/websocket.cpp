#include <Arduino.h>
#include<WiFi.h>
#include<AsyncTCP.h>
#include<ESPAsyncWebServer.h>

const char *ssid="Son";
const char *password="77687768";

bool led1State=0;
bool led2State=0;
const int led1Pin=26;
const int led2Pin=27;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char index_html[] PROGMEM= R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Websocket Web Server Websocket</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:, ">
<title>ESP Web Server </title>
<meta name="viewport" content="width=device-width , initial-scale=1">
<link rel="icon" href="data:, ">
<style>
  html{
    font-family: Arial,Helvetica,sans-serif;
    text-align: center;
  }
  h1{
    font-size: 1.8rem;
    color: white;
  }
  h2{
    font-size:1.5rem;
    font-weight: bold;
    color: #03630e;
  }
  var gateway = `ws://${window.location.hostname}/ws`;
</head>
<body>
  <div class="topnav">
  <h1>ESP WebSocket Server</h1>
  </div>
  <div class="content">
    <div class="card">
      <h2>Khue Nguyen Creator</h2>
      <p class="state1">LED1: <span id="state1">%STATE1%</span></p>
      <p><button id="button1" class="button1">BUTTON1</button></p>
       <p class="state1">LED2: <span id="state2">%STATE2%</span></p>
      <p><button id="button2" class="button2">BUTTON2</button></p>
    </div>
  </div>
</body>
</html>
)rawliteral";

void notifyClient()
{
  ws.textAll(String(led1State)+String(led2State));
}

/*Xử lý message của client, 
nếu có lệnh toggle1 và toggle 2 sẽ đảo trạng thái led và dùng 
notifyClients để gửi về client trạng thái led.*/

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) 
{
  AwsFrameInfo *info=(AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if(strcmp((char *)data,"toggle1")==0)
    {
      led1State=!led1State;
      notifyClient();
    }
    if(strcmp((char *)data,"toggle2")==0)
    {
      led2State=!led2State;
      notifyClient();
    }
  }
}
// Hàm onEvent để xử lý các sự kiện khi kết nối websocket
void onEvent(AsyncWebSocket *server,AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type)
  {
  case WS_EVT_CONNECT:
    /* code */
    Serial.printf("WebSocket client #%u connected from %s\n",client->id(), client->remoteIP().toString().c_str());
    break;
  case WS_EVT_DISCONNECT:
    Serial.printf("WebSocket client #%u disconnected \n",client->id());
    break;
  case WS_EVT_DATA:
    handleWebSocketMessage(arg,data,len);
    break;
  case WS_EVT_PONG:
  case WS_EVT_ERROR:
    break;
  }
}
//Hàm initWebSocket để khởi tạo
void initWebSocket() //trả về giá trị của led và gửi về các client
{
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

//Hàm processor để sửa giá trị của STATES1 và STATES 2 trên web
String processor(const String& var){
  Serial.println(var);
  if(var=="STATE1")
  {
    if(led1State)
    {
      return "ON";
    }
    else
    {
      return "OFF";}
  }
  if(var=="STATE2")
  {
    if(led2State)
    {
      return "ON";
    }
    else{
      return "OFF";
    }
  }
}

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led1Pin,OUTPUT);
  digitalWrite(led1Pin,LOW);
  pinMode(led2Pin,OUTPUT);
  digitalWrite(led2Pin,LOW);
  // connect to WiFi
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi... ");
  }
  Serial.println(WiFi.localIP());
  initWebSocket();
  // Route for root/web page
    // khởi tạo webserver websocket. Sử dụng trang index_html đã code bên trên và hàm processer để xử lý dữ liệu
  server.on("/",HTTP_GET,[](AsyncWebServerRequest *request){
    request->send_P(200,"text/html",index_html,processor);
  });
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  ws.cleanupClients();
  digitalWrite(led1Pin,led1State);
  digitalWrite(led2Pin,led2State);
}



