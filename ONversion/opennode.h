
void fetchpayment(){

  WiFiClientSecure client;

  if (!client.connect(host, httpsPort)) {
    return;
  }

  String topost = "{  \"amount\": \""+ amount  +"\", \"description\": \""+ description  +"\", \"route_hints\": \""+ hints  +"\"}";
  String url = "/v1/charges";

   client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "User-Agent: ESP32\r\n" +
                 "Authorization: " + apikey + "\r\n" +
                 "Content-Type: application/json\r\n" +
                 "Connection: close\r\n" +
                 "Content-Length: " + topost.length() + "\r\n" +
                 "\r\n" + 
                 topost + "\n");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {

      break;
    }
  }
  String line = client.readStringUntil('\n');
  Serial.println(line);
    const size_t capacity = 169*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(168) + 3800;
    DynamicJsonDocument doc(capacity);

    deserializeJson(doc, line);

    String data_idd = doc["data"]["id"]; 
    data_id = data_idd;
    String data_lightning_invoice_payreqq = doc["data"]["lightning_invoice"]["payreq"];
    data_lightning_invoice_payreq = data_lightning_invoice_payreqq;
}




void checkpayment(String PAYID){

  WiFiClientSecure client;

  if (!client.connect(host, httpsPort)) {

    return;
  }

  String url = "/v1/charge/" + PAYID;


  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Authorization: " + apikey + "\r\n" +
               "User-Agent: ESP32\r\n" +
               "Connection: close\r\n\r\n");


  while (client.connected()) {

    
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }
  String line = client.readStringUntil('\n');


  
const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(14) + 650;
 DynamicJsonDocument doc(capacity);

    deserializeJson(doc, line);

String data_statuss = doc["data"]["status"]; 
data_status = data_statuss;
Serial.println(data_status);

}
