// Gabriel Pantoja (190107227) e Rafael Brasileiro (190044110)
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

//Endereço em hexadecimal do sensor MPU 6050
const int ENDERECO_SENSOR=0x68;
MPU6050 mpu(ENDERECO_SENSOR);

//int acelX,acelY,acelZ;
int ax, ay, az;
float accel_ang_x;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
}

void loop() 
{
  //Começa uma transmissão com o sensor
  Wire.beginTransmission(ENDERECO_SENSOR);

  //Enfilera os bytes que vão ser transmitidos para o sensor
  Wire.write(0x3B);  //Começando com o registor 0x3B

  //Finaliza e transmite os dados para o sensor. O false fará com que seja enviado uma mensagem de restart e o barramento não será liberado
  Wire.endTransmission(false);
  
  //Solicita os dados do sensor em 14 bytes, o true fará com que o barramento seja liberado após a solicitação (o valor padrão deste parâmetro é true)
  Wire.requestFrom(ENDERECO_SENSOR, 14, true);
  //Armazena o valor dos sensores nas variaveis correspondentes
  ax = Wire.read()<<8|Wire.read();    
  ay = Wire.read()<<8|Wire.read();    
  az = Wire.read()<<8|Wire.read();    

  //Calcular os angulos de inclinação

  //Se estiver no 1°quadrante
  if((ax > 0) & (ay > 0)){
      accel_ang_x = atan(ax / sqrt(pow(ay, 2) + pow(az, 2)))*(180.0 / 3.14);
  }
  //Se estiver no 2°quadrante
  if((ax > 0) & (ay < 0)){
      accel_ang_x = 180 - atan(ax / sqrt(pow(ay, 2) + pow(az, 2)))*(180.0 / 3.14);
  }
  //Se estiver no 3°quadrante
  if((ax < 0) & (ay > 0)){
      accel_ang_x =  atan(ax / sqrt(pow(ay, 2) + pow(az, 2)))*(180.0 / 3.14)+360;
  }
  //Se estiver no 4°quadrante
  if((ax < 0) & (ay < 0)){
      accel_ang_x = 180 - atan(ax / sqrt(pow(ay, 2) + pow(az, 2)))*(180.0 / 3.14);
  }
  
  // Mostrar resultados
  //Imprime o valor X do acelerômetro
  Serial.print("Acelerômetro X = "); 
  Serial.print(ax);
 
  //Imprime o valor Y do acelerômetro
  Serial.print(" \tY = "); 
  Serial.print(ay);
   
  //Imprime o valor Z do acelerômetro
  Serial.print(" \tZ = "); 
  Serial.println(az);

  //Imprime o valor de Ângulo Calculado em X
  Serial.print(F("Ângulo no eixo X: "));
  Serial.println(accel_ang_x);
  delay(10);
}
