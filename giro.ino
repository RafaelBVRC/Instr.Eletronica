// Gabriel Pantoja (190107227) e Rafael Brasileiro (190044110)
#include <Wire.h>

#define MPU 0x68
 
//Conversão de giros para º/s
#define G_R 131.0 // 32768/250
 
//Valores RAW
int16_t ax, ay, az, GyX, GyY, GyZ;
 
//Angulos
float Acc[2];
float Gy[3];
float AnguloX;

String valores;

long tempo_prev;
float passo;

void setup()
{
Wire.beginTransmission(MPU);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
Serial.begin(9600);
}

void loop()
{
   //Ler os valores do Acelerometro da MPU
   Wire.beginTransmission(MPU);
   Wire.write(0x3B); //Escrever o registro em 0x3B - corresponde ao AcX
   Wire.endTransmission(false);
   Wire.requestFrom(MPU,6,true);   //A partir de 0x3B, são necessarios registros
   ax=Wire.read()<<8|Wire.read(); //Cada valor ocupa 2 registros
   ay=Wire.read()<<8|Wire.read();
   az=Wire.read()<<8|Wire.read();
 
   //Ler os valores do Giroscopio
   Wire.beginTransmission(MPU);
   Wire.write(0x43);
   Wire.endTransmission(false);
   Wire.requestFrom(MPU,6,true);   //A partir del 0x43, são necessarios 6 registros
   GyX=Wire.read()<<8|Wire.read(); //Cada valor ocupa 2 registros
   GyY=Wire.read()<<8|Wire.read();
   GyZ=Wire.read()<<8|Wire.read();
 
   //Calculo do ângulo do Giroscopio
   Gy[0] = GyX/G_R;
   Gy[1] = GyY/G_R;
   Gy[2] = GyZ/G_R;

   passo = (millis() - tempo_prev) / 1000.0;
   tempo_prev = millis();

  float angulo_inicial;
  //Se estiver no 1°quadrante
  if((ax > 0) & (ay > 0)){
      //Calculo para verificar o ângulo inicial a partir da aceleração
      angulo_inicial = atan(ax / sqrt(pow(ay, 2) + pow(az, 2)))*(180.0 / 3.14);
      if(angulo_inicial-1>0){
         AnguloX = angulo_inicial+Gy[0]*passo;
         angulo_inicial = AnguloX;
      }
     
  }
  //Se estiver no 2°quadrante
  if((ax > 0) & (ay < 0)){
      //Calculo para verificar o ângulo inicial a partir da aceleração
      angulo_inicial = atan(ax / sqrt(pow(ay, 2) + pow(az, 2)))*(180.0 / 3.14);
      if(angulo_inicial-1>0){
         AnguloX = angulo_inicial+Gy[0]*passo;
         angulo_inicial = AnguloX;
      }
      AnguloX = 180-AnguloX;
  }
  //Se estiver no 3°quadrante
  if((ax < 0) & (ay < 0)){
      //Calculo para verificar o angulo inicial a partir da aceleração
      angulo_inicial = 180 - atan(ax / sqrt(pow(ay, 2) + pow(az, 2)))*(180.0 / 3.14);
      if(angulo_inicial-1>0){
         AnguloX = (angulo_inicial+Gy[0]*passo);
         angulo_inicial = AnguloX;
      }
  }
  //Se estiver no 4°quadrante
  if((ax < 0) & (ay > 0)){
      //Calculo para verificar o angulo inicial a partir da aceleração
      angulo_inicial = atan(ax / sqrt(pow(ay, 2) + pow(az, 2)))*(180.0 / 3.14)+360;
      if(angulo_inicial-1>0){
         AnguloX = angulo_inicial+Gy[0]*passo;
         angulo_inicial = AnguloX;
      }
  }

   
  // Mostrar resultados
  //Imprime o valor do passo
  //Serial.print("Valor do passo = "); 
  //Serial.println(passo);

  //Imprime o valor do Giro no Eixo X
  //Serial.print("Giro no eixo X = "); 
  //Serial.println(Gy[0]);
 
  //Imprime o valor X do acelerômetro
  //Serial.print("Acelerômetro X = "); 
  //Serial.print(ax);
 
  //Imprime o valor Y do acelerômetro
  //Serial.print(" \tY = "); 
  //Serial.print(ay);
   
  //Imprime o valor Z do acelerômetro
  //Serial.print(" \tZ = "); 
  //Serial.println(az);
  
   //Imprime o valor de Ângulo Calculado em X
   Serial.print(F("Ângulo pelo cálculo do giro: "));
   Serial.println(AnguloX);
   Serial.print(F("Ângulo pelo cálculo de aceleração: "));
   Serial.println(angulo_inicial);
   delay(10);
}
