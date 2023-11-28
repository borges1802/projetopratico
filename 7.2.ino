#include <IRremote.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#define IR_PIN_RECEIVER 7
#define SERVO_PIN 6

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Define os pinos que serão utilizados para ligação ao display

Servo servomotor;

int contador = 0;//número de dígitos recebidos
int numero = 0;//número recebido
unsigned long ultDecod = 0;//tempo do último dígito recebido

int numeroRecebido(uint8_t comando);

void setup() {
  servomotor.attach(SERVO_PIN); // inicia o servo
  servomotor.write(0);
  Serial.begin(9600);
  lcd.begin(16, 2);
  IrReceiver.begin(IR_PIN_RECEIVER);
}

void loop() {
if (IrReceiver.decode()) {
    int digito = numeroRecebido(IrReceiver.decodedIRData.command);
    if (digito >= 0 && digito <= 9) {
      numero = numero * 10 + digito;
      contador++;
      ultDecod = millis();
    }
    IrReceiver.resume();
  }
  if (contador == 3 || (millis() - ultDecod > 1200 && contador > 0))
  {
    if(numero > 180) numero = 180;
    servomotor.write(numero);
    Serial.println(numero);
    numero = 0;
    contador = 0;
    ultDecod = 0;
  }
}

int numeroRecebido(uint8_t comando){
  switch(comando){
      case 0xC:
          return 0;
    case 0x10:
          return 1;
    case 0x11:
          return 2;
    case 0x12:
          return 3;
    case 0x14:
          return 4;
    case 0x15:
          return 5;
    case 0x16:
          return 6;
    case 0x18:
          return 7;
    case 0x19:
          return 8;
    case 0x1A:
          return 9;
    default:
        return -1;
    
    lcd.clear(); // Limpa a tela
    lcd.setCursor(3, 0); // Posiciona o cursor na coluna 3, linha 0;
    lcd.print("Posicao atual:"); // Envia o texto entre aspas para o LCD
    lcd.setCursor(3, 1);
    lcd.print(IrReceiver.decodedIRData.command, HEX);
    delay(1000);
    Serial.println(IrReceiver.decodedIRData.command, HEX); // Mostra o valor em hexadecimal
    IrReceiver.resume(); // Reinicia o receptor IR para receber o próximo sinal
  }
}
