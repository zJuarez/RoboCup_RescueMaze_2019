  #include "MotoresPuentes.h"

double Kp=2, Ki=0, Kd=0;
double Input=0, Output=0, Setpoint=0;
double Kp2=2, Ki2=0, Kd2=0;
double Input2=0, Output2=0, Setpoint2=6;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, REVERSE);
PID myPID2(&Input2, &Output2, &Setpoint2, Kp2, Ki2, Kd2, REVERSE);

double velocidadBaseIzqAde=200;
double velocidadBaseIzqAtras=200;
double velocidadBaseDerAde=250;
double velocidadBaseDerAtras=250;




MotoresPuentes::MotoresPuentes(){
bno = Adafruit_BNO055();
}

void MotoresPuentes::setup(){

    if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
   delay(1000);
  bno.setExtCrystalUse(true);
  Input;
  Setpoint;
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  pinMode(motorIzqAde1, OUTPUT);
  pinMode(motorIzqAde2, OUTPUT);
  pinMode(motorIzqAtras1, OUTPUT);
  pinMode(motorIzqAtras2, OUTPUT);
  pinMode(motorDerAde1, OUTPUT);
  pinMode(motorDerAde2, OUTPUT);
  pinMode(motorDerAtras1, OUTPUT);
  pinMode(motorDerAtras2, OUTPUT);
}
void MotoresPuentes::actualizaSetpoint(){
    double med=0;
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    Serial.print("X: ");
    med=euler.x();
    Setpoint=med;
    Serial.println(med);
    delay(BNO055_SAMPLERATE_DELAY_MS);
}
void MotoresPuentes::moveAdelante(){
    double med=0;
    double velocidadIzqAde, velocidadIzqAtras, velocidadDerAde, velocidadDerAtras;
    velocidadIzqAde=velocidadBaseIzqAde;
    velocidadIzqAtras=velocidadBaseIzqAtras;
    velocidadDerAde=velocidadBaseDerAde;
    velocidadDerAtras=velocidadBaseDerAtras;
//TODAVI NO SE SABEN LAS POSICIONES CORRECTAS.......
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    Serial.print("X: ");
    med=euler.x();
    Serial.println(Setpoint);
    delay(BNO055_SAMPLERATE_DELAY_MS);
    Input=med;
    myPID.Compute();
    if(Input-Setpoint>1 || Input-Setpoint <-1){
        if(Input-Setpoint>0){
         //MOVE DERECHA
            digitalWrite(motorIzqAde1, LOW);
            analogWrite(motorIzqAde2, velocidadIzqAde+Output);
            digitalWrite(motorIzqAtras1, LOW);
            analogWrite(motorIzqAtras2, velocidadIzqAtras+Output);
            digitalWrite(motorDerAde1, LOW);
            analogWrite(motorDerAde2, velocidadDerAde-Output);
            digitalWrite(motorDerAtras1, LOW);
            analogWrite(motorDerAtras2, velocidadDerAtras-Output);
        }
        else if(Input-Setpoint<0){
            //MOVE IZQUIERDA
            digitalWrite(motorIzqAde1, LOW);
            analogWrite(motorIzqAde2, velocidadIzqAde-Output);
            digitalWrite(motorIzqAtras1, LOW);
            analogWrite(motorIzqAtras2, velocidadIzqAtras-Output);
            digitalWrite(motorDerAde1, LOW);
            analogWrite(motorDerAde2, velocidadDerAde+Output);
            digitalWrite(motorDerAtras1, LOW);
            analogWrite(motorDerAtras2, velocidadDerAtras+Output);
        }
    }
    else{
            digitalWrite(motorIzqAde1, LOW);
            analogWrite(motorIzqAde2, velocidadIzqAde);
            digitalWrite(motorIzqAtras1, LOW);
            analogWrite(motorIzqAtras2, velocidadIzqAtras);
            digitalWrite(motorDerAde1, LOW);
            analogWrite(motorDerAde2, velocidadDerAde);
            digitalWrite(motorDerAtras1, LOW);
            analogWrite(motorDerAtras2, velocidadDerAtras);
    }
/*
    MotorAtrasDer->setSpeed(210);
    MotorAtrasDer->run(FORWARD);
    MotorAtrasIzq->setSpeed(235);
    MotorAtrasIzq->run(FORWARD);
    MotorAdeIzq->setSpeed(235);
    MotorAdeIzq->run(BACKWARD);
    MotorAdeDer->setSpeed(210);
    MotorAdeDer->run(BACKWARD);
*/
}
/*
void MotoresPuentes::moveAdelanteLento(){
    uint8_t i=235;
//TODAVI NO SE SABEN LAS POSICIONES CORRECTAS.......
digitalWrite(motorIzqAde1, LOW);
analogWrite(motorIzqAde2, i);
digitalWrite(motorIzqAtras1, LOW);
analogWrite(motorIzqAtras2, i);
digitalWrite(motorDerAde1, LOW);
analogWrite(motorDerAde2, i);
digitalWrite(motorDerAtras1, LOW);
analogWrite(motorDerAtras2, i);

    MotorAtrasDer->setSpeed(50);
    MotorAtrasDer->run(FORWARD);
    MotorAtrasIzq->setSpeed(50);
    MotorAtrasIzq->run(FORWARD);
    MotorAdeIzq->setSpeed(50);
    MotorAdeIzq->run(BACKWARD);
    MotorAdeDer->setSpeed(50);
    MotorAdeDer->run(BACKWARD);

}
*/

