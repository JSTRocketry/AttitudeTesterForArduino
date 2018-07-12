#include <Arduino.h>
#define END_LINE "b'\\r\\n'"

String X_SYNTAX = "X:";
String Y_SYNTAX = "Y:";
String Z_SYNTAX = "Z:";
char data[100];
int pos = 0;
float xData = -1;
float yData = -1;
float zData = -1;
float tsData;
bool compiled = false;

void setup() {
  Serial.begin(115200);
  // long startTime = millis();
  // data = Serial.readString();
  // while(Serial.available() > 0){
  //   if(data.indexOf(X_SYNTAX) >= 0){
  //     pos = data.indexOf(X_SYNTAX+X_SYNTAX.length());
  //     xData = data.substring(pos).toFloat();
  //   } else if(data.indexOf(Y_SYNTAX) >= 0){
  //     pos = data.indexOf(Y_SYNTAX+Y_SYNTAX.length());
  //     yData = data.substring(pos).toFloat();
  //   } else if(data.indexOf(Z_SYNTAX) >= 0){
  //     pos = data.indexOf(Z_SYNTAX+Z_SYNTAX.length());
  //     zData = data.substring(pos).toFloat();
  //   }
  //   if(xData != -1 && yData != -1 && zData != -1){
  //     tsData = millis();
  //     data = ("@{OX:%s;OY:%s;OZ:%s;TS:%s;}@", xData, yData, zData, tsData);
  //     Serial.println(data);
  //     xData, yData, zData, tsData = -1;
  //   }
  // }
}

void loop() {
  if(Serial.available() > 0){
    compiled = false;
    int recv = Serial.read();
    data[pos] = recv;
    Serial.println(data[pos]);
    pos++;
  }
  else if(pos > 0 && !compiled){
    String out = data;
    Serial.println(out);
    compiled = true;
  }
}
