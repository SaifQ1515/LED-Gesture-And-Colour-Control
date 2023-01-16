/*
This is code for LED Gesure and Colour Control
 * Uses and I2C dysplay
 * Sparkfun APDS-9 Gesture and Colour Sensor
 * Created by Saif Qadri
 */
 
#include <FastLED.h> // LED libraries
#include <Wire.h>   // I2C Communication 
#include <SparkFun_APDS9960.h>   // Gesture and RGB sensor libraries
#include <LiquidCrystal_I2C.h>   // LCD screen libraries

#define LED_PIN     5   // digital input pin for LED
#define NUM_LEDS    5   // Numbers of LED on
CRGB leds[NUM_LEDS];   // Array for LEDs

LiquidCrystal_I2C lcd(0x27, 16, 2);  //LCD size initiallization

SparkFun_APDS9960 apds = SparkFun_APDS9960();  //Creating an object for the sensor

uint8_t proximity_data = 0; // variable for proximety value

uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;              // ambient, red, green, blue varables
uint16_t blue_light = 0;

const int buttonPin = 7;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  lcd.begin();
  lcd.backlight();  //Initialize LCD Screen

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);  //Initialize LED tpye, pin and array (number of leds)
  
  pinMode(ledPin, OUTPUT);  // initialize the LED pin as an output:

  pinMode(buttonPin, INPUT);   // initialize the pushbutton pin as an input:
}

void loop() {
  buttonState = digitalRead(buttonPin);     // read the state of the pushbutton value:

  if (buttonState == HIGH) {       // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    
    digitalWrite(ledPin, HIGH);      // turn LED on:

  Serial.begin(9600);                // Initialize Serial port this portion is only used for the console, does not directly impact user
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - ColorSensor"));
  Serial.println(F("--------------------------------"));
  
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));       // Initialize APDS-9960 (configure I2C and initial values)
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  if ( apds.enableLightSensor(false) ) {                  // Start running the APDS-9960 light sensor (no interrupts)
    Serial.println(F("Light sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during light sensor init!"));
  }
  
  delay(500);        // Wait for initialization and calibration to finish

  Colour();   // Call Colour function to read data
  
  } else {    // if LED is not on, it is off and there for the status is LOW
  
    digitalWrite(ledPin, LOW);
    Serial.begin(9600);
    Serial.println();
    Serial.println(F("------------------------------------"));
    Serial.println(F("SparkFun APDS-9960 - ProximitySensor"));
    Serial.println(F("------------------------------------"));
    
    if ( apds.init() ) {                       // Initialize APDS-9960 (configure I2C and initial values)
      Serial.println(F("APDS-9960 initialization complete"));
    } else {
      Serial.println(F("Something went wrong during APDS-9960 init!"));
    }
    
    if ( !apds.setProximityGain(PGAIN_2X) ) {             // Adjust the Proximity sensor gain
      Serial.println(F("Something went wrong trying to set PGAIN"));
    }
    
    if ( apds.enableProximitySensor(false) ) {                    // Start running the APDS-9960 proximity sensor (no interrupts)
      Serial.println(F("Proximity sensor is now running"));
    } else {
      Serial.println(F("Something went wrong during sensor init!"));
    }
    Prox(); // Call fundtion prox to read data
  }
}

void Colour() {
      if (  !apds.readAmbientLight(ambient_light) ||
          !apds.readRedLight(red_light) ||
          !apds.readGreenLight(green_light) ||
          !apds.readBlueLight(blue_light) ) {
      lcd.print("Error reading light values");     //error trap
    } else {
      if (red_light > green_light)
      {
        if (red_light > blue_light)       //This section compares RGB values and if the conditions are met, red is detected
        {
          leds[0] = CRGB(255, 0, 0);
          FastLED.show();
          leds[1] = CRGB(255, 0, 0);
          FastLED.show();
          leds[2] = CRGB(255, 0, 0);
          FastLED.show();
          leds[3] = CRGB(255, 0, 0);
          FastLED.show();
          leds[4] = CRGB(255, 0, 0);
          FastLED.show();
          lcd.print("Red");   //prints Red on screen for 1 second then clears
          delay (1000);
          lcd.clear();
        }
        else
        {
          leds[0] = CRGB(0, 0, 255);          //This section compares RGB values and if the conditions are met, blue is detected
          FastLED.show();
          leds[1] = CRGB(0, 0, 255);
          FastLED.show();
          leds[2] = CRGB(0, 0, 255);
          FastLED.show();
          leds[3] = CRGB(0, 0, 255);
          FastLED.show();
          leds[4] = CRGB(0, 0, 255);
          FastLED.show();
          lcd.print("Blue");       //prints Blue on screen for 1 second then clears
          delay (1000);
          lcd.clear();
        }
      }
      else if (green_light > blue_light) {                 //This section compares RGB values and if the conditions are met, greeb is detected
          leds[0] = CRGB(0, 255, 0);
          FastLED.show();
          leds[1] = CRGB(0, 255, 0);
          FastLED.show();
          leds[2] = CRGB(0, 255, 0);
          FastLED.show();
          leds[3] = CRGB(0, 255, 0);
          FastLED.show();
          leds[4] = CRGB(0, 255, 0);
        lcd.print("Green");         //prints Green on screen for 1 second then clears
        delay (1000);
        lcd.clear();
      }
      else {
          leds[0] = CRGB(0, 0, 255);              //This section compares RGB values and if the conditions are met, blue is detected
          FastLED.show();
          leds[1] = CRGB(0, 0, 255);
          FastLED.show();
          leds[2] = CRGB(0, 0, 255);
          FastLED.show();
          leds[3] = CRGB(0, 0, 255);
          FastLED.show();
          leds[4] = CRGB(0, 0, 255);
        lcd.print("Blue");         //prints Blue on screen for 1 second then clears
        delay (1000);
        lcd.clear();
      }

    }
}

void Prox(){
  // Read the proximity value
if ( !apds.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");   //Error trap
  } else {
    Serial.print("Proximity: ");
    Serial.println(proximity_data);
    
      if (proximity_data >=200)        //if the hand is closer than 200m then a right swipe is detected
      {
        leds[0] = CRGB(255, 0, 0);    //Raising the brightness
          FastLED.show();
          leds[1] = CRGB(255, 0, 0);
          FastLED.show();
          leds[2] = CRGB(255, 0, 0);
          FastLED.show();
          leds[3] = CRGB(255, 0, 0);
          FastLED.show();
          leds[4] = CRGB(255, 0, 0);
      lcd.print("Right Swipe");      //prints Right Swipe on screen for 2 second then clears
      delay(2000);
      lcd.clear();
      }
      else if (proximity_data >=200< 200 && proximity_data >= 100)     //if the hand is further than 200mm but closer than 100mm
      {
        leds[0] = CRGB(64, 0, 0);
          FastLED.show();
          leds[1] = CRGB(64, 0, 0);  //lowering the brightness
          FastLED.show();
          leds[2] = CRGB(64, 0, 0);
          FastLED.show();
          leds[3] = CRGB(64, 0, 0);
          FastLED.show();
          leds[4] = CRGB(64, 0, 0);
      lcd.print("Left Swipe");        //prints Left Swipe on screen for 2 second then clears
      delay(2000);
      lcd.clear();
      }
  }
  

  delay(250);   // Delay 
}
