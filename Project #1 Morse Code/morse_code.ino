// include LCD library
#include <LiquidCrystal.h>

// initialized LCD interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// declare which pin the LED is connected to
unsigned int ledPin = 9;

// array of morse codes for alphabets
char *letters[] = {
  ".-",   // a
  "-...", // b
  "-.-.", // c
  "-..",  // d
  ".",    // e
  "..-.", // f
  "--.",  // g
  "....", // h
  "..",   // i
  ".---", // j
  "-.-",  // k
  ".-..", // l
  "--",   // m
  "-.",   // n
  "---",  // o
  ".--.", // p
  "--.-", // q
  ".-.",  // r
  "...",  // s
  "-",    // t
  "..-",  // u
  "...-", // v
  ".--",  // w
  "-..-", // x
  "-.--", // y
  "--.."  // z   
};
 
unsigned int blinkDuration = 200;
bool done = false;

void setup() {
  // set the LED to output
  pinMode(ledPin, OUTPUT);
   
  // open the serial port
  Serial.begin(9600);
  Serial.println("Enter message or ! to exit");

  // initialize and print to the LCD
  lcd.begin(16, 2);
  lcd.print("Enter message");
  
  lcd.setCursor(0,1);
  lcd.print("or ! to exit.");
}

void loop() {
  char ch;
   
  // main loop that keeps running until the sentinel "!" is entered
  while (!done) {
    if (Serial.available() > 0) {

      // clears the lcd
      lcd.clear();

      // read char
      ch = Serial.read();
      
      // handle upper case letters
      if (ch >= 'A' && ch <= 'Z') {
        outputMorse(ch, letters[ch - 'A']);
      }
      
      // handle lower case letters
      if (ch >= 'a' && ch <= 'z') {
        outputMorse(ch, letters[ch - 'a']);        
      }
      
      // handle spaces
      else if (ch == ' ') {
        // Put space between two words in a message...equal to seven dots
        delay(blinkDuration * 7);       
      }
      
      // handle exit condition
      else if (ch == '!') {
        done = true;  
        Serial.println("Thank you for using morse code! Have a good day!");

        lcd.clear();
        lcd.print("Thank you! Have");

        lcd.setCursor(0,1);
        lcd.print("a good day!");
        
      }
    }
  }  
}

void outputMorse(char ch, char *morseCode) {

  // print the char and corresponding morse code to the LCD
  lcd.clear();
  lcd.print(ch);
  lcd.setCursor(0,1);
  lcd.print(morseCode);
  
  // loop through the morse code and send the type of signal to the LED
  for (int i = 0; i < sizeof(morseCode) + 1; i++) {
    blinkType(morseCode[i]);
  }
  
  // delay until next letter
  delay(blinkDuration * 3);    
}

void blinkType(char morse) {
   
  // turn the LED on
  digitalWrite(ledPin, HIGH);

  if (morse == '.') {
    delay(blinkDuration);           
  } else {
    delay(blinkDuration * 3);           
  }
   
  // turn the LED off
  digitalWrite(ledPin, LOW);

  // delay until the next code
  delay(blinkDuration); 
}
