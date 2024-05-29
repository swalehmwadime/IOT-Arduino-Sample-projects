
#include <LiquidCrystal.h>

// Initialize the LiquidCrystal library with the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// 12 - rs, 11 -e, 5 - D4, 4- D5, 3 -D6, 2 - D7
// Define pins for the ultrasonic sensor
#define ECHO_PIN 7
#define TRIG_PIN 6

// Variables to hold the duration of the pulse and the calculated distance
long duration;
int distance;

void setup() {
  // Set the trigger pin as an output
  pinMode(TRIG_PIN, OUTPUT);
  // Set the echo pin as an input
  pinMode(ECHO_PIN, INPUT);

  // Initialize the LCD with 16 columns and 2 rows
  lcd.begin(16, 2);
  // Clear any previous content on the LCD
  lcd.clear();
}

void loop() {
  // Ensure the trigger pin is low for a short time to start clean
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a 10 microsecond high pulse to trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the duration of the high pulse on the echo pin
  duration = pulseIn(ECHO_PIN, HIGH);

  // Check if the sensor received an echo
  if (duration == 0) {
    // If no echo received, display an error message
    lcd.setCursor(0, 0);
    lcd.print("Distance: Error");
  } else {
    // Calculate the distance in centimeters
    // Speed of sound is approximately 343 meters per second or 0.0343 cm per microsecond
    // Divide by 2 because the duration is the time for the sound to go to the object and back
    distance = (duration * 0.0343) / 2;
    
    // Clear previous distance value on the first row
    lcd.setCursor(0, 0);
    lcd.print("Distance:       ");
    
    // Display the calculated distance
    lcd.setCursor(9, 0); // Position cursor after "Distance: "
    lcd.print(distance);
    lcd.print(" cm");
  }

  // Wait for a second before taking another measurement
  delay(1000);
}