void MotoresPuentes::acomodoD()
{
  uint8_t i=235;
//TODAVI NO SE SABEN LAS POSICIONES CORRECTAS.......
digitalWrite(motorIzqAde1, LOW);
analogWrite(motorIzqAde2, 50);
digitalWrite(motorIzqAtras1, LOW);
analogWrite(motorIzqAtras2, 50);
digitalWrite(motorDerAde1, LOW);
analogWrite(motorDerAde2, 170);
digitalWrite(motorDerAtras1, LOW);
analogWrite(motorDerAtras2, 170);
/*
    MotorAtrasDer->setSpeed(170);
    MotorAtrasDer->run(FORWARD);
    MotorAtrasIzq->setSpeed(50);
    MotorAtrasIzq->run(FORWARD);
    MotorAdeIzq->setSpeed(50);
    MotorAdeIzq->run(BACKWARD);
    MotorAdeDer->setSpeed(170);
    MotorAdeDer->run(BACKWARD);
    */
}
void MotoresPuentes::acomodoI()
{
 uint8_t i=235;
//TODAVI NO SE SABEN LAS POSICIONES CORRECTAS.......
digitalWrite(motorIzqAde1, LOW);
analogWrite(motorIzqAde2, 170);
digitalWrite(motorIzqAtras1, LOW);
analogWrite(motorIzqAtras2, 170);
digitalWrite(motorDerAde1, LOW);
analogWrite(motorDerAde2, 50);
digitalWrite(motorDerAtras1, LOW);
analogWrite(motorDerAtras2, 50);
/*
  MotorAtrasDer->setSpeed(50);
    MotorAtrasDer->run(FORWARD);
    MotorAtrasIzq->setSpeed(170);
    MotorAtrasIzq->run(FORWARD);
    MotorAdeIzq->setSpeed(170);
    MotorAdeIzq->run(BACKWARD);
    MotorAdeDer->setSpeed(50);
    MotorAdeDer->run(BACKWARD);
    */
}
void MotoresPuentes::detenerse(){
  uint8_t i=235;
//TODAVI NO SE SABEN LAS POSICIONES CORRECTAS.......
digitalWrite(motorIzqAde1, LOW);
digitalWrite(motorIzqAde2, LOW);
digitalWrite(motorIzqAtras1, LOW);
digitalWrite(motorIzqAtras2, LOW);
digitalWrite(motorDerAde1, LOW);
digitalWrite(motorDerAde2, LOW);
digitalWrite(motorDerAtras1, LOW);
digitalWrite(motorDerAtras2, LOW);
}
void MotoresPuentes::moveAtras(){
uint8_t i;
//TODAVI NO SE SABEN LAS POSICIONES CORRECTAS.......

digitalWrite(motorIzqAde2, LOW);
analogWrite(motorIzqAde1, velocidadBaseIzqAde);
digitalWrite(motorIzqAtras2, LOW);
analogWrite(motorIzqAtras1, velocidadBaseIzqAtras);
digitalWrite(motorDerAde2, LOW);
analogWrite(motorDerAde1, velocidadBaseDerAde);
digitalWrite(motorDerAtras2, LOW);
analogWrite(motorDerAtras1, velocidadBaseDerAtras);
/*
    MotorAtrasDer->setSpeed(210);
    MotorAtrasDer->run(BACKWARD);
    MotorAtrasIzq->setSpeed(235);
    MotorAtrasIzq->run(BACKWARD);
    MotorAdeIzq->setSpeed(235);
    MotorAdeIzq->run(FORWARD);
    MotorAdeDer->setSpeed(210);
    MotorAdeDer->run(FORWARD);
    */
}
void MotoresPuentes::moveAtrasLento(){
 uint8_t i=235;
//TODAVI NO SE SABEN LAS POSICIONES CORRECTAS.......
digitalWrite(motorIzqAde1, LOW);
analogWrite(motorIzqAde2, 50);
digitalWrite(motorIzqAtras1, LOW);
analogWrite(motorIzqAtras2, 50);
digitalWrite(motorDerAde1, LOW);
analogWrite(motorDerAde2, 50);
digitalWrite(motorDerAtras1, LOW);
analogWrite(motorDerAtras2, 50);
/*
    MotorAtrasDer->setSpeed(50);
    MotorAtrasDer->run(BACKWARD);
    MotorAtrasIzq->setSpeed(50);
    MotorAtrasIzq->run(BACKWARD);
    MotorAdeIzq->setSpeed(50);
    MotorAdeIzq->run(FORWARD);
    MotorAdeDer->setSpeed(50);
    MotorAdeDer->run(FORWARD);
    */
}
void MotoresPuentes::moveIzq(){
uint8_t i;
double med=0, newMed=0, punto=0, newPunto=0, nOutput=0;

    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    Serial.print("X: ");
    med=euler.x();
    Serial.println(med);
    delay(BNO055_SAMPLERATE_DELAY_MS);

if(med<90){

    punto=med-82;
    newPunto=360+punto;
    Setpoint=newPunto;
    do{
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    Serial.print("X: ");
    newMed=euler.x();
    Input=newMed;
    Serial.println(newMed);
    delay(BNO055_SAMPLERATE_DELAY_MS);
    myPID.Compute();
    nOutput=Output+150;
    (nOutput>=255)? nOutput=255: nOutput=nOutput;
    Serial.println(nOutput);
    //analogWrite(PIN_OUTPUT, Output);

//TODAVI NO SE SABEN LAS POSICIONES CORRECTAS.......
digitalWrite(motorIzqAde2, LOW);
analogWrite(motorIzqAde1, nOutput);
digitalWrite(motorIzqAtras2, LOW);
analogWrite(motorIzqAtras1, nOutput);
digitalWrite(motorDerAde1, LOW);
analogWrite(motorDerAde2, nOutput);
digitalWrite(motorDerAtras1, LOW);
analogWrite(motorDerAtras2, nOutput);
    /*
    MotorAtrasDer->setSpeed(nOutput);
    MotorAtrasDer->run(BACKWARD);
    MotorAtrasIzq->setSpeed(nOutput);
    MotorAtrasIzq->run(FORWARD);
    MotorAdeIzq->setSpeed(nOutput);
    MotorAdeIzq->run(BACKWARD);
    MotorAdeDer->setSpeed(nOutput);
    MotorAdeDer->run(FORWARD);
    */
    }while(newMed<=med || newMed>newPunto);
  }
  else{
    punto=med-82;
    Setpoint=punto;
    do{
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    Serial.print("X: ");
    newMed=euler.x();
    Input=newMed;
    Serial.println(newMed);
    delay(BNO055_SAMPLERATE_DELAY_MS);
    myPID.Compute();
    nOutput=Output+150;
    (nOutput>=255)? nOutput=255: nOutput=nOutput;
    Serial.println(nOutput);
    //analogWrite(PIN_OUTPUT, Output);
    digitalWrite(motorIzqAde2, LOW);
    analogWrite(motorIzqAde1, nOutput);
    digitalWrite(motorIzqAtras2, LOW);
    analogWrite(motorIzqAtras1, nOutput);
    digitalWrite(motorDerAde1, LOW);
    analogWrite(motorDerAde2, nOutput);
    digitalWrite(motorDerAtras1, LOW);
    analogWrite(motorDerAtras2, nOutput);
    /*
    MotorAtrasDer->setSpeed(nOutput);
    MotorAtrasDer->run(BACKWARD);
    MotorAtrasIzq->setSpeed(nOutput);
    MotorAtrasIzq->run(FORWARD);
    MotorAdeIzq->setSpeed(nOutput);
    MotorAdeIzq->run(BACKWARD);
    MotorAdeDer->setSpeed(nOutput);
    MotorAdeDer->run(FORWARD);
    */
    }while(newMed>punto);
  }
  Serial.println("YA SALIO********");
  digitalWrite(motorIzqAde1, LOW);
analogWrite(motorIzqAde2, LOW);
digitalWrite(motorIzqAtras1, LOW);
analogWrite(motorIzqAtras2, LOW);
digitalWrite(motorDerAde1, LOW);
analogWrite(motorDerAde2, LOW);
digitalWrite(motorDerAtras1, LOW);
analogWrite(motorDerAtras2, LOW);
}

