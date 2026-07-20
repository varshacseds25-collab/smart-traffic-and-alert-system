/*
====================================================
SMART TRAFFIC MANAGEMENT SYSTEM
====================================================

COMPONENTS:
1. Arduino UNO / ESP32
2. DHT11 Sensor
3. Sound Sensor
4. Red LED
5. Yellow LED
6. Green LED

====================================================
PIN CONNECTIONS
====================================================

DHT11 Sensor:
VCC  -> 5V
GND  -> GND
DATA -> Pin 2

Sound Sensor:
OUT -> A0

LEDs:
Red LED    -> Pin 8
Yellow LED -> Pin 9
Green LED  -> Pin 10

====================================================
*/

#include <DHT.h>

// =================================================
// DHT SENSOR CONFIGURATION
// =================================================

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// =================================================
// PIN DEFINITIONS
// =================================================

#define SOUND_SENSOR A0

#define RED_LED 8
#define YELLOW_LED 9
#define GREEN_LED 10

// =================================================
// VARIABLES
// =================================================

int soundValue = 0;
int trafficDensity = 0;

float temperature = 0;
float humidity = 0;

bool ambulanceDetected = false;

// =================================================
// SETUP
// =================================================

void setup()
{
    Serial.begin(9600);

    dht.begin();

    pinMode(SOUND_SENSOR, INPUT);

    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    randomSeed(analogRead(1));

    Serial.println("SMART TRAFFIC MANAGEMENT SYSTEM");
    Serial.println("SYSTEM STARTED");
}

// =================================================
// AMBULANCE DETECTION
// =================================================

void detectAmbulance()
{
    soundValue = analogRead(SOUND_SENSOR);

    // Threshold for sound detection
    if (soundValue > 600)
    {
        ambulanceDetected = true;
    }
    else
    {
        ambulanceDetected = false;
    }
}

// =================================================
// TEMPERATURE & HUMIDITY
// =================================================

void readEnvironment()
{
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity))
    {
        Serial.println("DHT SENSOR ERROR");

        temperature = 0;
        humidity = 0;
    }
}

// =================================================
// TRAFFIC DENSITY
// =================================================

void calculateTrafficDensity()
{
    // Simulated traffic density
    trafficDensity = random(0, 101);
}

// =================================================
// TRAFFIC LIGHT CONTROL
// =================================================

void controlTrafficLights()
{
    // Ambulance detected
    if (ambulanceDetected)
    {
        digitalWrite(RED_LED, LOW);
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
    }
    else
    {
        // Heavy traffic
        if (trafficDensity > 80)
        {
            digitalWrite(RED_LED, LOW);
            digitalWrite(YELLOW_LED, HIGH);
            digitalWrite(GREEN_LED, LOW);
        }
        else
        {
            digitalWrite(RED_LED, HIGH);
            digitalWrite(YELLOW_LED, LOW);
            digitalWrite(GREEN_LED, LOW);
        }
    }
}

// =================================================
// DISPLAY STATUS
// =================================================

void displayStatus()
{
    Serial.println();
    Serial.println("==============================");

    if (ambulanceDetected)
    {
        Serial.println("AMBULANCE DETECTED");
        Serial.println("GREEN SIGNAL ENABLED");
    }
    else
    {
        Serial.println("NO AMBULANCE");
    }

    Serial.print("SOUND VALUE: ");
    Serial.println(soundValue);

    Serial.print("TEMPERATURE: ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("HUMIDITY: ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("TRAFFIC DENSITY: ");
    Serial.print(trafficDensity);
    Serial.println(" %");

    if (trafficDensity > 80)
    {
        Serial.println("HEAVY TRAFFIC ALERT");
    }

    if (temperature > 38)
    {
        Serial.println("HIGH TEMPERATURE ALERT");
    }

    Serial.println("==============================");
}

// =================================================
// MAIN LOOP
// =================================================

void loop()
{
    detectAmbulance();

    readEnvironment();

    calculateTrafficDensity();

    controlTrafficLights();

    displayStatus();

    delay(5000);
}
