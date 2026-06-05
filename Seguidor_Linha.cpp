// Controle do L298N
#define ENA 9     // PWM motor esquerdo
#define ENB 11    // PWM motor direito
#define IN1 8     // Direção motor esquerdo
#define IN2 10    // Direção motor direito

// Sensores infravermelho
#define pin_S1 7  // Sensor esquerdo
#define pin_S2 6  // Sensor direito

int velocidade = 150;
int curva = 80;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(pin_S1, INPUT);
  pinMode(pin_S2, INPUT);

  // Sentido dos motores: frente (ajustável se necessário)
  digitalWrite(IN1, HIGH); // ↔ Se o motor girar ao contrário, troque HIGH/LOW
  digitalWrite(IN2, HIGH);
}

void loop() {
  bool sensorEsq = digitalRead(pin_S1);  // HIGH = preto (linha)
  bool sensorDir = digitalRead(pin_S2);  // LOW = branco (fundo)

  if (sensorEsq == HIGH && sensorDir == HIGH) {
    // Ambos na linha → reto
    analogWrite(ENA, velocidade);
    analogWrite(ENB, velocidade);
  }
  else if (sensorEsq == HIGH && sensorDir == LOW) {
    // Linha à esquerda → curva à esquerda
    analogWrite(ENA, curva);
    analogWrite(ENB, velocidade);
  }
  else if (sensorEsq == LOW && sensorDir == HIGH) {
    // Linha à direita → curva à direita
    analogWrite(ENA, velocidade);
    analogWrite(ENB, curva);
  }
  else {
    // Ambos fora da linha → parar ou buscar
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
  }
}