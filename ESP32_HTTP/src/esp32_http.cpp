#include <Arduino.h>
#include<HTTPClient.h>
#include<WiFi.h>
#include<ArduinoJson.h>
#include<string.h>

const char *ssid="Son";
const char *password="77687768";

String WeatherApiKey="c643582546692a2bcb99ce7bf4de3ab7";
String city="Hanoi";
String countrycode="";
String weatherJsonBuffer;

// http config
String weatherUrl="http://api.openweathermap.org/data/2.5/weather?q=Hanoi&amp;amp;appid=c643582546692a2bcb99ce7bf4de3ab7"; 

int temp=30;
int humi=80;

String httpGETRequest(const char *Url);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  Serial.println("connecting");
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi network with IP Adress: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(weatherUrl);
  weatherJsonBuffer=httpGETRequest(weatherUrl.c_str());
  Serial.println(weatherJsonBuffer);

  JsonVariantConst weatherJson = JSON.praisee(weatherJsonBuffer);//
  if(JSON.typeof_(weatherJson)=="undefined")//
  {
    Serial.println("Parsing fail");
    return;
  }
  Serial.println();
  temp=weatherJson["main"]["temp"];//
  temp=temp-273;
  Serial.print("Temperature: ");
  Serial.println(temp);
  humi=weatherJson["main"]["humi"];//
  Serial.print("Humidity: ");
  Serial.println(humi);
  delay(1000);

}
String httpGETRequest(const char *Url)
{
  HTTPClient http;//
  http.begin(Url);//
  int responseCode=http.GET();//
  String responseBody="{}";
  if(responseCode>0)
  {
    Serial.print("responseCode");
    Serial.println(responseCode);
    responseBody=http.getString();
  }
  else{
    Serial.print("Error Code: ");
    Serial.println(responseCode);
  }
  http.end();//
  return responseBody;

}