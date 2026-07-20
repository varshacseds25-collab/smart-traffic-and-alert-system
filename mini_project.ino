#include <DHT.h>

// DHT11
#define DHTPIN 3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Ultrasonic Sensor
int trigPin = 9;
int echoPin = 10;

// Sound Sensor
int soundPin = 2;

// LEDs
int greenLED = 5;
int yellowLED = 6;
int redLED = 7;

// Buzzer
int buzzer = 4;

long duration;
int distance;
float temp;

void setup()
{
  Serial.begin(9600);

  dht.begin();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(soundPin, INPUT);

  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  pinMode(buzzer, OUTPUT);

  Serial.println("SMART TRAFFIC SYSTEM");
}

void loop()
{
  // TEMPERATURE
  temp = dht.readTemperature();

  // ULTRASONIC
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  // SOUND SENSOR
  int sound = digitalRead(soundPin);

  // SERIAL MONITOR DISPLAY
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // LED CONTROL
  if(distance > 30)
  {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);

    Serial.println("LOW TRAFFIC");
  }
  else if(distance > 15)
  {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);

    Serial.println("MEDIUM TRAFFIC");
  }
  else
  {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);

    Serial.println("HIGH TRAFFIC");
  }

  // SOUND ALERT
  if(sound == HIGH)
  {
    digitalWrite(buzzer, HIGH);

    Serial.println("AMBULANCE DETECTED");
  }
  else
  {
    digitalWrite(buzzer, LOW);
  }

  Serial.println("-------------------");

  delay(1000);
}
