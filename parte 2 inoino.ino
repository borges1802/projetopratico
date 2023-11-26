#include <IRremote.h>
#include <Servo.h>

Servo servomotor;
const byte IR_RECEIVE_PIN = 7;

int pos = 90; // posição inicial do servo

decode_results results;

void setup() {
  servomotor.attach(6); // inicia o servo
  Serial.begin(9600);
  Serial.println("Teste de IR");
  IrReceiver.enableIRIn(); // inicializa o receptor IR
}

void loop() {
  IRrecv IrReceiver(IR_RECEIVE_PIN); // Declaração estática para evitar redefinição

  if (IrReceiver.decode(&results)) {
    unsigned long keycode = (results.value);
    Serial.println(keycode);
    switch (keycode) {
      case 16:
        Serial.println("1");
        break;
      case 17:
        Serial.println("2");
        break;
      case 18:
        Serial.println("3");
        break;
      case 20:
        Serial.println("4");
        break;
      case 21:
        Serial.println("5");
        break;
      case 22:
        Serial.println("6");
        break;
      case 24:
        Serial.println("7");
        break;
      case 25:
        Serial.println("8");
        break;
      case 26:
        Serial.println("9");
        break;
      case 12:
        Serial.println("0");
        break;
      case 10:
        Serial.println("^");
        break;
      case 6:
        pos += 5; // Aumenta o ângulo do servo em +5

        if (pos > 180) {
          pos = 180; // Não permite que a posição do servo seja maior que 180 graus
        }
        break;
      case 8:
        pos -= 5; // Diminui o ângulo do servo em -5

        if (pos < 0) {
          pos = 0; // Não permite que a posição do servo seja menor que 0 graus
        }
        break;
      default:
        break;
    }

    IrReceiver.resume(); // Reinicia o receptor IR para receber o próximo sinal
  }
}
