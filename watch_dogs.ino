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