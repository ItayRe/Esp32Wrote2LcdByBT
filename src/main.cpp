#include <Arduino.h>
#include "BluetoothSerial.h"
#include <Adafruit_SSD1306.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

BluetoothSerial SerialBT;


#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino resetpin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String message = "";
char incomingChar;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(921600);
    SerialBT.begin("ESP32test"); //Bluetooth device name
    Serial.println("The device started, now you can pair it with bluetooth!");

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Don't proceed, loop forever
    }
    // Clear the buffer.
    display.clearDisplay();
    // Display Text
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 28);
    display.println("Hello world!");
    display.display();
    delay(2000);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 28);
    display.println("Goodbye!");
    display.display();
    display.println("");
    display.display();
}



void loop() {
  // put your main code here, to run repeatedly:
    if (SerialBT.available()) {
        char incomingChar = SerialBT.read();
        if (incomingChar != '\n'){
            message += incomingChar;
        }
        else{
            message = "";
        }
    Serial.write(incomingChar);
    }
    
    if (message == "hello"){
        Serial.println(message);
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 28);
        display.println(message);
        display.display();
        delay(2000);
        // Clear the buffer.
        display.clearDisplay();
    }
    delay(20);

}
