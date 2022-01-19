//Viral Science
// www.youtube.com/c/viralscience
//Google Assistant Home Automation
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <TimeLib.h>

#define GND 2
#define VCC 5
#define DATA 10

#define WLAN_SSID       "Not so fast..."             // Your SSID
#define WLAN_PASS       "TeApAmOnDiAlA2020#"        // Your password

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com" //Adafruit Server
#define AIO_SERVERPORT  1883                   
#define AIO_USERNAME    "DavidCop"            // Username
#define AIO_KEY         "aio_Selm30Gb4hBqOYhrbmpCjsGlb7Wf"   // Auth Key

const char* ssid     = "Not so fast...";
const char* password = "TeApAmOnDiAlA2020#";


boolean recordedSignalDOWN[] = {LOW,LOW,HIGH,LOW,LOW,LOW,HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,LOW};
boolean recordedSignalUP[] =   {LOW,LOW,HIGH,LOW,LOW,LOW,HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,HIGH,LOW};
boolean toStopUp = false;
boolean toStopDown = false;


int ok = 0;
int ok2 = 0;

int previousSlideAmount = 0;
int delaySlider = 0;

unsigned long startUpTime = 0;
unsigned long startDownTime = 0;



String lastPress = " ";
String output5State = "Press a button";
String output4State = "off";

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

unsigned long time_now = 0;

//WIFI CLIENT
WiFiClient client;
WiFiServer server(80);

String header;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe WindowDownState = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/WindowDown"); // Feeds name should be same everywhere

Adafruit_MQTT_Subscribe WindowUpState = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/WindowUp"); // Feeds name should be same everywhere

Adafruit_MQTT_Subscribe WindowDownState20 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/WindowDown20"); // Feeds name should be same everywhere

Adafruit_MQTT_Subscribe WindowUpState20 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/WindowUp20"); // Feeds name should be same everywhere

Adafruit_MQTT_Subscribe WindowSliderState = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/WindowSlider"); // Feeds name should be same everywhere


void MQTT_connect();

void setup() {
  Serial.begin(115200);

  pinMode(DATA,OUTPUT);

  
  // Connect to WiFi access point.
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());

  Serial.println(hour());
  Serial.println(startUpTime);
 
  mqtt.subscribe(&WindowDownState);
  mqtt.subscribe(&WindowDownState20);
  mqtt.subscribe(&WindowUpState);
  mqtt.subscribe(&WindowUpState20);
  mqtt.subscribe(&WindowSliderState);
  server.begin();

}

void sendSignal(boolean signal){

if(signal == HIGH){

  digitalWrite(DATA, HIGH);
  delayMicroseconds(2000);
  digitalWrite(DATA,LOW);
  delayMicroseconds(210);

}else{

  digitalWrite(DATA, HIGH);
  delayMicroseconds(370);
  digitalWrite(DATA, LOW);
  delayMicroseconds(2000);
}
  
}

void windowUp(){

              
              if(ok ==0){
                
                  digitalWrite(DATA, HIGH);
                  delayMicroseconds(14600);
                  digitalWrite(DATA, LOW);
                  delayMicroseconds(9200);
                  ok++;

              }

       for(int j = 0; j< 10; j++){
        
              for(int i = 0; i<sizeof(recordedSignalUP); i++){
                
                  sendSignal(recordedSignalUP[i]);
                  Serial.println("going up");
    
              }

              delayMicroseconds(16000);

              
              }

               ok2=0;
               
}

void windowDown(){
   
              
              if(ok2 == 0){
                
                  digitalWrite(DATA, HIGH);
                  delayMicroseconds(14600);
                  digitalWrite(DATA, LOW);
                  delayMicroseconds(9200);
                  ok2++;

              }

        for(int k = 0 ; k<15 ; k++){
          
              for(int i = 0; i<sizeof(recordedSignalDOWN); i++){
                
                  sendSignal(recordedSignalDOWN[i]);
                  Serial.println("going down");
    
              }

              delayMicroseconds(16000);

              }

                ok = 0;
                
}

void windowDown50(){
   
              
              if(ok2 == 0){
                
                  digitalWrite(DATA, HIGH);
                  delayMicroseconds(14600);
                  digitalWrite(DATA, LOW);
                  delayMicroseconds(9200);
                  ok2++;

              }

        for(int k = 0 ; k<30 ; k++){
          
              for(int i = 0; i<sizeof(recordedSignalDOWN); i++){
                
                  sendSignal(recordedSignalDOWN[i]);
                  Serial.println("going down");
    
              }

              delayMicroseconds(16000);

              }

                ok = 0;
                
}

void loop() {
 
  MQTT_connect();
  
  
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) {
    
    if (subscription == &WindowUpState) {
      
      Serial.print(F("Got: "));
      Serial.println((char *)WindowUpState.lastread);
      int Window_state = atoi((char *)WindowUpState.lastread);
      digitalWrite(DATA, LOW);
      
      if((Window_state == 1)){

            windowUp();
        
      }
      
    }

    if (subscription == &WindowDownState){

      Serial.print(F("Got: "));
      Serial.println((char *)WindowDownState.lastread);
      int Window_stateDown = atoi((char *)WindowDownState.lastread);
      digitalWrite(DATA, LOW);

      if(Window_stateDown == 1){

          windowDown();
      }
      
    }

    if (subscription == &WindowUpState20){

      Serial.print(F("Got: "));
      Serial.println((char *)WindowUpState20.lastread);
      int Window_stateUp20 = atoi((char *)WindowUpState20.lastread);
      digitalWrite(DATA, LOW);

      if(Window_stateUp20 == 1){

        windowUp();
        delay(14000);
        windowDown();
        
      }

      
    }

    if (subscription == &WindowDownState20){

      Serial.print(F("Got: "));
      Serial.println((char *)WindowDownState20.lastread);
      int Window_stateDown20 = atoi((char *)WindowDownState20.lastread);
      digitalWrite(DATA, LOW);

      if(Window_stateDown20 == 1){

          windowDown50();
          delay(9000);
          windowUp();
      }
      
    }

    if (subscription == &WindowDownState20){

      Serial.print(F("Got: "));
      Serial.println((char *)WindowDownState20.lastread);
      int Window_stateDown20 = atoi((char *)WindowDownState20.lastread);
      digitalWrite(DATA, LOW);

      if(Window_stateDown20 == 1){

          windowDown50();
          delay(9000);
          windowUp();
      }
      
    }

    if (subscription == &WindowSliderState){

      Serial.print(F("Got: "));
      Serial.println((char *)WindowSliderState.lastread);
      int Window_stateSlider = atoi((char *)WindowSliderState.lastread);
      digitalWrite(DATA, LOW);

      if(previousSlideAmount - Window_stateSlider < 0){

            int windowStop = 0;
            
            windowDown();
            delaySlider = (abs(previousSlideAmount - Window_stateSlider) * 23200)/100;
            Serial.println(delaySlider);
            delay(delaySlider);
            windowUp();
            previousSlideAmount = Window_stateSlider;    
                 
      }

      if(previousSlideAmount - Window_stateSlider > 0){

            int windowStop = 0;
            
            windowUp();
            delaySlider = (abs(previousSlideAmount - Window_stateSlider) * 23200)/100;
            Serial.println(delaySlider);
            delay(delaySlider);
            windowDown();

            previousSlideAmount = Window_stateSlider; 
      }
      
    }
    
  }

  WiFiClient client = server.available();   // Listen for incoming clients
  
}

void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000); 
    retries--;
    if (retries == 0) {
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
  
}
