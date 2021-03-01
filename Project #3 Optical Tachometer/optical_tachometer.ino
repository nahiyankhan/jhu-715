int irPin = 10;
int statusPin = 9;
// int motorPin = 8;

volatile byte rpmcount;
volatile int status;
unsigned int rpm;
unsigned long timeOld;
unsigned long timeStamp;

void calcRpm() {
  rpmcount++;

  // Toggle status LED
  if (status == LOW) {
    status = HIGH;
  } else {
    status = LOW;
  }
  digitalWrite(statusPin, status);
}
 
void setup() {  
  Serial.begin(9600);

  // Set up motor connection
  // pinMode(motorPin, OUTPUT);

  // Run motor
  // analogWrite(motorPin, 255);

  //Interrupt 0 is digital pin 2, so that is where the IR detector is connected
  //Triggers on FALLING (change from HIGH to LOW)
  attachInterrupt(digitalPinToInterrupt(2), calcRpm, FALLING);

  //Turn on IR LED
  pinMode(irPin, OUTPUT); 
  digitalWrite(irPin, HIGH);

  //Use statusPin to flash along with interrupts
  pinMode(statusPin, OUTPUT);

  rpmcount = 0;
  rpm = 0;
  timeOld = 0;
  status = LOW;
}  
 
void loop() {
  
  //Update RPM every second
  delay(1000);

  // get timestamp
  timeStamp = millis();

  //Don't process interrupts during calculations
  detachInterrupt(digitalPinToInterrupt(2));

  //Note that this would be 60*1000/(millis() - timeOld)*rpmcount if the interrupt
  //happened once per revolution instead of twice. Other multiples could be used
  //for multi-bladed propellers or fans
  rpm = 30*1000/(timeStamp - timeOld)*rpmcount;
  timeOld = millis();
  rpmcount = 0;

  // converting time stamp to seconds
  timeStamp /= 1000;
  
  //Write it out to serial port
  Serial.print(timeStamp); Serial.print(","); Serial.println(rpm, DEC);
  
  //Restart the interrupt processing
  attachInterrupt(digitalPinToInterrupt(2), calcRpm, FALLING);
}
