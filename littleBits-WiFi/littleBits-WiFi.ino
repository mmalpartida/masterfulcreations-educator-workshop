#include <SPI.h>
#include <RH_NRF24.h>
#include <RadioHead.h>


//#define SCK 10
//#define MISO 13
//#define MOSI A4
//#define CE 11
//#define CSN 10
//#define IRQ 11


//RH_NRF24 nrf24;
// RH_NRF24 nrf24(8, 7); // use this to be electrically compatible with Mirf
RH_NRF24 nrf24(11, 10);// For Leonardo, need explicit SS pin
// RH_NRF24 nrf24(8, 7); // For RFM73 on Anarduino Mini


const int topIn = 0;
const int midIn = A0;
const int botIn = A1;

//CSN -- Yellow  -- A2
//CE -- Orange -- A3
//MOSI -- Green  -- A4
//SCK -- Grey -- 10
//IRQ -- White -- 11
//MISO -- Purple -- 13

const int topOut = 1;
const int midOut = 5;
const int botOut = 9;


void setup() {
  // put your setup code here, to run once:

  //pinMode(SCK, OUTPUT);
  //pinMode(MISO, OUTPUT);
  //pinMode(MOSI, INPUT);
  //pinMode(CE, INPUT);
  //pinMode(CSN, INPUT);
  //pinMode(IRQ, INPUT_PULLUP);


 Serial.begin(9600);

 
  while (!Serial) 
   Serial.println("begin setup");
    ; // wait for serial port to connect. Needed for Leonardo only
    Serial.println("serial avail");
  if (!nrf24.init()){
    Serial.println("init failed");
  }else{
 Serial.println("init succeed");
    
  }
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1)){
    Serial.println("setChannel failed");

  }else{
Serial.println("setChannel succeed");
    
  }
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm)){
    Serial.println("setRF failed");    
  }else{
    Serial.println("setRF succeed");  
  }
}
 
  

void loop() {
  // put your main code here, to run repeatedly:
 //Serial.println("hi");
   if (nrf24.available())
  {
    // Should be a message for us now   
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (nrf24.recv(buf, &len))
    {
//      NRF24::printBuffer("request: ", buf, len);
      Serial.print("got request: ");
      Serial.println((char*)buf);
      
      // Send a reply
      uint8_t data[] = "And hello back to you";
      nrf24.send(data, sizeof(data));
      nrf24.waitPacketSent();
      Serial.println("Sent a reply");
    }
    else
    {
      Serial.println("recv failed");
    }
  }

}
