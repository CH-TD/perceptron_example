#include "perceptron.h »
// Constant values
const int ECHO_PIN = 5;
const int TRIGGER_PIN = 6;
const int GREEN_LED_PIN = 12;
const int RED_LED_PIN = 11;
// Vars
float distance;
long time;
// Our perceptron
Perceptron perceptron(1);
// Train the perceptron
void train()
{
int distance_step = 5;
// Train for 160 epochs
for (int epoch = 0; epoch < 160; epoch++)
{
for (int d = 0; d < 340; d += distance_step)
{
perceptron.inputs[0] = d; // Set the input in the model
// Make a prediction
int predicted = perceptron.feed_forward();
if ((d <= 150 && predicted == -1) || (d > 150 && predicted == 1))
{
perceptron.train(-predicted, predicted);
}
}
}
}

void setup()
{
Serial.begin(115200);
// Set the pins
pinMode(TRIGGER_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);
pinMode(GREEN_LED_PIN, OUTPUT);
pinMode(RED_LED_PIN, OUTPUT);
// Train the model before
train();
}
void loop()
{
// Send a pulse to activate the sensor
digitalWrite(TRIGGER_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIGGER_PIN, LOW);
// Measure response pulse
time = pulseIn(ECHO_PIN, HIGH)/2;
// d = v * t, Speed of sound = 343m/s
distance = float(time*0.0343);
Serial.print("Distance: ");
Serial.println(distance);
// Set the input in the model
perceptron.inputs[0] = distance;
// Classify
int predicted = perceptron.feed_forward();
Serial.print("Predicted: ");
Serial.println(predicted);
if (predicted == -1)
{
digitalWrite(GREEN_LED_PIN, LOW);
digitalWrite(RED_LED_PIN, HIGH);
}
else
{
digitalWrite(GREEN_LED_PIN, HIGH);
digitalWrite(RED_LED_PIN, LOW);
}
delay(1000);
}