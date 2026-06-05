# Robô Seguidor de Linha👾

![Arduino](https://img.shields.io/badge/Arduino-UNO-00979D?style=flat-square&logo=arduino&logoColor=white)
![Language](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)
 

Robô autonomo que **segue uma linha preta em um fundo branco**.Este projeto funciona com a seguinte lógica:

**Leitura** • Você lê o estado de cada sensor (por exemplo, com digitalRead()). • Cada sensor retorna “linha preta” ou “fundo branco” (pode ser HIGH ou LOW, depende do seu módulo).

**Interpretação** • Ambos veem branco → a faixa preta está entre os sensores, ou seja, o robô está no centro do caminho. • Só o esquerdo vê preto → a linha “bateu” no sensor esquerdo, o robô deslocou-se para direita da linha e precisa virar levemente para a esquerda. • Só o direito vê preto → o robô está deslocado para esquerda da linha e precisa virar levemente para a direita. • Ambos veem preto → o robô saiu totalmente da pista ou encontrou um cruzamento; a resposta mais simples é parar ou entrar numa rotina de busca.

**Ação** • No centro (branco/branco): mandar os dois motores com a mesma velocidade — segue reto. • Desvio para esquerda (esq=preto, dir=branco): reduzir a velocidade do motor esquerdo e manter (ou elevar) a do direito — curva suave para a esquerda. • Desvio para direita (esq=branco, dir=preto): reduzir a velocidade do motor direito e manter (ou elevar) a do esquerdo — curva suave para a direita. • Fora da linha (preto/preto): parar ambos motores para não perder controle.

Esse processo de “ler → interpretar → ajustar velocidades” acontece dezenas de vezes por segundo, garantindo que o robô fique sempre reagindo ao desvio com correções suaves.




## Lista de materiais⚙️

**1.** Arduino UNO (1x)

**2.** Ponte H dupla (1x)

**3.** Sensor de obstáculos reflexivo infravermelho (2x)

**4.** Suporte de pilhas (1x)

**5.** Pilha (4x)

**6.** Bateria de 9V (1x)

**7.** Motor (2x)

**8.** Chassi (1x)

<img width="512" height="377" alt="image" src="https://github.com/user-attachments/assets/66f523e7-364f-4c51-9062-e2275c99f38f" />


OBS: Também é necessário cabos jumper e ferramentas como chaves philips.

______________________________________________________________________________________________________________________________________________________________________

### Montagem

* Conecte as entradas digitais(Dx) aos IN's da ponte H dupla e ligue.

* As entradas de "sinal" dos sensores devem ser conectados aos pinos digitais do Arduino (D6 e D7).

* Ligue as entradas VCC e GNG dos sensores no VCC e GND do Arduino

* Ligue a "parte positiva" das pilhas no 12V da ponte H

* Ligue a "parte negativa" das pilhas no GND da ponte H

* Ligue os motores a ponte H (tome cuidado para não inverter as fases, muda o sentido do giro)

**OBS:** Verifique as conexões antes de alimentar o Arduino



## Conexões⚡


<img width="683" height="500" alt="image" src="https://github.com/user-attachments/assets/01542313-c367-44cb-8c88-fc9eec1c53e6" />





| Componente | Pino do Arduino |
|------------|-----------------|
| IN1       | D8              |
| IN2       | D9              |
| IN3       | D10              |
| IN4       | D11              |
| Sensor direito | D6              |
| Sensor esquerdo | D7              |

_____________________________________________________________________________________________________________________________________________________________


### Pinagem do sensor


<img width="512" height="377" alt="image" src="https://github.com/user-attachments/assets/37d43ddc-d296-42b0-bf51-9c68637fe5dd" />







Ligue as entradas VCC e GNG dos sensores no VCC e GND do Arduino(respectivamente).



## Código💻

```
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
```

caso o código apresente alguma falha, olhe as **entradas digitais** que estão sendo usadas, costma ser isso.


## Resultado❗



https://github.com/user-attachments/assets/6f975571-af58-4cbe-87cd-664b2785b8c8




## considerações

Quando for colocar o sensor no carrinho, se atente a distancia entre eles, para fazer a linha juntei duas fitas isolantes, ficou com 1.5CM de diametro (na média isso) e coloquei o sensor a 2.5CM um do outro. Caso não funcione vá testando outras distâncias, e recomendo usar uma fita barata ou canetão preto se a sua pista for de azulejo por exemplo.

### Referência

https://blog.eletrogate.com/robo-seguidor-de-linha-tutorial-completo/









