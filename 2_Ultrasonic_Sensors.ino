//######################################################################################################################
//#
//#     Author : Hariharan Raveenthiran 
//#     Testing of two Ultrasonic sensorss for Smart_Direction_Sensor_Setup
//#
//######################################################################################################################


//This is the basic setup of two Ultrasonic sensors setup which predicts the direction that you have to go according to the obstacles detected.
int DISTANCE1 = 0;
int DISTANCE2=0;
int check_num=0,check_num1=0;
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

void setup()
{
  Serial.begin(9600);

}

void loop()
{
  //Find the distance according to the echo wave recieved from each pin.
  DISTANCE1 = 0.01723 * readUltrasonicDistance(8, 9);
  DISTANCE2 = 0.01723 * readUltrasonicDistance(12,11);
  Serial.print(DISTANCE1);
  Serial.println(" cm");
  Serial.print(DISTANCE2);
  Serial.println(" cm");
   if(DISTANCE1>100){
    check_num=1;
  }
  if(DISTANCE2>100){
    check_num1=1;
  }
  if ((check_num==1)&& (check_num1==0)){
    Serial.print("Go right\n");
  }
  
  if ((check_num==0)&& (check_num1==1)){
    Serial.print("Move forward\n");
  }
  if ((check_num==1)&& (check_num1==1)){
    Serial.print("Go left\n");
  }
  delay(100); // Wait for 100 millisecond(s)
}
