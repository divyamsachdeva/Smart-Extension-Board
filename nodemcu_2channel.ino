#include <ESP8266WiFi.h>
const char* ssid = "Virus";// enter wifi name 
const char* password = "zHi@22tesh";// enter password here

int ledPin1 = 13; //pin D7 of nodemcu
int ledPin2 = 12; //pin D6 of nodemcu
int switch1 = HIGH,switch2 = HIGH;
  
WiFiServer server(80);// connects server to port 80 




 
void setup() 
{
// turning all the switches off initially.
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, switch1);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, switch2);
    //////////////////////////////////////// Connect to WiFi network//////////////////////////////////////////////////////
  Serial.begin(115200);// setting up baud rate of 115200
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);// connecting to the wifi using wifi name and password provided
 
  while (WiFi.status() != WL_CONNECTED) // checks if wifi is connected or not...if conected loop will end
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");//
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////// Start the server/////////////////////////////////////////////////////
  server.begin();
  Serial.println("Server started");
  ////////////////////////////////////////// Print the IP address////////////////////////////////////////////////////
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());// this function "WiFi.localIP()" provides ip address
  Serial.println("/");
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
 
void loop() {
 /////////// Check if a client has connected//////////////////////////////////////////////
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 //////////// Wait until the client sends some data//////////////////////////////////////
  
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  ///////////////////////////////////////////////////////////////////////////////////
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  ////////////////////// Match the request///////////////////////////////////////////
 
  if (request.indexOf("/LED1=ON") != -1)  {
    digitalWrite(ledPin1, LOW);
    switch1 = LOW;
  }
  if (request.indexOf("/LED1=OFF") != -1)  {
    digitalWrite(ledPin1, HIGH);
    switch1 = HIGH;
  }
  if (request.indexOf("/LED2=ON") != -1)  {
    digitalWrite(ledPin2, LOW);
    switch2 = LOW;
  }
  if (request.indexOf("/LED2=OFF") != -1)  {
    digitalWrite(ledPin2, HIGH);
    switch2 = HIGH;
  }
// Set ledPin according to the request
//digitalWrite(ledPin, switch);
 
  // Return the response
//  client.println("HTTP/1.1 200 OK");
//  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  
  client.println("<p align=middle><center><font size =7 color=blue> Button 1: ");
  if(switch1 == LOW) 
  {  client.print("<font color=green>ON </font>");
     client.println("<a href=\"/LED1=OFF\"\"><button><h1> OFF </h1></button></a>");
  }
  if (switch1 == HIGH)
  {  client.print("<font color=green>OFF </font>"); 
     client.println("<a href=\"/LED1=ON\"\"><button><h1> ON </h1></button></a>");
  }
  
  client.println("<br><br>"); 
  client.println(" Button 2: ");
  if(switch2 == LOW) 
  {client.println("<font color=green>ON </font>");
  client.println("<a href=\"/LED2=OFF\"\"><button><h1> OFF </h1></button></a>");  
  } 
  if (switch2 == HIGH)
  {client.println("<font color=green>OFF </font>");
   client.println("<a href=\"/LED2=ON\"\"><button><h1> ON </h1></button></a>");
  }
  client.print("</font></center></p>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
 
