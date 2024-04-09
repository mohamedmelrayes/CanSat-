#include <SPI.h>
#include <RH_NRF24.h>
RH_NRF24 nrf24;
void setup() {
  Serial.begin(9600);
  while(!Serial);
  if(!nrf24.init())
  Serial.println("init failed");
  if(!nrf24.setChannel(1))
  Serial.println("setChannel failed");
  if(!nrf24.setRF(RH_NRF24::DataRate2Mbps,RH_NRF24::TransmitPower0dBm))
  Serial.println("setRF failed");
}

void loop() {
   if (nrf24.available())
  {
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];  
    uint8_t len = sizeof(buf);
    if(nrf24.recv(buf,&len))
    {
      Serial.print("got request: ");
      Serial.println((char*)buf);
    }
    else
    {
      Serial.println("recv failed");
    }
  }

}
