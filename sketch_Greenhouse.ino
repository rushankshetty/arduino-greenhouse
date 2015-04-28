#include "DHT.h"

#define DHTPIN 2           // what pin we're connected the DHT11 to

#define DHTTYPE DHT11      // DHT 11 

#define FANPIN1 8          // what pin we've connected the FAN to

#define FANPIN2 9          // what pin we've connected the FAN to

#define MOISTURESENSOR A0  // what pin we've connected the SOIL MOISTURE SENSOR to

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);
// NOTE: For working with a faster chip, like an Arduino Due or Teensy, you
// might need to increase the threshold for cycle counts considered a 1 or 0.
// You can do this by passing a 3rd parameter for this threshold.  It's a bit
// of fiddling to find the right value, but in general the faster the CPU the
// higher the value.  The default for a 16mhz AVR is a value of 6.  For an
// Arduino Due that runs at 84mhz a value of 30 works.
// Example to initialize DHT sensor for Arduino Due:
//DHT dht(DHTPIN, DHTTYPE, 30);

void setup() {
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
 
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  // Read soil moisture
  float s = analogRead(MOISTURESENSOR);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  else if(isnan(s)) {
    Serial.println("Failed to read from SOIL MOISTURE sensor!");
    return;
  }
  else {
  // Compute heat index
  // Must send in temperature in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Soil moisture: "); 
  Serial.print(s);
  Serial.print(" \t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");
  
  if(t > 29.0) {
	// Start the fan for cooling
     digitalWrite(FANPIN1, HIGH);
  }
  else {
	// Else don't
    digitalWrite(FANPIN1, LOW);
  }
  
  }
}
