#include <Arduino.h>

uint8_t msg[24] = { 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0 };

#define BIT_LEN 32      // length of individual bit pulses
#define SEQ_RPT 4       // number of times to repeat full sequence (requires a minimum of 3 to register)
#define SEQ_PAUSE 1000  // time in microseconds to pause between repeated sequences

#define TX_PIN 2        // physical pin to which 433MHz module is connected

void sendBit(bool bit)
{
  digitalWrite(TX_PIN, bit);     // set pin state based on pulse bit
  delayMicroseconds(BIT_LEN);    // hold pin state for the bit length time
  digitalWrite(TX_PIN, LOW);     // pull pin low once bit sent
}

void send_pulse2(bool state)
{
  if (state) 
  {
    // 1000
    digitalWrite(TX_PIN, HIGH); 
    delayMicroseconds(BIT_LEN);
    digitalWrite(TX_PIN, LOW); // pull pin low once bit sent
    delayMicroseconds(BIT_LEN * 3);
  }
  else
  {
    // 1110
    digitalWrite(TX_PIN, HIGH); 
    delayMicroseconds(BIT_LEN * 3);
    digitalWrite(TX_PIN, LOW); // pull pin low once bit sent
    delayMicroseconds(BIT_LEN);
  }
}

void send_commmand()
{
  for (uint8_t x = 0; x < SEQ_RPT; x++) 
  {   
      sendBit(1);
      delayMicroseconds(1000);  
      
      for(uint8_t i = 0; i < 24; i++)
      {
        send_pulse2(msg[i] & 1);
      }

      sendBit(1);
      delayMicroseconds(SEQ_PAUSE);    
  }
}