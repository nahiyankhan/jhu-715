//TMP36 Pin Variables
int sensorPin = 0;
float sensorInput;
float voltage;
unsigned long timeStamp;

void setup() {
  Serial.begin(9600);
}
 
void loop() {
 //getting the voltage reading from the temperature sensor
 sensorInput = analogRead(sensorPin);  
 timeStamp = millis();

 // converting time stamp to seconds
 timeStamp /= 1000;
 
 // converting that reading to voltag
 voltage = sensorInput * 5;
 voltage /= 1024.0; 
 
 // convert voltage to celsius
 float celsius = (voltage - 0.5) * 100;
 
 // now convert to Fahrenheit
 float fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
 Serial.print(timeStamp); Serial.print(","); Serial.print(fahrenheit); Serial.println("F");

 // delay by 10 seconds
 delay(10000);
}
