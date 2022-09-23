// BH1750FVI - Version: Latest 
#include <BH1750FVI.h>
#include <WiFiNINA.h>
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

//please enter your sensitive data in the Secret tab
char ssid[] = "kanishk";
char pass[] = "kanishk02";

WiFiClient client;

char   HOST_NAME[] = "maker.ifttt.com";
String queryString = "?value1=57&value2=25";

bool sunlight = false;

void setup() {
  // initialize WiFi connection
  WiFi.begin(ssid, pass);
  LightSensor.begin();
  
  Serial.begin(9600);
  while (!Serial);

  // // connect to web server on port 80:
  // if (client.connect(HOST_NAME, 80)) {
  //   // if connected:
  //   Serial.println("Connected to server");
  // }
  // else {// if not connected:
  //   Serial.println("connection failed");
  // }
}

void sunlight_received() {
  String PATH_NAME   = "/trigger/sunlight_recieved/with/key/_u16eoxBEbN1oPhUmTfyJim3t2PjsjRgzvv57ELsmX"; // change your EVENT-NAME and YOUR-KEY
  
  // make a HTTP request:
    // send HTTP header
    client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); // end HTTP header
   

    while (client.connected()) {
      if (client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }
}

void sunlight_stopped() {
  String PATH_NAME   = "/trigger/sunlight_stopped/with/key/_u16eoxBEbN1oPhUmTfyJim3t2PjsjRgzvv57ELsmX"; // change your EVENT-NAME and YOUR-KEY
  
  // make a HTTP request:
    // send HTTP header
    client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); // end HTTP header


    while (client.connected()) {
      if (client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }
}

void connect() {
  while (!Serial);

  // connect to web server on port 80:
  if (client.connect(HOST_NAME, 80)) {
    // if connected:
    Serial.println("Connected to server");
  }
  else {// if not connected:
    Serial.println("connection failed");
  }
}

void disconnect() {
  client.stop();
  Serial.println();
  Serial.println("disconnected");
}

void loop() {
  int intensity = LightSensor.GetLightIntensity();
  int count = 0;
  
  Serial.println("Light: " + intensity);
//  Serial.println(lux);

  if (intensity < 100 && sunlight == true )
  {
    count++;
    if(count > 5000)
    {
    connect();
    sunlight_stopped();
    disconnect();
    sunlight = false;
    count = 0;
    }
  }
  else if (intensity > 100 && sunlight == false && count > 1000)
  {
    count++;
    if (count > 5000)
    {
    connect();
    sunlight_received();
    disconnect();
    sunlight = true;
    count = 0;
    }
  }
}

// Kanishk Jain
// Task 3.2C SIT210
