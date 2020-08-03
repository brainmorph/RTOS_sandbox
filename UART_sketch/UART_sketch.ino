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

unsigned int counter = 65500;
void loop() {
  // put your main code here, to run repeatedly:

  /* Send to STM32 */
  //mySerial.print(counter);

  /* !!NOTE!! : The documentation on Serial.write(var) function makes it seem like if var is bigger than 1 byte 
   *  that the system will serialize the bytes and send them out sequentially.  This is NOT AT ALL what happens.
   *  Thorough reading the documentation reveals that this only happens for "string" type objects.  That being said,
   *  we need to send out 1 byte at a time (lower bits and higher bits) if 'var' is larger than 1 byte data type.
   */
  
  byte numWritten = mySerial.write(counter);  // send low byte
  Serial.print("Sent LOW byte: ");
  Serial.println(numWritten);
  
  mySerial.write(counter >> 8);    // send high byte
  Serial.print("Sent HIGH byte: ");
  Serial.println(numWritten);
    
  /* Send to Arduino serial monitor */
  Serial.print(counter);
  Serial.print("\r\n");
  
  counter += 1;

  delay(300);
  
//  if (mySerial.available())
//    Serial.write(mySerial.read());
//  if (Serial.available())
//    mySerial.write(Serial.read());

}
