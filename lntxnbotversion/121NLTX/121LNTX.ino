#include <WiFiClientSecure.h>

#include <ArduinoJson.h> //Most current version can be used
#include <GxEPD2_BW.h>
#include <qrcode.h>
#include <string.h>

#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
GxEPD2_BW<GxEPD2_154, GxEPD2_154::HEIGHT> display(GxEPD2_154(/*CS=5*/ SS, /*DC=*/ 22, /*RST=*/ 21, /*BUSY=*/ 4));

char wifiSSID[] = "WIFINAME";
char wifiPASS[] = "PASSWORD";

float price = 1.50; //price per cookie
float satoshis;
int intsats;
float conversion;
String payreq;
String payhash;
bool settle = false;

//LNTXBOT DETAILS
int httpsPort = 443;
const char* lntxbothost = "YOURHOST"; //format like lntxbot.alhur.es
String invoicekey = "YOUR-INVOICE-KEY"; 

void setup() {
display.init(115200);
  display.firstPage();
  do
  {
  display.fillScreen(GxEPD_WHITE);
  display.setFont(&FreeSansBold18pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(0, 80);
  display.println("Loading :)");
  }
  while (display.nextPage());{
  }

  
Serial.begin(115200); 
           
  WiFi.begin(wifiSSID, wifiPASS);   
  while (WiFi.status() != WL_CONNECTED) {
     Serial.println("connecting");
     delay(100);
     }
     
  Serial.println("connected");


  pinMode(27, OUTPUT);

  on_rates();
  satoshis = temp/conversion;
  intsats = (int) round(satoshis*100000000.0);
  
}

void loop() {
  
int counta = 0;

fetchpayment();

  display.firstPage();
  do
  {
  display.fillScreen(GxEPD_WHITE);
    
  qrmmaker(payreq);

  }
  while (display.nextPage());{
  }

  checkpayment();
 while (counta < 30){
  if (settle == false){
    delay(1000);
   checkpayment();
   counta++;
  }
  else{
  digitalWrite(27, HIGH);
  delay(4000);
  digitalWrite(27, LOW);
  delay(500);
  counta = 30;
    }  
  }
  counta = 0;
  
  display.firstPage();
  do
  {
  display.fillScreen(GxEPD_WHITE);
  display.setFont(&FreeSansBold18pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(20, 80);
  display.println("COOKIE");
  display.println(price + "EUR");
  display.setFont(&FreeSansBold9pt7b);
  display.println(" Press button for QR");

  }
  while (display.nextPage());{
  }
  
  esp_deep_sleep_start();
}



//OPENNODE REQUESTS

void on_rates(){
  WiFiClientSecure client;
  if (!client.connect("api.opennode.co", httpsPort)) {
    return;
  }

  String url = "/v1/rates";
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: api.opennode.co\r\n" +
               "User-Agent: ESP32\r\n" +
               "Connection: close\r\n\r\n");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {

      break;
    }
  }
  String line = client.readStringUntil('\n');
    const size_t capacity = 169*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(168) + 3800;
    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, line);
    conversion = doc["data"][on_currency][on_currency.substring(3)]; 

}

////////////////////////// GET/POST REQUESTS///////////////////////////////


void fetchpayment(String nosats){

  WiFiClientSecure client;
  
  if (!client.connect(lntxbothost, httpsPort)) {
    return;
  }
  
  String topost = "{  \"amt\" : \"" + nosats +"\", \"memo\" :\""+ memo + String(random(1,1000)) + "\"}";
  String url = "/addinvoice";
  client.print(String("POST ") + url +" HTTP/1.1\r\n" +
                "Host: " + lntxbothost + "\r\n" +
                "User-Agent: ESP32\r\n" +
                "Authorization: Basic "+ invoicekey +"\r\n" +
                "Content-Type: application/json\r\n" +
                "Connection: close\r\n" +
                "Content-Length: " + topost.length() + "\r\n" +
                "\r\n" + 
                topost + "\n");


  while (client.connected()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
    if (line == "\r") {
      break;
    }
  }
  
  String line = client.readStringUntil('\n');
  Serial.println(line);
  const size_t capacity = JSON_ARRAY_SIZE(32) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(5) + 820;
  DynamicJsonDocument doc(capacity);

  deserializeJson(doc, line);
  const char* pay_req = doc["pay_req"]; 
  const char* payment_hash = doc["payment_hash"]; // "5bf52e3be4d1832bd61eb25770f79a948803fda2af2281ae3037d7b527e7622c"
  payreq = pay_req;
  payhash = payment_hash;
  
}




void checkpayment(){

 WiFiClientSecure client;
  
  if (!client.connect(lntxbothost, httpsPort)) {
    return;
  }
  String url = "/invoicestatus/";
  client.print(String("GET ") + url + payhash +" HTTP/1.1\r\n" +
                "Host: " + lntxbothost + "\r\n" +
                "User-Agent: ESP32\r\n" +
                "Authorization: Basic "+ invoicekey +"\r\n" +
                "Content-Type: application/json\r\n" +
                "Connection: close\r\n\r\n");

  String line = client.readString();
  Serial.println(line);

  if (line == ""){
    settle = false;
  }
  else{
    settle = true;
  }
}



// QR maker function
void qrmmaker(String xxx){
  tft.fillScreen(TFT_WHITE);
  XXX.toUpperCase();
 const char* addr = XXX.c_str();
 Serial.println(addr);
  int qrSize = 12;
  int sizes[17] = { 14, 26, 42, 62, 84, 106, 122, 152, 180, 213, 251, 287, 331, 362, 412, 480, 504 };
  int len = String(addr).length();
  for(int i=0; i<17; i++){
    if(sizes[i] > len){
      qrSize = i+1;
      break;
    }
  }
  QRCode qrcode;
  uint8_t qrcodeData[qrcode_getBufferSize(qrSize)];
  qrcode_initText(&qrcode, qrcodeData, qrSize - 2, ECC_LOW, addr);
  Serial.println(qrSize );
 
  float scale = 2;

  for (uint8_t y = 0; y < qrcode.size; y++) {
    for (uint8_t x = 0; x < qrcode.size; x++) {
      if(qrcode_getModule(&qrcode, x, y)){       
        display.fillRect(15+3+scale*x, 3+scale*y, scale, scale, GxEPD_BLACK);
      }
      else{
        display.fillRect(15+3+scale*x, 3+scale*y, scale, scale, GxEPD_WHITE);
      }
    }
  }
}
