/*==========================================================================================
                             C O M P U T A Ç Ã O   N A   E S C O L A
                             ---  Software de Apoio ao Professor ---

Sketch de configuração para operação wireless com Scratch via s2a_fm de Módulos Bluetooth 
HC-05 e outros que utilizam comandos Hayes terminados com CR+LF.

Comandos Hayes ou Comandos-AT é uma linguagem de configuração de modems originalmente 
desenvolvida em 1981 para o Hayes Smartmodem de 300 bps da hoje extinta Hayes Microcomputer 
Products. Todo comando Hayes é formado por "AT" (significando "attention!") um ligador "+" e
uma palavra-chave seguida ou não de parâmetros. 
Mais infos aqui: http://en.wikipedia.org/wiki/Hayes_command_set

Comandos Hayes utilizados para configurar o módulo Bluetooth:
AT+NAME=ARDUINO**
AT+UART=57600,0,0
onde ** é o número do módulo que você vai determinar.

INSTRUÇÕES DE USO:

Para gravar este program em um Arduino:
1. Grave o sketch no Arduino antes de fazer as conexões do diagrama.
2. Desligue o Arduino (desconecte da porta USB).

Para começar a usar:
1. Conecte Arduino ao protoboard ou ao HC-05 conforme diagrama.
2. Conecte o Arduino à porta USB do seu computador.
3. Abra o Monitor Serial, configurando a sua velocidade para 9600 baud e o fim de linha para NL e CR.
4. Siga as instruções que forem aparecendo no monitor serial, entrando os parâmetros na caixinha de entrada, acima.

Para programar outro HC-05:
0. Não há necesidade de desligar ou desconectar o Arduino.
1. Desconecte o cabo de enregia (vermelho) do HC-05 do pino +5V do Arduino.
2. Desconecte-o do protoboard.
3. Conecte um novo HC-05.
4. Conecte o cabo de energia de volta ao pino +5V do Arduino.
5. IMPORTANTE -> Aperte o botão de reset do Arduino.
6. Siga as instruções que forem aparecendo no monitor serial, entrando os parâmetros na caixinha de entrada, acima.

====================================
CONEXÕES DO MODULO BLUETOOTH
KEY   : PINO 9    (fio LARANJA)
VCC   : PINO +5v  (fio VERMELHO)
GND   : PINO GND  (fio PRETO)
TXD   : PINO 10   (fio VERDE)
RXD   : PINO 11   (fio AMARELO)

AUTOR: Aldo von Wangenheim - INCoD/UFSC
DATA: 20/06/2014

Baseado em parte no código "HC-05-Modify The HC-05 Bluetooth Module Defaults Using AT Commands" de:
AUTHOR: Hazim Bitar (techbitar)
DATE: Aug 29, 2013
LICENSE: Public domain (use at your own risk)
CONTACT: techbitar at gmail dot com (techbitar.com)
disponível em: http://www.instructables.com/id/Modify-The-HC-05-Bluetooth-Module-Defaults-Using-A/?ALLSTEPS

==========================================================================================*/


#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX

void setup()
{
  pinMode(13, OUTPUT);    // Vamos usar LED onboard como sinalizador de comunicação
  pinMode(9, OUTPUT);     // Pino para acionar o modo de configuracao (pino KEY do módulo)
  digitalWrite(9, HIGH);  // Ativar modo de configuracao para aceitar comandos Hayes
  Serial.begin(38400);
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
  delay(1000);
  Serial.println("Entre com Comandos Hayes:");
}


void loop()
{

  // Leia a saída do HC-05 and envie ao Monitor Serial do Arduino 
  if (BTSerial.available()){
    digitalWrite(13, HIGH);
    Serial.write(BTSerial.read());
    digitalWrite(13, LOW);
  }

  // Leia o que foi digitado no Monitor Serial do Arduino e envie ao HC-05
  if (Serial.available()){
    digitalWrite(13, HIGH);
    BTSerial.write(Serial.read());
    digitalWrite(13, LOW);
  }
}
