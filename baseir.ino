#include <IRremote.h>
#include <Servo.h>

#define IR_RECEIVE_PIN 7

#define SERVO 6
Servo s; // variável servo
int pos; // posição do servo
  
void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  Serial.println("Entenda o servo:");
  s.attach(SERVO); // liga o servo
  s.write(0); // posição inicial do servo motor
}

void loop()
{
  s.write(180); // Comando para mandar o servo para posição 180
  delay(1500); // Espera de 500 ms
  s.write(0); // Comando para mandar o servo para posição 0
  delay(1500); // Espera de 500 ms
  s.write(90); // Comando para mandar o servo para posição 90
  delay(1500);  // Espera de 500 ms
}
