#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  // put your setup code here, to run once:
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(38400);
  mySerial.println("Hello, world?");
}

byte counter = 0;
void loop() {
  // put your main code here, to run repeatedly:

  /* Send to STM32 */
  //mySerial.print(counter);
  mySerial.write(counter);
    
  /* Send to Arduino serial monitor */
  Serial.print(counter);
  Serial.print("\r\n");
  
  counter += 1;

  delay(5000);
  
//  if (mySerial.available())
//    Serial.write(mySerial.read());
//  if (Serial.available())
//    mySerial.write(Serial.read());

}
