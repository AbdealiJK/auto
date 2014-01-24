/*   VCNL4000 Breakout ---------------- Arduino
        3.3V  -----------------------  3.3V
        GND  ------------------------  GND
        SCL  ------------------------  A5
        SDA  ------------------------  A4
        IR+  ------------------------  5V (3.3V is fine too)
  
  Values for distance :
  >> nothing - 3214
  >> top - 3157
  >> middle - 3370
  >> bottom - 

 */
#include <Wire.h>

#define VCNL4000_ADDRESS 0x13  // 0x26 write, 0x27 read

// VCNL4000 Register Map
#define COMMAND_0 0x80  // starts measurments, relays data ready info
#define PRODUCT_ID 0x81  // product ID/revision ID, should read 0x11
#define IR_CURRENT 0x83  // sets IR current in steps of 10mA 0-200mA
#define AMBIENT_PARAMETER 0x84  // Configures ambient light measures
#define AMBIENT_RESULT_MSB 0x85  // high byte of ambient light measure
#define AMBIENT_RESULT_LSB 0x86  // low byte of ambient light measure
#define PROXIMITY_RESULT_MSB 0x87  // High byte of proximity measure
#define PROXIMITY_RESULT_LSB 0x88  // low byte of proximity measure
#define PROXIMITY_FREQ 0x89  // Proximity IR test signal freq, 0-3
#define PROXIMITY_MOD 0x8A  // proximity modulator timing


void setup_vcnl()
{
  Wire.begin();  // initialize I2C stuff

  /* Test that the device is working correctly */
  byte temp = readByte(PRODUCT_ID);
  if (temp != 0x11)  // Product ID Should be 0x11
  {
    PC.print("Something's wrong. Not reading correct ID: 0x");
    PC.println(temp, HEX);
  }
  else
    PC.println("VNCL4000 Online...");

  /* Now some VNCL400 initialization stuff
     Feel free to play with any of these values, but check the datasheet first!*/
  writeByte(AMBIENT_PARAMETER, 0x0F);  // Single conversion mode, 128 averages
  writeByte(IR_CURRENT, 20);  // Set IR current to 200mA
  writeByte(PROXIMITY_FREQ, 2);  // 781.25 kHz
  writeByte(PROXIMITY_MOD, 0x81);  // 129, recommended by Vishay
}

void update_avs() {
  int lim = 10;
  int n = lim;
  unsigned int proximityValue = 0;
  while(n--) {
    unsigned int temp = readProximity();
    proximityValue += temp;
  }
  proximityValue /= lim;
  avs_value = proximityValue;
  Serial.println(avs_value);
}

// readProximity() returns a 16-bit value from the VCNL4000's proximity data registers
unsigned int readProximity() {
  unsigned int data;
  byte temp;
  
  temp = readByte(COMMAND_0);
  writeByte(COMMAND_0, temp | 0x08);  // command the sensor to perform a proximity measure
  
  //while(!(readByte(COMMAND_0)&0x20)) 
  //  ;  // Wait for the proximity data ready bit to be set
  delayMicroseconds(700);
  data = readByte(PROXIMITY_RESULT_MSB) << 8;
  data |= readByte(PROXIMITY_RESULT_LSB);
  
  return data;
}

// writeByte(address, data) writes a single byte of data to address
void writeByte(byte address, byte data) {
  Wire.beginTransmission(VCNL4000_ADDRESS);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

// readByte(address) reads a single byte of data from address
byte readByte(byte address) {
  byte data;
  
  Wire.beginTransmission(VCNL4000_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(VCNL4000_ADDRESS, 1);
//  while(!Wire.available())
//    ;
  delayMicroseconds(700);
  data = Wire.read();

  return data;
}
