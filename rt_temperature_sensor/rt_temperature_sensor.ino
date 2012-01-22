#include <SPI.h>
#include <Ethernet.h>
#include <WebSocketClient.h>

#define SENSOR0

#ifdef SENSOR0
  #define MAC { 0xAE, 0x3D, 0xB6, 0xEF, 0xFE, 0xE0 }
  #define IP { 10,0,1,69 }
  #define SENSOR_ID 0
#endif

#ifdef SENSOR1
  #define MAC { 0xAC, 0x3D, 0xB6, 0xEF, 0xFE, 0xE1 }
  #define IP { 10,0,1,68 }
  #define SENSOR_ID 1;
#endif

byte mac [] = MAC;
byte ip [] = IP;
int sensor_id = SENSOR_ID;

byte server[] = { 10,0,1,6 }; //socket.io server
byte subnet[] = { 255,255,255,0 }; 
byte gateway[] = { 10,0,1,1 }; 
WebSocketClient client(server, "/socket.io/websocket/", 80);

void setup() {
  Serial.begin(9600);
  
  Ethernet.begin(mac, ip);
  delay(3000);
  if(client.connect()) {
    client.setDataArrivedDelegate(dataArrived);
  }
  else {
    while(1) {}
  }
}

boolean subscribed = false;

void loop() {
  //client.monitor();
  
  if(!subscribed) {
    client.subscribe("tempsensor");
    delay(2000);
    subscribed = true;
  }
  
  // now we send the data packet with the temperature reading
  char _s[8];  
  String message = "{\"room\":\"tempsensor\", ";
  message += "\"sensor\":";
  message += sensor_id;
  message += ", \"value\":";
  message += dtostrf(get_temp(0), 8, 3, _s);
  message += "}";

  client.send(message);
  delay(100);
}

void dataArrived(WebSocketClient client, String data) {
  Serial.println("Data Arrived: " + data);
}


float get_temp(int pin) {
  // gets the temperature from the sensor

  // eg 626 ADC value
  // adc val / 1024 (range) gives % of range.  (eg 626/1024 = 0.611)
  // multiply by 5 (which is the voltage range - so % of 5v being provided) is no V measured (eg: 0.611 x 5 = 3.06V)
  // multiply by 1000 to get value as mV measured (eg: 3.06 * 1000 = 3056.6mV)
  // divide by 10 as it's 10mV / K linear. (eg: 3056.5/10 = 305.6K)
  // formula K = (adc / 1024) * 5 * 1000 / 10
  // simplify K = (adc / 1024) * 500
  // C = K - 273
  
  float raw = analogRead(pin);
  float kelvin = (raw / 1024) * 500; 
  float celcius = kelvin - 273;
  return (celcius);
}
