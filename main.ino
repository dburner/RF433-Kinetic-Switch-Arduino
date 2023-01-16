#include <Arduino.h>

uint8_t msg[24] = { 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0 };

#define HIGH_PULSE 0x8  // 4-bit pulse sequence representing a logical 1 - 1000
#define LOW_PULSE 0xE   // 4-bit pulse sequence representing a logical 0 - 1110
#define BIT_LEN 32     // length of individual bit pulses

#define SEQ_LEN 25      // total number of bits in sequence
#define SEQ_RPT 4       // number of times to repeat full sequence (requires a minimum of 3 to register)
#define SEQ_PAUSE 1000  // time in microseconds to pause between repeated sequences

#define CMD_LEN 8       // total number of bits in command
#define CMD_ON 0x55     // on command sequence
#define CMD_OFF 0x57    // sequence for off command


#define TX_PIN 2        // physical pin to which 433MHz module is connected

void sendBit(bool bit)
{
    digitalWrite(TX_PIN, bit);                     // set pin state based on pulse bit
    delayMicroseconds(BIT_LEN);                    // hold pin state for the bit length time
    digitalWrite(TX_PIN, LOW);                     // pull pin low once bit sent
}

/* send 4-bit pulse sequence representing logical 1 or 0 */
void send_pulse(bool state) {
  uint8_t pulse = state ? HIGH_PULSE : LOW_PULSE;  // determine pulse sequence based on state

  for (uint8_t j = 4; j > 0; j--) {
    bool bit = pulse >> (j - 1) & 1;               // extract individual bits from pulse from most to least significant bit
    digitalWrite(TX_PIN, bit);                     // set pin state based on pulse bit
    delayMicroseconds(BIT_LEN);                    // hold pin state for the bit length time
    digitalWrite(TX_PIN, LOW);                     // pull pin low once bit sent
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void send_commmand()
{
  for (uint8_t x = 0; x < SEQ_RPT; x++) 
  {   
      sendBit(1);
      delayMicroseconds(1000);  
      
      for(uint8_t i = 0; i < 24; i++)
      {
        send_pulse(msg[i] & 1);
      }

      sendBit(1);
      delayMicroseconds(SEQ_PAUSE);    
  }
}

void loop() {
  Serial.println("Sending command");
  send_commmand();

  Serial.println("delay");
  delay(3000);
}
