/////////////////////////////////////////////////////////////
Author : Hariharan Raveenthiran
/////////////////////////////////////////////////////////////


#include <SoftwareSerial.h>
#define RX 2
#define TX 3
String AP = "WIFI NAME";       // AP NAME
String PASS = "WIFI PASSWORD"; // AP PASSWORD
String API = "";   //Your write API KEY from the clould( I have used Thingspeak)
String HOST = "api.thingspeak.com";
String PORT = "80";
String field = "field1";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 

//String data to be sent to cloud
String valSensor;
SoftwareSerial esp8266(RX,TX); 

//Initialize variables for the distances from two ultrasonic sensors
int cm = 0;
int cm1=0;
int check_num=0,check_num1=0;
String Response;

//Function used for getting data from Ultrasonic sensors by passing trigger pin number, and echo pin number
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
} 
  

//Setup of Arduino and Wifi module
void setup() {
  Serial.begin(9600);
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
}


void loop() {
  //Finding distance using the echo wave using the mathematical formula
  cm = 0.01723 * readUltrasonicDistance(8, 9);
  cm1 = 0.01723 * readUltrasonicDistance(12,11);

  //Print the distances to serial monitor
  Serial.print(cm);
  Serial.println(" cm");
  Serial.print(cm1);
  Serial.println(" cm");


  //If distances detected are greater than 100cm, then change the directions according to the conditions.
   if(cm>100){
    check_num=1;
  }
  if(cm1>100){
    check_num1=1;
  }
  if ((check_num==1)&& (check_num1==0)){
    Response="Go right";
  }
  
  if ((check_num==0)&& (check_num1==1)){
    Response="Move forward";
  }
  if ((check_num==1)&& (check_num1==1)){
    Response="Go left";
  }
  delay(100); // Wait for 100 millisecond(s) 

//Send the string data to cloud, and check the connections.
valSensor = Response;
String getData = "GET /update?api_key="+ API +"&"+ field +"="+String(valSensor);
sendCommand("AT+CIPMUX=1",5,"OK");
sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
esp8266.println(getData);delay(1);countTrueCommand++;
sendCommand("AT+CIPCLOSE=0",5,"OK");
}

String Resonse_Data(){
  return ("Hello"); // Replace with your own sensor code
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("Connected");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
