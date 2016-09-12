/*************************************************************
ARDUINO BREAKER READ/SPI PRE-PROC/TRANSMIT CASES
****************************************************************/

/***************************************************************
 Global Variables
***************************************************************/

byte command = 0; //command from PI
byte bytes[4];
byte bytes2[4];
byte bytes3[4];//

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

    union 
  {
    float f_var2;
    unsigned char bytes2[4];
  } u2;

    union 
  {
    float f_var3;
    unsigned char bytes3[4];
  } u3;
  
  // Overwrite bytes of union with float variable
  u.f_var = RealVoltage;
  u2.f_var2 = RealCurrent;
  u3.f_var3 = Power;
  
  // Assign bytes to input array
  memcpy(bytes, u.bytes, 4);
  memcpy(bytes2, u2.bytes2, 4);
  memcpy(bytes3, u3.bytes3, 4);
  
  byte c = SPDR;
  command = c; 

  if(command == 0)
  {
    SPDR = 0; //null command zeroes register
  }
  else if(command == 1) //command 1 - 4 reserved for voltage
  {
    SPDR = u.bytes[0];
  }
  else if(command == 2)
  {
    SPDR = u.bytes[1];  
  }
  else if(command == 3)
  { 
    SPDR =  u.bytes[2];  
  }
  else if(command == 4)
  { 
    SPDR = u.bytes[3];  
  } 
 // command 5 - 8 reserved for current
   else if(command == 5) //command 1 - 4 reserved for voltage
  {
    SPDR = u2.bytes2[0];
  }
  else if(command == 6)
  {
    SPDR = u2.bytes2[1];  
  }
  else if(command == 7)
  { 
    SPDR =  u2.bytes2[2];  
  }
  else if(command == 8)
  { 
    SPDR = u2.bytes2[3];  
  }  
  // command 9 - 12 reserved for wattage
  else if(command == 9) //command 1 - 4 reserved for voltage
  {
    SPDR = u3.bytes3[0];
  }
  else if(command == 10)
  {
    SPDR = u3.bytes3[1];  
  }
  else if(command == 11)
  { 
    SPDR =  u3.bytes3[2];  
  }
  else if(command == 12)
  { 
    SPDR = u3.bytes3[3];  
  }
  else
  {
    SPDR = 0; //null
  }

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
  RealCurrent = 1.234;
  Power = (RealVoltage*RealCurrent);
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

