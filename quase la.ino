#include <IRremote.h>
#include <Servo.h>

Servo servomotor;
const byte IR_RECEIVE_PIN = 7;

int digito = (IrReceiver.decodedIRData.command, HEX);

int teclaClicada(uint8_t teclas);
int contador = 0;//número de dígitos recebidos
int numero = 0;//número recebido
unsigned long ultDecod = 0;//tempo do último dígito recebido

void setup() {
  servomotor.attach(6, 1000, 2000); // inicia o servo
  Serial.begin(9600);
  Serial.println("Teste de IR");
  IrReceiver.begin(IR_RECEIVE_PIN);
}

void loop() {
  if (IrReceiver.decode()) {
    	if (digito >= 0 && digito <= 9) {
      	//add o dígito ao número
      	numero = numero * 10 + digito;

      	//Incrementa o contador de dígitos
      	contador++;

      	//att o tempo do último dígito recebido
      	ultDecod = millis();
    }
    // Verifica se o número está completo
  if (contador == 3 || (millis() - ultDecod > 1500 && contador > 0)) {
    // Imprime o número no monitor serial
    if(numero > 180) numero = 180;
    servomotor.write(numero);
    Serial.println(numero);

    // Reinicia o número, o contador e o tempo
    numero = 0;
    contador = 0;
    ultDecod = 0;
  }
    Serial.print("Valor: ");
    Serial.println(digito); // Mostra o valor em hexadecimal

    IrReceiver.resume(); // Reinicia o receptor IR para receber o próximo sinal
  }
}
