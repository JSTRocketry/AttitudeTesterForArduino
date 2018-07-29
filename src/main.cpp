#include <Arduino.h>

String X_SYNTAX = "X:";
String Y_SYNTAX = "Y:";
String Z_SYNTAX = "Z:";
String ALTITUDE_SYNTAX = "PA:";
int pos = 0;
char convertedData[100];
float xData = -1;
float yData = -1;
float zData = -1;
float altData = -1;
float tsData = -1;
bool compiled = false;
long startTime = 0;

class DataParser {
    int syntaxPosition = 0;
    float parseData(String data){
      int syntax = getSyntax(data);
      switch (syntax) {
        case 0:
          syntaxPosition = data.indexOf(X_SYNTAX+X_SYNTAX.length());
          return data.substring(syntaxPosition).toFloat();
        case 1:
          syntaxPosition = data.indexOf(Y_SYNTAX+Y_SYNTAX.length());
          return data.substring(syntaxPosition).toFloat();
        case 2:
          syntaxPosition = data.indexOf(Z_SYNTAX+Z_SYNTAX.length());
          return data.substring(syntaxPosition).toFloat();
        case 3:
          syntaxPosition = data.indexOf(ALTITUDE_SYNTAX+ALTITUDE_SYNTAX.length());
          return data.substring(syntaxPosition).toFloat();
        default:
          return -1;
      }
    }

    int getSyntax(String data){
      if(data.indexOf(X_SYNTAX) != -1) return 0;
      else if(data.indexOf(Y_SYNTAX) != -1) return 1;
      else if(data.indexOf(Z_SYNTAX) != -1) return 2;
      else if(data.indexOf(ALTITUDE_SYNTAX) != -1) return 3;
      else return -1;
    }

  public:
    DataParser(){}
    void addData(String data){
      int syntax = getSyntax(data);
      switch(syntax){
        case 0:
          xData = parseData(data);
          tsData = millis()-startTime;
          break;
        case 1:
          yData = parseData(data);
          tsData = millis()-startTime;
          break;
        case 2:
          zData = parseData(data);
          tsData = millis()-startTime;
          break;
        case 3:
          altData = parseData(data);
          tsData = millis()-startTime;
        default:
          break;
      }
    }
    void sendData(){
      String toSend = "";
      if(xData != -1 && yData != -1 && zData != -1 && tsData != -1){
        toSend = "@{OX:" + String(xData) + ";OY:" + String(yData) + ";OZ:" + String(zData) + ";TS:" + String(tsData) + ";}@";
        xData, yData, zData, tsData = -1;
      } else if(altData != -1 && tsData != -1){
        toSend = "@{PA:" + String(altData) + ";TS:" + String(tsData) + ";}@";
        altData, tsData = -1;
      }
      if(toSend != "") Serial.println(toSend);
    }
};

DataParser parser;

void setup() {
  Serial.begin(115200);
  startTime = millis();
  parser = DataParser();

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
    convertedData[pos] = recv;
    pos++;
  }
  else if(pos > 0 && !compiled){
    String compiledData = convertedData;
    parser.addData(compiledData);
    compiled = true;
  }
}
