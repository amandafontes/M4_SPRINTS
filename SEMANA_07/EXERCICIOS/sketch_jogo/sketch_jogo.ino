// Atribuindo as portas da ESP32 aos respectivos LEDs nas quais se conectam

#define ledVermelho 5 // LED vermelho conectado à porta 5
#define ledAzul 4 // LED azul conectado à porta 4
#define ledAmarelo 6 // LED amarelo conectado à porta 6

// Incluindo as biblitoecas auxiliares a fim de estabelecer conexão entre o microcontrolador e o servidor WEB

#include <WiFi.h>
#include <WebServer.h>

// Definindo o nome e a senha da rede WiFi que irá estabelecer comunicação entre ESP e servidor

const char* ssid = "";
const char* password = "";

WebServer server(80); // Definição da porta que o servidor irá utilizar (80, por padrão)

void jogadorX(){ // Função que deixa o LED vermelho aceso quando a vez for do jogador X
  server.send(200); // Método utilizado para responder a uma solicitação HTTP
  digitalWrite(ledVermelho, HIGH); // Acende LED vermelho
  digitalWrite(ledAzul, LOW); // Deixa apagado o LED azul
}

void jogadorO(){ // Função que deixa o LED azul aceso quando a vez for do jogador O
  server.send(200); // Método utilizado para responder a uma solicitação HTTP
  digitalWrite(ledAzul, HIGH); // Acende LED azul
  digitalWrite(ledVermelho, LOW); // Deixa apagado LED vermelho
}

void vencedorX(){ // Função que faz piscar o LED vermelho se o vencedor do jogo for X
  server.send(200); // Método utilizado para responder a uma solicitação HTTP

  digitalWrite(ledAzul, LOW); // Deixa apagado o LED azul, visto que o player O perdeu

  // Sequência que acende e apaga, por quatro vezes, o LED vermelho, com delay de 200 milissegundos

  digitalWrite(ledVermelho, HIGH);
  delay(200);
  digitalWrite(ledVermelho, LOW);
  delay(200);
  digitalWrite(ledVermelho, HIGH);
  delay(200);
  digitalWrite(ledVermelho, LOW);
  delay(200);
  digitalWrite(ledVermelho, HIGH);
  delay(200);
  digitalWrite(ledVermelho, LOW);
  delay(200);
  digitalWrite(ledVermelho, HIGH);
  delay(200);
  digitalWrite(ledVermelho, LOW);
}

void vencedorO(){ // Função que faz piscar o LED azul se o vencedor do jogo for O
  server.send(200); // Método utilizado para responder a uma solicitação HTTP

  digitalWrite(ledVermelho, LOW); // Deixa apagado o LED vermelho, visto que o player X perdeu

  // Sequência que acende e apaga, por quatro vezes, o LED azul, com delay de 200 milissegundos

  digitalWrite(ledAzul, HIGH);
  delay(200);
  digitalWrite(ledAzul, LOW);
  delay(200);
  digitalWrite(ledAzul, HIGH);
  delay(200);
  digitalWrite(ledAzul, LOW);
  delay(200);
  digitalWrite(ledAzul, HIGH);
  delay(200);
  digitalWrite(ledAzul, LOW);
  delay(200);
  digitalWrite(ledAzul, HIGH);
  delay(200);
  digitalWrite(ledAzul, LOW);
}

void empate(){ // Função que faz piscar o LED amarelo se houver empate no jogo
  server.send(200); // Método utilizado para responder a uma solicitação HTTP

  digitalWrite(ledAzul, LOW); // Deixa apagado o LED azul, visto que o player O não venceu o jogo
  digitalWrite(ledVermelho, LOW); // Deixa apagado o LED vermelho, visto que o player X não venceu o jogo

  // Sequência que acende e apaga, por quatro vezes, o LED amarelo, com delay de 200 milissegundos

  digitalWrite(ledAmarelo, HIGH);
  delay(200);
  digitalWrite(ledAmarelo, LOW);
  delay(200);
  digitalWrite(ledAmarelo, HIGH);
  delay(200);
  digitalWrite(ledAmarelo, LOW);
  delay(200);
  digitalWrite(ledAmarelo, HIGH);
  delay(200);
  digitalWrite(ledAmarelo, LOW);
  delay(200);
  digitalWrite(ledAmarelo, HIGH);
  delay(200);
  digitalWrite(ledAmarelo, LOW);
}

void setup() { // Configurações iniciais

  Serial.begin(115200); // O baud rate do Serial é inicializado em 115200
  
  pinMode(ledVermelho, OUTPUT); // Configurando saída para o led vermelho
  pinMode(ledAzul, OUTPUT); // Configurando saída para o led azul
  pinMode(ledAmarelo, OUTPUT); // Configurando saída para o led amarelo

  // Estabelecendo conexão à rede WiFi por meio do SSID e senha:

  Serial.print("Conectando à rede "); // Exibe no Serial Monitor a rede com a qual a ESP32 está tentando se conectar
  Serial.println(ssid);
  WiFi.begin(ssid, password); // Método utilizado para estabelecer a conexão

  while (WiFi.status() != WL_CONNECTED) { // Enquanto o WiFi estiver buscando a conexão, exibe "...."
    delay(500);
    Serial.print(".");
  }

  // Inicializando o servidor WEB:

  // Exibe no Serial Monitor que a placa está devidamente conectada à rede WiFi

  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP()); // Método que retorna o endereço de IP resultante da conexão

  // Abaixo, estabelecemos as rotas responsáveis pela execução de cada função correspondente
  // "server.on" é o método responsável por lidar com as solicitações HTTP recebidas

  server.on("/jogaX", jogadorX);
  server.on("/jogaO", jogadorO);
  server.on("/venceX", vencedorX);
  server.on("/venceO", vencedorO);
  server.on("/empate", empate);
  server.begin(); // Método utilizado para iniciar o servidor

}

// As solicitações HTTP recebidas são tratadas na função de loop. Para isso, utiliza-se o método "handleClient"

void loop() {
  server.handleClient();
}