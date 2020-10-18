
#include <SPI.h>

char buf[100];
volatile byte pos;
volatile boolean process_it;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  // turn on SPI in slave mode
  SPCR |= bit(SPE);


  // get ready for an interrupt 
  pos = 0;   // buffer empty
  process_it = false;
}

void loop() {
  Serial.println("ok");
  
  // put your main code here, to run repeatedly:
  
  byte c = SPDR;  // grab byte from SPI Data Register
  
  // add to buffer if room
  if (pos < (sizeof (buf) - 1))
    buf [pos++] = c;
    
  // example: newline means time to process buffer
  if (c == '\n')
    process_it = true;


  if (process_it)
  {
    buf [pos] = 0;  
    Serial.println (buf);
    pos = 0;
    process_it = false;
  }  // end of flag set
  
}
