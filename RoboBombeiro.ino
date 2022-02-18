// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

//Carrega a biblioteca do sensor ultrassonico
#include <AFMotor.h>
#include <Ultrasonic.h>

AF_DCMotor motorEsqF(1);
AF_DCMotor motorDirF(2);
AF_DCMotor motorEsqT(3);
AF_DCMotor motorDirT(4);

//Define os pinos para o trigger e echo
#define pino_trigger_1 52
#define pino_echo_1 53
#define pino_trigger_2 51
#define pino_echo_2 50
#define pino_trigger_3 45
#define pino_echo_3 44
#define INA 47
#define INB 46
#define flamePinD  49
#define flamePinE  48
int flameD;
int flameE;

int mspeed = 0;

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic1(pino_trigger_1, pino_echo_1);
Ultrasonic ultrasonic2(pino_trigger_2, pino_echo_2);
Ultrasonic ultrasonic3(pino_trigger_3, pino_echo_3);

//Le as informacoes do sensor, em cm e pol
float esquerda;
float frente;
float direita;
int ofrente = 0;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(flamePinD, INPUT);
  pinMode(flamePinE, INPUT);

  // turn on motor
  motorEsqF.setSpeed(mspeed);
  motorEsqT.setSpeed(mspeed);
  motorDirF.setSpeed(mspeed);
  motorDirT.setSpeed(mspeed);


  motorEsqF.run(RELEASE);
  motorEsqT.run(RELEASE);
  motorDirF.run(RELEASE);
  motorDirT.run(RELEASE);

  delay(3000);
}

void loop() {

  flameD = digitalRead(flamePinD);
  flameE = digitalRead(flamePinE);
  //Serial.println(flameD);

  if (flameD == 1 || flameE == 1)
  {
    parar();
    //delay(1000);
    digitalWrite(INA, LOW);
    digitalWrite(INB, HIGH);
    delay(1500);
  }
  else
  {
    digitalWrite(INA, LOW);
    digitalWrite(INB, LOW);
    seguirparede();
  }

}


void forward() {
  motorEsqF.run(FORWARD);
  motorEsqT.run(FORWARD);
  motorDirF.run(FORWARD);
  motorDirT.run(FORWARD);
}

void backward() {
  motorEsqF.run(BACKWARD);
  motorEsqT.run(BACKWARD);
  motorDirF.run(BACKWARD);
  motorDirT.run(BACKWARD);
}

void right() {
  motorEsqF.run(FORWARD);
  motorEsqT.run(FORWARD);
  motorDirF.run(BACKWARD);
  motorDirT.run(BACKWARD);
}

void left() {
  motorEsqF.run(BACKWARD);
  motorEsqT.run(BACKWARD);
  motorDirF.run(FORWARD);
  motorDirT.run(FORWARD);
}

void parar() {
  motorEsqF.run(RELEASE);
  motorEsqT.run(RELEASE);
  motorDirF.run(RELEASE);
  motorDirT.run(RELEASE);
}

void seguirparede() {

  esquerda = ultrasonic1.convert(ultrasonic1.timing(), Ultrasonic::CM);
  frente = ultrasonic2.convert(ultrasonic2.timing(), Ultrasonic::CM);
  direita = ultrasonic3.convert(ultrasonic3.timing(), Ultrasonic::CM);
  //  Serial.print("Esq: ");
  //  Serial.print(esquerda);
  //  Serial.print(" Frente: ");
  //  Serial.print(frente);
  //  Serial.print(" Dir: ");
  //  Serial.println(direita);
  //  delay(100);


  forward();
  if (frente > 20) // Caso exista caminho livre em frente:
  {
    if (direita >= 12  && direita <= 15) // se a distância à direita estiver entre 9 e 12 cm, o robô mantém-se em linha reta;
    {
      mspeed = 80;
      motorEsqF.setSpeed(mspeed);
      motorEsqT.setSpeed(mspeed);
      motorDirF.setSpeed(mspeed);
      motorDirT.setSpeed(mspeed);

      //Serial.println("Estou a andar em frente");
    }
    if (direita > 15 && direita < 25) // se a distância à direita for maior que 12 cm e menor que 25cm, o robô aumenta
      // a velocidade dos motores da esquerda para se aproximar da parede direita;
    {
      motorEsqF.setSpeed(80);
      motorEsqT.setSpeed(80);
      motorDirF.setSpeed(40);
      motorDirT.setSpeed(40);

      // Serial.println("Estou a aproximar da parede");
    }
    if (direita >= 25 && direita < 40) {
      motorEsqF.setSpeed(150);
      motorEsqT.setSpeed(150);
      motorDirF.setSpeed(0);
      motorDirT.setSpeed(0);
    }
    if (direita >= 40) // se a distância à direita for maior que 25 cm, o robô aumenta
      // ainda mais a velocidade dos motores da esquerda para se aproximar da parede direita;
    {
      if (ofrente == 1) {
        delay(50);
        frente = 0;
      }
      motorEsqF.setSpeed(150);
      motorEsqT.setSpeed(150);
      motorDirF.setSpeed(60);
      motorDirT.setSpeed(60);
      right();
      //Serial.println("Estou a aproximar da parede");
    }

    if (direita < 12) // se a distância à direita for menor que 9 cm, o robô aumenta
      // a velocidade do motor direito para se distanciar da parede direita;
    {

      motorEsqF.setSpeed(0);
      motorEsqT.setSpeed(0);
      motorDirF.setSpeed(150);
      motorDirT.setSpeed(150);

      // Serial.println("Estou a afastar da parede");
    }
  } else { // Caso não exista caminho livre em frente:
    //Se o caminho não estiver livre à frente e à esquerda
    if (direita <= 20 && esquerda > 20) {
      motorEsqF.setSpeed(60);
      motorEsqT.setSpeed(60);
      motorDirF.setSpeed(150);
      motorDirT.setSpeed(150);
      left();
      delay(500);
      ofrente = 1;
    }
    //Se o caminho não estiver livre à frente e à direita
    if (esquerda <= 20 && direita > 20) {
      motorEsqF.setSpeed(150);
      motorEsqT.setSpeed(150);
      motorDirF.setSpeed(60);
      motorDirT.setSpeed(60);
      right();
    }
    //Se o caminho não estiver livre à frente, à direita e à esquerda
    if (direita <= 20 && esquerda <= 20) {
      motorEsqF.setSpeed(60);
      motorEsqT.setSpeed(60);
      motorDirF.setSpeed(150);
      motorDirT.setSpeed(150);
      left();
    }
  }

}
