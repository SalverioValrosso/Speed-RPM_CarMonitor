// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// loovee, 2014-6-13


#include <SPI.h>
#include "mcp_can.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <stdlib.h>
long strtol (const char *__nptr, char **__endptr, int __base);

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address


// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10

void lcdWriter(String text, int l, int r) {

  lcd.setCursor(l, r);
  lcd.print(text);
}
void lcdWriters(int text, int l, int r) {

  lcd.setCursor(l, r);
  lcd.print(text);
  delay(10);
  lcd.clear();
}

const int SPI_CS_PIN = 9;
MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin


void setup()
{
  lcd.begin(20, 4);
  Serial.begin(115200);

  while (CAN_OK != CAN.begin(CAN_500KBPS))              // init can bus : baudrate = 500k
  {
    Serial.println("CAN BUS Shield init fail");
    Serial.println(" Init CAN BUS Shield again");
    delay(100);
  }
  Serial.println("CAN BUS Shield init ok!");
}


void loop()
{
  unsigned char len = 0;
  unsigned char buf[8];
  int rpmnum;
float myspeed;
  if (CAN_MSGAVAIL == CAN.checkReceive())           // check if data coming
  {
    CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

    unsigned int canId = CAN.getCanId();
    unsigned int newid, lastid;
    //Serial.print("ve mo ve");
    
    //newid=lastid;

   
      if (canId == 781) {
       //if (buf[0] ==0 & buf[1]==0){
     //  Serial.println("-----------------------------");
      //   Serial.println(canId, DEC);
        //Serial.print("Get data from ID: ");

       // for (int i = 0; i < len; i++) // print the data
       // {
       //   Serial.print(buf[i],DEC);
        //  Serial.print("\t");
       // }
Serial.println();
      //  rpmnum = (buf[0] * 256) + buf[1];
        //rpmnum = rpmnum /8;
myspeed=(buf[0] * 256) + buf[1];
myspeed=myspeed/100.0;

          Serial.println(myspeed);
        lcdWriter("Rpm", 1, 1);
        lcdWriters(rpmnum, 2, 2);


      //}
       }
    }
  
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
