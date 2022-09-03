// Program for publishing wheel encoder values

//#define USE_USBCON

#include <ros.h>
#include <std_msgs/Int32.h>
#include <Arduino.h>

int encLA = 2;
int encLB = 3;
int encRA = 4;
int encRB = 5;

ros::NodeHandle nh;

std_msgs::Int32 encLMsg;
std_msgs::Int32 encRMsg;

ros::Publisher EncLVal("EncLVal", &encLMsg);
ros::Publisher EncRVal("EncRVal", &encRMsg);

int encLVal = 0;
int encRVal = 0;

int encLALast = LOW;
int encRALast = LOW;
int encLAPres = LOW;
int encRAPres = LOW;

long freq = 0;

void setup() {
  nh.initNode();
  nh.advertise(EncLVal);
  nh.advertise(EncRVal);

  pinMode(encLA, INPUT);
  pinMode(encLB, INPUT);
  pinMode(encRA, INPUT);
  pinMode(encRB, INPUT);

  Serial.begin(57600);

}


void loop() {

//  if (millis() > freq)
//  {
    encLAPres = digitalRead(encLA);
    encRAPres = digitalRead(encRA);

    if (encLALast == LOW && encLAPres == HIGH) {
      if (digitalRead(encLB) == HIGH)
        encLVal++;
      else
        encLVal--;

      if (encLVal > 32768)
        encLVal = -32768;
      if (encLVal < -32768)
        encLVal = 32768;
    }

    if (encRALast == LOW && encRAPres == HIGH) {
      if (digitalRead(encRB) == HIGH)
        encRVal++;
      else
        encRVal--;

      if (encRVal > 32768)
        encRVal = -32768;
      if (encRVal < -32768)
        encRVal = 32768;
    }

    encLMsg.data = encLVal;
    encRMsg.data = encRVal;

    EncLVal.publish(&encLMsg);
    EncRVal.publish(&encRMsg);

    encLALast = encLAPres;
    encRALast = encRAPres;

//    freq = millis() + 50;
//  }
  
  nh.spinOnce();

}
