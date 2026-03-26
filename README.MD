# IOT Watch Dog

Projeto da matéria de IOT, criando um sistema que detecta se o Wi-Fi está ligado ou não, utilizando o arduino ESP32, projeto feito individual

### 📋 Código do Projeto

Siga o código que utilizei para fazer o sistema funcionar

```
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

// Credenciais da rede industrial 
const char* ssid = "A54 de Julio";
const char* password = "Julio12345678";

// Configuração dos pinos
const int PINO_LED_VERDE = 18;
const int PINO_LED_VERMELHO = 19;

const char* serverName = "https://jsonplaceholder.typicode.com/todos/1";

void setup(){
  Serial.begin(115200);

  pinMode(PINO_LED_VERDE, OUTPUT);
  pinMode(PINO_LED_VERMELHO, OUTPUT);

  // Inicia conexão como Station
  WiFi.begin(ssid, password);
  Serial.print("Conectando a: ");
  Serial.println(ssid);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado com sucesso!");
}

void loop(){
  // Verifica conexão a cada 10 segundos
  if(WiFi.status() == WL_CONNECTED){
    // Criamos o obejto cliente seguro
    WiFiClientSecure *client = new WiFiClientSecure;

    if(client){
      client ->setInsecure();

      HTTPClient https;

      Serial.print("[HTTPS] Iniciando requisição...\n");

      if(https.begin(*client, serverName)) {
        // Realiza o GET
        int httpCode = https.GET();

        // httpCode será positivo se o servidor responder 
        if(httpCode > 0){
          Serial.printf("[HTTPS] Código de resposta: %d\n", httpCode);

          if(httpCode == HTTP_CODE_OK){
            String payload = https.getString();
            Serial.println("Conteúdo recebido:");
            Serial.println(payload);
            digitalWrite(PINO_LED_VERDE, HIGH);
            digitalWrite(PINO_LED_VERMELHO, LOW);
            
          }
        }else{
          Serial.printf("[HTTPS] Falha na requisição, erro: %s\n", https.errorToString(httpCode).c_str());
        }

        https.end();
      } else{
        Serial.printf("[HTTPS] Não foi possível conectar ao servidor\n");
      }
      delete client;
    }
  }else{
    Serial.println("Reconectando...");
    WiFi.reconnect();
    digitalWrite(PINO_LED_VERDE, LOW);
    digitalWrite(PINO_LED_VERMELHO, HIGH);
  }

  delay(15000);
}
```

## Demonstração em Vídeo
* [Clique Aqui](https://drive.google.com/file/d/1mB5TDDsJA-hbIklEdpMaZEIjnqbn4fi-/view?usp=sharing) - Vídeo do sistema funcionando

## Software Utilizado

* [Arduino](https://www.arduino.cc/en/software/) - Software que fui utilizado para criação do sistema
