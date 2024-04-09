#include <SPI.h>
#include <RH_NRF24.h>
RH_NRF24 nrf24;
void setup()
{
  Serial.begin(9600);
  
  while(!Serial);
  if (!nrf24.init());
  Serial.println("initnfaild");
  if(!nrf24.setChannel(1))
  Serial.println("setChannal faild");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
  Serial.println ("setRF failed");
}
void loop()
{
  Serial.println("Sending to nrf24_server");
  uint8_t data[]="nada";
  nrf24.send(data,sizeof(data));
  nrf24.waitPacketSent();
  delay(1000);
}
