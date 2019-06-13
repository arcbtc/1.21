#include <WiFiClientSecure.h>

#include <ArduinoJson.h> //Most current version can be used
#include <GxEPD2_BW.h>
#include <qrcode.h>
#include <string.h>

#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
GxEPD2_BW<GxEPD2_154, GxEPD2_154::HEIGHT> display(GxEPD2_154(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));

char wifiSSID[] = "WIFINAME";
char wifiPASS[] = "PASSWORD";

const char* host = "api.opennode.co";
const int httpsPort = 443;
String amount = "400";
String apikey = "OPENNODE-API-KEY"; 
String description = "Sweets"; //invoice description
String hints = "false"; 

String data_lightning_invoice_payreq = "";
String data_status = "unpaid";
String data_id = "";
int counta = 0;

//Set other Arduino Strings used
String setoffour = "";
String right = "";
String third = "";
String fourth = "";
String tempfourhex = "";
String line = "";
String line2 = "";
String doublelines = "";
String finalhex = "";
String hexvalues = "";
String result = "";
String PAYMENT = ""; 
String PAYMENTPAID = "true"; 
String response;

//Buffers for Arduino String conversions
char fourbuf[5];
char fourbuff[5];
int tamp = 0;

//Char for holding the QR byte array
unsigned char PROGMEM singlehex[4209];

//Char dictionary for conversion from 1s and 0s
char ref[2][16][5]={
{"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"},
{"0",   "1",   "2",   "3",   "4",   "5",   "6",   "7",   "8",   "9",   "a",   "b",   "c",   "d",   "e",   "f"}
};

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

}

void loop() {
  
int counta = 0;

hexvalues = "";

fetchpayment();

  qrmmaker(data_lightning_invoice_payreq);

     for (int i = 0;  i < line.length(); i+=4){      
        int tmp = i; 
        setoffour = line.substring(tmp, tmp+4); 
       
             for (int z = 0; z < 16; z++){
               if (setoffour == ref[0][z]){
                hexvalues += ref[1][z];
               }
             }
      }

  line = "";

//for loop to build the epaper friendly char singlehex byte array image of the QR
  for (int i = 0;  i < 4209; i++){
     int tmp = i;   
     int pmt = tmp*2; 
     result = "0x" + hexvalues.substring(pmt, pmt+2) + ",";
     singlehex[tmp] = (unsigned char)strtol(hexvalues.substring(pmt, pmt+2).c_str(), NULL, 16);
  }


  display.firstPage();
  do
  {
  display.fillScreen(GxEPD_WHITE);
  display.drawBitmap( 7, 7, singlehex, 184, 183, GxEPD_BLACK); 
  
  }
  while (display.nextPage());{
  }

 
  checkpayment(data_id);
 while (counta < 30){
  if (data_status == "unpaid"){
    delay(1000);
   checkpayment(data_id);
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
  display.println("  ONLY");
  display.println(" 400SATS!");
  display.setFont(&FreeSansBold9pt7b);
  display.println(" Press button for QR");

  }
  while (display.nextPage());{
  }
  
  esp_deep_sleep_start();
}


// QR maker function
void qrmmaker(String xxx){

int str_len = xxx.length() + 1; 
char xxxx[str_len];
xxx.toCharArray(xxxx, str_len);

Serial.println(xxxx);

    QRCode qrcode;
    uint8_t qrcodeData[qrcode_getBufferSize(11)];
    qrcode_initText(&qrcode, qrcodeData, 11, 0, xxxx);

    int une = 0;
    
    line = "";

    for (uint8_t y = 0; y < qrcode.size; y++) {

        // Each horizontal module
        for (uint8_t x = 0; x < qrcode.size; x++) {
          line += (qrcode_getModule(&qrcode, x, y) ? "111": "000");
        }
        line += "1";
        for (uint8_t x = 0; x < qrcode.size; x++) {
          line += (qrcode_getModule(&qrcode, x, y) ? "111": "000");
        }
        line += "1";
        for (uint8_t x = 0; x < qrcode.size; x++) {
          line += (qrcode_getModule(&qrcode, x, y) ? "111": "000");
        }
        line += "1";    
    }
}
