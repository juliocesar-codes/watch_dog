# IOT Watch Dog

Projeto da matéria de IOT, criando um sistema que detecta se o Wi-Fi está ligado ou não, utilizando o arduino ESP32, projeto feito individual

### 📋 Código do Projeto

Siga o código que utilizei para fazer o sistema funcionar

```
const int PINO_TRIG = 33;
const int PINO_ECHO = 32;
const int PINO_LED_INTRUSO = 25;

float obter_distancia();

void setup() {

  Serial.begin(115200);
  pinMode(PINO_TRIG, OUTPUT);
  pinMode(PINO_ECHO, INPUT);
  pinMode(PINO_LED_INTRUSO, OUTPUT);
  digitalWrite(PINO_TRIG, LOW);

}

void loop() {

  float dist = obter_distancia();

  Serial.print("Distância :");
  Serial.print(dist);
  Serial.println(" cm");

  if(dist > 0 && dist <= 10){
    Serial.println("Intruso detectado!");
    digitalWrite(PINO_LED_INTRUSO, HIGH);
    delay(500);
  }else{
    Serial.println("Ambiente seguro");
    digitalWrite(PINO_LED_INTRUSO, LOW);
  }
  delay(500);
}

float obter_distancia(){

  digitalWrite(PINO_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PINO_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PINO_TRIG, LOW);
  long duracao = pulseIn(PINO_ECHO, HIGH, 30000);
  float distancia = (duracao/2.0) * 0.0343;
  
  return distancia;

}

```

## Demonstração em Vídeo
* [Clique Aqui](https://drive.google.com/file/d/1mB5TDDsJA-hbIklEdpMaZEIjnqbn4fi-/view?usp=sharing) - Vídeo do sistema funcionando

## Software Utilizado

* [Arduino](https://www.arduino.cc/en/software/) - Software que fui utilizado para criação do sistema
