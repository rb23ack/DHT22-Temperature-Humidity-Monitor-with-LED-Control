#include <WiFi.h>  // Remove if no WiFi functionality
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// DHT Sensor Setup
#define DHTPIN 16       // DHT22 data pin
#define DHTTYPE DHT22   // DHT22 type
DHT dht(DHTPIN, DHTTYPE);

// OLED Display Setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// LED and Button Pins
#define LED_PIN 4
#define BUTTON_PIN 18

// Custom I2C Pins
#define SDA_PIN 13  // Custom SDA pin
#define SCL_PIN 33  // Custom SCL pin

// Variables for button and debounce
bool buttonPressed = false;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;  // 50ms debounce

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize DHT Sensor
  dht.begin();

  // Initialize I2C with custom SDA and SCL pins
  Serial.println("Initializing I2C...");
  Wire.begin(SDA_PIN, SCL_PIN);

  // Check for I2C communication
  if (!Wire.requestFrom(0x3C, 1)) {
    Serial.println("I2C Communication failed!");
  } else {
    Serial.println("I2C Communication successful!");
  }

  // Initialize OLED Display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // OLED address 0x3C
    Serial.println("OLED initialization failed!");
    while (true);  // If OLED fails, stop the program
  } else {
    Serial.println("OLED initialized successfully!");
  }

  display.clearDisplay();
  display.display();

  // Initialize LED and Button
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // Read Temperature and Humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if the readings are valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print readings to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Display readings on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" °C");
  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");
  display.display();

  // Handle Button Press (Debounce Logic)
  if (digitalRead(BUTTON_PIN) == LOW) { // Button is pressed (LOW state)
    unsigned long currentTime = millis();
    if (currentTime - lastDebounceTime > debounceDelay) {
      lastDebounceTime = currentTime;
      buttonPressed = !buttonPressed;  // Toggle the buttonPressed state
      Serial.print("Button Pressed: ");
      Serial.println(buttonPressed);  // Show the current state of buttonPressed
    }
  }

  // Blink LED when button is pressed
  if (buttonPressed) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }

  delay(2000);  // Delay between readings
}
