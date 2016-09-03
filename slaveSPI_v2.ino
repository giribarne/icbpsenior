/*************************************************************
ARDUINO BREAKER READ/SPI PRE-PROC/TRANSMIT CASES
****************************************************************/

/***************************************************************
 Global Variables
***************************************************************/

byte command = 0; //command from PI
byte bytes[4];    //

int sensorVoltage, sensorCurrent; //eventual live reading vars
float Voltage, Current, RealCurrent, RealVoltage, Power;

/***************************************************************
 Set Up
  -designate arudino as slave
  -turn on interrupts
***************************************************************/

void setup (void)
{
  //debugging with serial monitor
  Serial.begin(9600);
  
  // Set up arduino as slave
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);   
  pinMode(MISO, OUTPUT);

  // turn on SPI in slave mode
  SPCR |= _BV(SPE);

  // turn on interrupts
  SPCR |= _BV(SPIE);

}  // end of setup

/*************************************************************
 Interrupt Service Routine 
 ************************************************************/
  
// SPI interrupt routine
ISR (SPI_STC_vect)
{ 
  // Create union of shared memory space
  union 
  {
    float f_var;
    unsigned char bytes[4];
  } u;
  
  // Overwrite bytes of union with float variable
  u.f_var = RealVoltage;
  
  // Assign bytes to input array
  memcpy(bytes, u.bytes, 4);
  
  byte c = SPDR;
  command = c; 

  switch (command)
  {
  // null command zeroes register
  case 0:
    
    SPDR = 0;
    break;
    
  // case a - d reserved for voltage
  case 'a':
    SPDR = bytes[0];  
    break;
    
  // incoming byte, return byte result
  case 'b':
    
    SPDR = bytes[1];  
    break;

  // incoming byte, return byte result    
  case 'c':
    
    SPDR =  bytes[2];  
    break;
   

  // incoming byte, return byte result    
  case 'd':
    
    SPDR = bytes[3];  
    break;
    
 /**  // case e -h reserved for current
  case 'e':
    
    SPDR = amps.b[0];  
    break;
    
  // incoming byte, return byte result
  case 'f':
    
    SPDR = amps.b[1];  
    break;

  // incoming byte, return byte result    
  case 'g':
    
    SPDR = amps.b[2];  
    break;

  // incoming byte, return byte result    
  case 'h':
    
    SPDR = amps.b[3];  
    break;
    
   // case i - l reserved for wattage
  case 'i':
    
    SPDR = watts.b[0];  
    break;
    
  // incoming byte, return byte result
  case 'j':
    
    SPDR = watts.b[1];  
    break;

  // incoming byte, return byte result    
  case 'k':
    
    SPDR = watts.b[2];  
    break;

  // incoming byte, return byte result    
  case 'l':
    
    SPDR = watts.b[3];  
    break;**/

  } // end of switch

}  // end of interrupt service routine (ISR) SPI_STC_vect

/***************************************************************  
 Loop until slave is enabled by Pi.
****************************************************************/
void loop (void)
{
/*************************************************************
Read and Calculate
****************************************************************/

  /**
  sensorVoltage = analogRead(A2);
  sensorCurrent = analogRead(A3);
  Voltage = sensorVoltage*(5.0/1023.0);
  Current = sensorCurrent*(5.0/1023.0);
  RealCurrent = Current/0.204545;
  RealVoltage = (Voltage/0.022005);
  Power = RealVoltage*RealCurrent;
**/
  RealVoltage = 1.234;
/*************************************************************
Loop Check for SS activation
****************************************************************/

  // if SPI not active, clear current command, else preproc floats and pass to SPI
  if (digitalRead (SS) == HIGH){
    command = 0;
  }
/*************************************************************
Debug with serial monitor
****************************************************************/
/*
  Serial.print("Byte 3: ");
  Serial.println(bytes[3],BIN);
  delay(500);
  Serial.print("Byte 2: ");
  Serial.println(bytes[2],BIN);
  delay(500);
  Serial.print("Byte 1: ");
  Serial.println(bytes[1],BIN);
  delay(500);
  Serial.print("Byte 0: ");
  Serial.println(bytes[0],BIN);
  delay(1000);
  Serial.println();*/
}

