#include <IRremote.h>   //Incluimos la libreria del infrarrojo

//Conectaremos el sensor infrarrojo a un pin DIGITAL del Arduino, en este caso sera el pin 2

IRrecv sensor(2);                 //Inicializamos el sensor infrarrojo, poniendo el pin digital 2 como parametro
decode_results lectura;           //Variable que va a almacenar la lectura del control infrarrojo

//Incluimos la libreria del servomotor
#include <Servo.h>
Servo servomotor;

int posicion_servo = 90; //El servo inicia en 90 grados

unsigned long lectura_anterior;   //Variable para almacenar la señal anterior recibida

void setup()
{
  servomotor.attach(6); //Pin PWM 6 del Arduino donde conectamos el servo
  sensor.enableIRIn();  //Habilitamos el sensor infrarrojo para que pueda recibir lecturas
}

void loop()

{
  if (sensor.decode(&lectura))    //Si recibe una lectura
  {
    if (lectura.value == 0xFFC23D)
    {
      lectura_anterior = 0xFFC23D;            //La señal anterior corresponde a la tecla ">" (Derecha)
      posicion_servo = posicion_servo + 5;    //Aumenta el angulo del servo en +5

      if (posicion_servo > 180)
      {
        posicion_servo = 180;                 //No permite que la posicion del servo sea mayor a 180 grados
      }
    }

    if (lectura.value == 0xFF22DD)
    {
      lectura_anterior = 0xFF22DD;            //La señal anterior corresponde a la tecla "<" (Izquierda)
      posicion_servo = posicion_servo - 5;    //Disminuye el angulo del servo en -5

      if (posicion_servo < 0)
      {
        posicion_servo = 0;                   //No permite que la posicion del servo sea menor a 0 grados
      }
    }

    //Si se recibe un 0xFFFFFFFF y la señal anterior recibida es un 0xFFC23D, quiere decir que se mantiene presionanda la tecla ">" (Derecha)
    if (lectura.value == 0xFFFFFFFF && lectura_anterior == 0xFFC23D)
    {
      posicion_servo = posicion_servo + 5;    //Aumenta el angulo del servo en +5

      if (posicion_servo > 180)
      {
        posicion_servo = 180;                 //No permite que la posicion del servo sea mayor a 180 grados
      }
    }

    //Si se recibe un 0xFFFFFFFF y la señal anterior recibida es un 0xFF22DD, quiere decir que se mantiene presionanda la tecla "<" (Izquierda)
    if (lectura.value == 0xFFFFFFFF && lectura_anterior == 0xFF22DD)
    {
      posicion_servo = posicion_servo - 5;     //Disminuye el angulo del servo en -5

      if (posicion_servo < 0)
      {
        posicion_servo = 0;                   //No permite que la posicion del servo sea menor a 0 grados
      }
    }

    if (lectura.value == 0xFF02FD)          //Corresponde a la tecla "OK"
    {
      posicion_servo = 90;                  //Regresa el servo a su posicion inicial de 90 grados
    }

    if (lectura.value == 0xFF629D)        //Corresponde a la tecla "Arriba"
    {
      posicion_servo = 180;               //Pone el servo en 180 grados
    }

    if (lectura.value == 0xFFA857)        //Corresponde a la tecla "Abajo"
    {
      posicion_servo = 0;                 //Pone el servo en 0 grados
    }
    sensor.resume();  //Prepara el sensor infrarrojos para nuevas lecturas
    servomotor.write(posicion_servo);  //Manda la posicion al servo
    delay(20);
  }

}
