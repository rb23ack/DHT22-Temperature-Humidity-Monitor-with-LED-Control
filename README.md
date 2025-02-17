# ESP32 Temperature, Humidity, and Button-Controlled LED with OLED Display

This project utilizes an ESP32 microcontroller to read temperature and humidity data from a DHT22 sensor, display the readings on an SSD1306 OLED display, and control an LED based on button presses. The button toggles the LED blinking on and off, with debounce logic implemented for reliable button presses. I built it using "Wokwi" the online simulator. It is a great tool for prototyping. We need to be careful with wirings when building the physical device since it's a bit different when implementing the "actual" work. 

## Components Used

- **ESP32**: Microcontroller for the project.
- **DHT22**: Temperature and humidity sensor.  
- **SSD1306 OLED Display**: 128x64 pixel OLED display.   
- **LED**: Used to show blinking based on button press.  
- **Push Button**: Used to toggle the LED blinking.

## Wiring

- **DHT22**:
  - VCC → 3.3V
  - GND → GND
  - Data Pin → GPIO 16 (DHTPIN)
  
- **OLED Display (SSD1306)**:
  - VCC → 3.3V
  - GND → GND
  - SDA → GPIO 33 (SDA_PIN)
  - SCL → GPIO 13 (SCL_PIN)
  
- **LED**:
  - Anode → GPIO 4 (LED_PIN)
  - Cathode → GND

- **Push Button**:
  - One terminal → GPIO 18 (BUTTON_PIN)
  - Other terminal → GND

## Software

This project is programmed in Arduino IDE and uses the following libraries:
- `Adafruit_SSD1306` for OLED display control.
- `DHT` for reading temperature and humidity data.
- `Wire` for I2C communication.

## Features

- **Temperature and Humidity Display**: Displays real-time temperature and humidity on the OLED screen.
- **Button Controlled LED**: The LED will blink when the button is pressed. The LED toggles on or off with each button press, thanks to debounce logic.
- **Debounce Logic**: Ensures stable and reliable button presses by filtering out noise.

## Installation

1. Clone or download the repository to your computer.
2. Open the project in the Arduino IDE.
3. Install the required libraries:
   - Adafruit SSD1306
   - DHT sensor library
4. Select the correct board (ESP32) and port in the Arduino IDE.
5. Upload the code to the ESP32.

## Code Explanation

- **DHT Sensor**: Reads temperature and humidity data every 2 seconds.
- **OLED Display**: Shows the current temperature and humidity values in real-time.
- **Button**: Toggles the LED blinking with debounce logic to avoid multiple triggers.
- **LED**: Blinks on and off when the button is pressed.

## Troubleshooting

- If the OLED display does not initialize, check the I2C connections (SDA and SCL) and make sure the address `0x3C` is correct.
- If the DHT22 sensor is not reading correctly, verify its connection and ensure it's powered properly.

## License

This project is open-source and available under the MIT License.    
   
