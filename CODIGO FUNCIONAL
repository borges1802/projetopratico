#include <IRremote.h>
#include <Servo.h>

Servo servomotor;
const byte IR_RECEIVE_PIN = 7;

void setup() {
  servomotor.attach(6); // inicia o servo
  Serial.begin(9600);
  Serial.println("Teste de IR");
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Valor: ");
    Serial.println(IrReceiver.decodedIRData.command, HEX); // Mostra o valor em hexadecimal

    IrReceiver.resume(); // Reinicia o receptor IR para receber o próximo sinal
  }
}
