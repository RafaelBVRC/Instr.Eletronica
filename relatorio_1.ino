#include<Wire.h>

//Endereço em hexadecimal do sensor MPU 6050
const int ENDERECO_SENSOR=0x68;  

int giroX, giroY, giroZ, acelX, acelY, acelZ; 
float gForceX, gForceY, gForceZ, rotX, rotY, rotZ;

void setup()
{
  Serial.begin(9600);

  //Inicializa a biblioteca Wire
  Wire.begin();
  Wire.beginTransmission(ENDERECO_SENSOR);
  Wire.write(0x6B); 
   
  //Inicializa o sensor
  Wire.write(0); 
  Wire.endTransmission(true);
}
void loop()
{
  //Começa uma transmissão com o sensor
  Wire.beginTransmission(ENDERECO_SENSOR);

  //Enfilera os bytes que vão ser transmitidos para o sensor
  Wire.write(0x3B);  //Começando com o registor 0x3B

  //Finaliza e transmite os dados para o sensor. O false fará com que seja enviado uma mensagem 
  //de restart e o barramento não será liberado
  Wire.endTransmission(false);
  
  //Solicita os dados do sensor em 14 bytes, o true fará com que o barramento seja liberado após a solicitação 
  //(o valor padrão deste parâmetro é true)
  Wire.requestFrom(ENDERECO_SENSOR, 14, true);  

  
  
  //Armazena o valor dos sensores nas variaveis correspondentes
  acelX = Wire.read()<<8|Wire.read();    
  acelY = Wire.read()<<8|Wire.read();    
  acelZ = Wire.read()<<8|Wire.read();    

  //Fazer a conversão dos dados de aceleração pela divisão da sensibilidade
  gForceX = acelX / 16384.0;
  gForceY = acelY / 16384.0; 
  gForceZ = acelZ / 16384.0;

  //Armazena o valor dos sensores nas variaveis correspondentes
  giroX = Wire.read()<<8|Wire.read();
  giroY = Wire.read()<<8|Wire.read();
  giroZ = Wire.read()<<8|Wire.read();

  //Fazer a conversão dos dados de giro pela divisão da sensibilidade
  rotX = giroX / 131.0;
  rotY = giroY / 131.0; 
  rotZ = giroZ / 131.0;
  
  
  //Imprime o valor X do acelerômetro
  Serial.print("Acelerômetro X = "); 
  Serial.print(acelX);
 
  //Imprime o valor Y do acelerômetro
  Serial.print(" \tY = "); 
  Serial.print(acelY);
   
  //Imprime o valor Z do acelerômetro
  Serial.print(" \tZ = "); 
  Serial.println(acelZ);

  //Imprime o valor X do acelerômetro convertido
  Serial.print("Acelerômetro convertido X = "); 
  Serial.print(gForceX);
 
  //Imprime o valor Y do acelerômetro convertido
  Serial.print(" \tY = "); 
  Serial.print(gForceY);
   
  //Imprime o valor Z do acelerômetro convertido
  Serial.print(" \tZ = "); 
  Serial.println(gForceZ);

  //Imprime o valor X do giroscópio
  Serial.print("Giroscópio X = "); 
  Serial.print(giroX);
  
  //Imprime o valor Y do giroscópio
  Serial.print(" \tY = "); 
  Serial.print(giroY); 
  
  //Imprime o valor Z do giroscópio
  Serial.print(" \tZ = "); 
  Serial.println(giroZ); 
  
  //Imprime o valor X do giroscópio convertido
  Serial.print("Giroscópio convertido X = "); 
  Serial.print(rotX);
  
  //Imprime o valor Y do giroscópio convertido
  Serial.print(" \tY = "); 
  Serial.print(rotY); 
  
  //Imprime o valor Z do giroscópio convertido
  Serial.print(" \tZ = "); 
  Serial.println(rotZ); 
  
  Serial.println("----------------------------------------------------------------"); //Divisoria pra cada leitura dos valores no monitor serial
   
  delay(200);
}
