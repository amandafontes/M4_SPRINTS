// Declarando os pinos nos quais se conectam os LEDs, botões, LDR e buzzer

#define ledVerde 3
#define ledAmarelo 17
#define ledAzul 7
#define ledVermelho 4
#define botao1 19
#define botao2 20
#define ldr 21
#define buzzer 2

int binario[4]; // Variável que armazena os 4 dígitos que compõem o número convertido para binário
int frequencias[100]; // Variável que armazena cada frequência com a qual o buzzer irá tocar
// A cada vez que o primeiro botão é apertado, a leitura do LDR convertida é armazenada nessa lista
int x = 0; // Variável referente às posições da lista "frequencias"

void setup() {

// Configurando o pinMode dos leds, LDR, botões e buzzer

  Serial.begin(115200);
  pinMode(ledAzul, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

}

// A função abaixo determina quais LEDs acenderão de acordo com cada número binário convertido por meio da leitura do LDR
// Em sequência, estarão os LEDs verde (que representa a unidade de milhar do número binário)
// Amarelo (que representa a centena), azul (que representa a dezena) e vermelho (representando a unidade)
// Há quatro possíveis dígitos no número binário. Se o valor da posição do binário for 1, o LED acende. Se for 0, ele fica apagado
// Isso significa que, se a leitura do LDR for 15, seu respectivo binário será 1111. Desse modo, todos os LEDs acenderão
// Por outro lado, se a leitura identificada for 4, teremos o binário 100. Assim, o primeiro LED fica apagado, o segundo LED acende, e o terceiro e quarto LEDs não acendem.

void leds() {

  if (binario[0] == 0) { // Posição 0, referente ao LED verde
      digitalWrite(ledVerde, LOW); // Impõe estado "low" ao LED, portanto, ele permanece apagado
    } else {
      digitalWrite(ledVerde, HIGH); // Impõe estado "low" ao LED, portanto, ele permanece aceso
    }

    if (binario[1] == 0) { // Posição 1, referente ao LED amarelo
      digitalWrite(ledAmarelo, LOW);
    } else {
      digitalWrite(ledAmarelo, HIGH);
    }

    if (binario[2] == 0) { // Posição 2, referente ao LED azul
      digitalWrite(ledAzul, LOW);
    } else {
      digitalWrite(ledAzul, HIGH);
    }

    if (binario[3] == 0) { // Posição 3, referente ao LED vermelho
      digitalWrite(ledVermelho, LOW);
    } else {
      digitalWrite(ledVermelho, HIGH);
    }
}

// A função abaixo será responsável por converter o valor da leitura do LDR para número binário

void converter(int valor) {

  for (int i = 0; i <= 3; i++) { // Realiza um loop responsável por preencher as quatro posições do binário, o qual será armazenado em uma lista

    if (valor >= 1) { // O valor inserido se refere à leitura do LDR. Se for maior que 1, entra na lógica de conversão binária

      binario[i] = valor % 2; // A lista "binario", que recebe os dígitos do número binário, recebe o módulo da divisão da leitura do LDR por 2
      valor = valor / 2; // Para retomar o loop enquanto o valor for superior a 1, divide esse valor por 2, dando continuidade à lógica da conversão binária

    } else {

      binario[i] = 0; // Se o valor lido pelo LDR for correspondente a 0, sua respectiva posição na lista receberá zero

    }
  }
}

// Função que realiza em loop os comandos necessários

void loop() {

  int leituraLDR = analogRead(ldr); // O comando "analogRead" será responsável por realizar a leitura do sensor de luminosidade (LDR)
  // O valor lido será armazenado na variável "leituraLDR", a qual será, posteriormente, convertida para número binário


  // O exercício requer que o número binário tenha até quatro dígitos. Essa condição só é satisfeita para os decimais que vão de 0 a 15
  // Assim, é necessário obter os valores máximo e mínimo lidos pelo sensor e convertê-los para 15 intervalos
  // Desse modo, a leitura do LDR passará a ler valores de 0 a 15. Esse processo é realizado pelo cálculo abaixo:
  int leituraLDRConvertida = leituraLDR / 257; // Armazenamos esses valores na variável "leituraLDRConvertida"

  // O valor "257" serve para a conversão em intervalos de 0 a 15 somente no componente LDR quando conectado à placa ESP32

  converter(leituraLDRConvertida); // Aqui, chamamos a função "converter", que tem como parâmetro o valor convertido da leitura do LDR
  // A função, explicada acima, converte esse número (que estará entre 0 e 15) para número binário

  leds(); // Agora, chamamos a função "leds", que irá fazer os leds piscarem de acordo com cada número binário resultante da conversão do valor lido pelo sensor de luminosidade

  if (digitalRead(botao1) == LOW) { // A cada vez que o primeiro botão for pressionado, será feita a leitura do LDR
  // Consequentemente, teremos o a frequência com a qual o buzzer irá tocar

    frequencias[x] = leituraLDRConvertida; // Esses valores serão armazenados na lista "frequencias"
    tone(buzzer, frequencias[x]*100, 350); // O comando "tone" faz com que o buzzer emita o som relativo a cada frequência armazenada
    Serial.println(frequencias[x]); // Aqui, estamos exibindo, no Serial Monitor, cada posição armazenada em "frequencias" (valores que podem variar de 0 a 15)
    x += 1; // A cada vez que o botão é apertado, será exibido o próximo valor de x, ou seja, a próxima posição da lista "frequencias"
    delay(50); // Aqui, colocamos um delay de 50 milissegundos para que os LEDs acendam em concordância com a emissão do buzzer
  }

  if (digitalRead(botao2) == LOW) { // Quando o segundo botão for pressionado é que entrará em funcionamento o "instrumento musical"
  // O objetivo é que o buzzer emita sons de todas as frequências armazenadas na lista, sequencialmente e em sincronia com os LEDs

    while (x >= 0) { // Loop para emitir todos os sons enquanto são percorridos os elementos da lista "frequencias"
      tone(buzzer, frequencias[x]*100, 350); // Comando para acionar o buzzer na frequência relativa a cada posição da lista
      converter(frequencias[x]); // Conversão realizada para, novamente, transformar em número binário cada valor compreendido no intervalo de 0 a 15
      delay(500); // Delay de 500 milissegundos para que haja sincronia entre os sons emitidos e os LEDs
      leds(); // Novamente, é chamada a função "leds", de modo que eles acendam ou apaguem de acordo com o número binário encontrado para cada leitura do LDR

      Serial.println(frequencias[x]*100); // Aqui, estamos exibindo no Serial Monitor cada frequência emitida pelo buzzer enquanto ele toca

      x = x-1; // Para a continuação do loop. Indica que todos os elementos de "frequencias" serão percorridos, de modo que o buzzer emita todos os sons em concordância com os LEDs
    }
  }
  delay(50); // Novamente, inserimos um delay para evitar possíveis falhas de sincronia
}