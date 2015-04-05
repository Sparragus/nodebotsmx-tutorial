#include <Bridge.h>
#include <Console.h>
#include <HttpClient.h>
#include <Servo.h> 

HttpClient client;

Servo servo;
int servoPin = 9;

float servoPos = 0;
float servoPosGain = 1.00;
float servoPosLoss = 0.25;
float servoPosMin = 0;
float servoPosMax = 180;

int newTweets = 0;

int delayTime = 1000;

void setup() {
  Bridge.begin();
  Console.begin();
  
  servo.attach(servoPin);
  setServoPosition(servo, servoPosMax - servoPos );
}

void loop() {
  client.get("192.168.1.169:3000");
  if (client.available()) {   
      newTweets = client.parseInt();
      
      if ( newTweets == 0 ) {
        servoPos -= servoPosLoss;
      } else {
        servoPos += newTweets*servoPosGain;
      }
      
      servoPos = constrain(servoPos, servoPosMin, servoPosMax);
      setServoPosition(servo, servoPosMax - servoPos);
      
      Console.print("Servo position: " + String(servoPos) + " :: ");
      Console.println("New tweets: " + String(newTweets));
      
  } else {
     Console.println("Request failed. Retrying in " + String(delayTime/1000) + " seconds");
  }
    
  newTweets = 0;
  delay(delayTime);
}

void setServoPosition(Servo &s, float pos) {
  s.write(pos);
  delay(10);
}