void MotoresPuentes::moveDer(){
uint8_t i;
double med=0, newMed=0, punto=0, newPunto=0, nOutput=0;

    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    Serial.print("X: ");
    med=euler.x();
    Serial.println(med);
    delay(BNO055_SAMPLERATE_DELAY_MS);

    if(med>=270){

    punto=med+82;
    newPunto=(360-punto)*-1;
    Setpoint=newPunto;
    do{
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    Serial.print("X: ");
    newMed=euler.x();
    Input=newMed;
    Serial.println(newMed);
    delay(BNO055_SAMPLERATE_DELAY_MS);
    myPID.Compute();
    nOutput=Output+150;
    (nOutput>=255)? nOutput=255: nOutput=nOutput;
    Serial.println(nOutput);
    //analogWrite(PIN_OUTPUT, Output);
    digitalWrite(motorIzqAde1, LOW);
    analogWrite(motorIzqAde2, nOutput);
    digitalWrite(motorIzqAtras1, LOW);
    analogWrite(motorIzqAtras2, nOutput);
    digitalWrite(motorDerAde2, LOW);
    analogWrite(motorDerAde1, nOutput);
    digitalWrite(motorDerAtras2, LOW);
    analogWrite(motorDerAtras1, nOutput);
    /*
    MotorAtrasDer->setSpeed(nOutput);
    MotorAtrasDer->run(FORWARD);
    MotorAtrasIzq->setSpeed(nOutput);
    MotorAtrasIzq->run(BACKWARD);
    MotorAdeIzq->setSpeed(nOutput);
    MotorAdeIzq->run(FORWARD);
    MotorAdeDer->setSpeed(nOutput);
    MotorAdeDer->run(BACKWARD);
    */
    }while(newMed>=med || newMed<newPunto);
  }
  else{
    punto=med+82;
    Setpoint=punto;
    do{
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    Serial.print("X: ");
    newMed=euler.x();
    Input=newMed;
    Serial.println(newMed);
    delay(BNO055_SAMPLERATE_DELAY_MS);
    myPID.Compute();
    nOutput=Output+150;
    (nOutput>=255)? nOutput=255: nOutput=nOutput;
    Serial.println(nOutput);
    //analogWrite(PIN_OUTPUT, Output);
    digitalWrite(motorIzqAde1, LOW);
    analogWrite(motorIzqAde2, nOutput);
    digitalWrite(motorIzqAtras1, LOW);
    analogWrite(motorIzqAtras2, nOutput);
    digitalWrite(motorDerAde2, LOW);
    analogWrite(motorDerAde1, nOutput);
    digitalWrite(motorDerAtras2, LOW);
    analogWrite(motorDerAtras1, nOutput);
    /*
    MotorAtrasDer->setSpeed(nOutput);
    MotorAtrasDer->run(FORWARD);
    MotorAtrasIzq->setSpeed(nOutput);
    MotorAtrasIzq->run(BACKWARD);
    MotorAdeIzq->setSpeed(nOutput);
    MotorAdeIzq->run(FORWARD);
    MotorAdeDer->setSpeed(nOutput);
    MotorAdeDer->run(BACKWARD);
    */
    }while(newMed<punto);
  }
  Serial.println("YA SALIO********");
   digitalWrite(motorIzqAde1, LOW);
analogWrite(motorIzqAde2, LOW);
digitalWrite(motorIzqAtras1, LOW);
analogWrite(motorIzqAtras2, LOW);
digitalWrite(motorDerAde1, LOW);
analogWrite(motorDerAde2, LOW);
digitalWrite(motorDerAtras1, LOW);
analogWrite(motorDerAtras2, LOW);
}
void MotoresPuentes::moveDerAcomodo(){
    uint8_t i=235;
//TODAVI NO SE SABEN LAS POSICIONES CORRECTAS.......
digitalWrite(motorIzqAde1, LOW);
analogWrite(motorIzqAde2, 80);
digitalWrite(motorIzqAtras1, LOW);
analogWrite(motorIzqAtras2, 80);
digitalWrite(motorDerAde1, LOW);
analogWrite(motorDerAde2, 80);
digitalWrite(motorDerAtras1, LOW);
analogWrite(motorDerAtras2, 80);
    /*
   MotorAtrasDer->setSpeed(80);
    MotorAtrasDer->run(FORWARD);
    MotorAtrasIzq->setSpeed(80);
    MotorAtrasIzq->run(BACKWARD);
    MotorAdeIzq->setSpeed(80);
    MotorAdeIzq->run(FORWARD);
    MotorAdeDer->setSpeed(80);
    MotorAdeDer->run(BACKWARD);
    */
}
void MotoresPuentes::moveIzqAcomodo(){
    uint8_t i=235;
//TODAVI NO SE SABEN LAS POSICIONES CORRECTAS.......
digitalWrite(motorIzqAde1, LOW);
analogWrite(motorIzqAde2, 80);
digitalWrite(motorIzqAtras1, LOW);
analogWrite(motorIzqAtras2, 80);
digitalWrite(motorDerAde1, LOW);
analogWrite(motorDerAde2, 80);
digitalWrite(motorDerAtras1, LOW);
analogWrite(motorDerAtras2, 80);
    /*
    MotorAtrasDer->setSpeed(80);
    MotorAtrasDer->run(BACKWARD);
    MotorAtrasIzq->setSpeed(80);
    MotorAtrasIzq->run(FORWARD);
    MotorAdeIzq->setSpeed(80);
    MotorAdeIzq->run(BACKWARD);
    MotorAdeDer->setSpeed(80);
    MotorAdeDer->run(FORWARD);
    */
}
