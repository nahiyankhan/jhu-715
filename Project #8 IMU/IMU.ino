#include <Arduino_FreeRTOS.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

// Initialize
Adafruit_BNO055 bno = Adafruit_BNO055(55);

// Register Task
void TaskIMU( void *pvParameters );

// Task
void TaskIMU(void *pvParameters)
{
  (void) pvParameters;
 
  for (;;)
  {
    // Get a new sensor event
    sensors_event_t event;
    bno.getEvent(&event);
    
    /* Display the floating point data */
    Serial.print("Yaw: ");
    Serial.print(event.orientation.x, 4);
    Serial.print("\tPitch: ");
    Serial.print(event.orientation.y, 4);
    Serial.print("\tRoll: ");
    Serial.print(event.orientation.z, 4);
    Serial.println("");
    
    // Seven tick delay (105ms) in between reads for stability
    vTaskDelay(7);  
  }
}

void setup() {
  
  Serial.begin(9600);
  Serial.println("Orientation Sensor"); Serial.println("");

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  bno.setExtCrystalUse(true);

  xTaskCreate(
    TaskIMU
    ,  "ReadIMU"
    ,  128  // Stack size
    ,  NULL
    ,  2  // Priority
    ,  NULL );
}

void loop() {
  // put your main code here, to run repeatedly:

}
