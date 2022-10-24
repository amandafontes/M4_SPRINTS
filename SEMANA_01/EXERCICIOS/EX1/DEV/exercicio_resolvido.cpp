#include <iostream>
#include <string>

using namespace std;

char *direcoes[4] = {(char *)"frente",(char *)"trás",(char *)"esquerda",(char *)"direita"}; // A variável "direções" armazena as possíveis direções para as quais o robô poderá seguir

// INSTRUÇÃO 1 -  Faça uma função que recebe uma certa medida e ajusta ela percentualmente entre dois valores mínimo e máximo e retorna esse valor

int ajusteDeValores(int medida, int minimo, int maximo){ // Função que ajusta percentualmente a medida da entrada
    int variacao = maximo - minimo;
    medida = (medida - minimo) * 100 / variacao; // não precisamos do int nesse caso pois já está definido ali em cima!

    int resultado = medida;
    return resultado; // Retorno da medida já ajustada percentualmente
}

// INSTRUÇÃO 2 - Faça uma função que simule a leitura de um sensor lendo o valor do teclado ao final a função retorna este valor

int leituraDasDistancias(int indiceDirecao){ // Função de leitura dos valores de entrada, os quais correspondem à distância
    int valor;
    cout << "Digite a distância, em centímetros, até a " << direcoes[indiceDirecao]; // Solicita, a partir do sensor, a distância entre o robô e cada uma das possíveis direções
    cout << ": " ;
    cin >> valor; // Input referente ao valor das distâncias
    return valor; // Retorno do valor recebido
}

// INSTRUÇÃO 3 - Faça uma função que armazena uma medida inteira qualquer em um vetor fornecido.
// Note que como C não possui vetores nativos da linguagem, lembre-se que você precisa passar o 
// valor máximo do vetor assim como a última posição preenchida (a posição atual)
// Evite também que, por acidente, um valor seja escrito em uma área de memória fora do vetor

int armazenaValorVetor(int medida, int *vetor, int tamanhoMaximoVetor, int posicaoAtualDoVetor){ // Função responsável pelo armazenamento dos valores inseridos em um vetor
    if (posicaoAtualDoVetor < tamanhoMaximoVetor){ // Enquanto os valores armazenados respeitarem o tamanho máximo do vetor, insere as medidas
        vetor[posicaoAtualDoVetor] = medida;
        posicaoAtualDoVetor += 1; // Para percorrer as posições do vetor, inserindo as novas medidas
    }
    
    return posicaoAtualDoVetor; // Retorno da última posição do vetor
}

// INSTRUÇÃO 4 - Faça uma função que recebe um vetor com 4 posições que contém o valor da distância de um pequeno robô até cada um dos seus 4 lados.
// A função deve retornar duas informações: A primeira é a direção de maior distância ("Direita", "Esquerda", "Frente", "Tras") e a segunda é esta maior distância.

// Feito na função "leituraDasDistancias" e na função "dirige"

// 5 - Faça uma função que pergunta ao usuário se ele deseja continuar o mapeamento e retorna verdadeiro ou falso

int continuaMapeamento(){ // Função que pergunta ao usuário se ele deseja continuar ou interromper o mapeamento
	char resposta; // Variável na qual será armazenada a resposta do usuário
	cout << "Deseja continuar? (s/n) "; // Solicita o input do usuário em "s" (sim) ou "n" (não)
	cin >> resposta; // Recebe o valor inserido pelo usuário

	if (resposta == 's'){ // Se a resposta for "sim" (ou seja, o usuário deseja continuar o mapeamento), retorna 1, que indica "verdadeiro".
		return 1;
	} 
    else { // Se a resposta for "não" (ou seja, o usuário deseja interromper o mapeamento), retorna 0, que indica "falso".
		return 0;
	}
}

// INSTRUÇÃO 6 - A função abaixo (que está incompleta) vai "dirigindo" virtualmente um robô e através de 4 sensores em cada um dos 4 pontos do robo ("Direita", "Esquerda", 
// "Frente", "Tras"). 
//      A cada passo, ele verifica as distâncias aos objetos e vai mapeando o terreno 
// para uma movimentação futura. 
//      Ele vai armazenando estas distancias em um vetor fornecido como parâmetro e retorna a ultima posicao preenchida do vetor.
//      Esta função deve ir lendo os 4 sensores até que um comando de pare seja enviado 
//
//      Para simular os sensores e os comandos de pare, use as funções já construídas 
// nos ítens anteriores e em um looping contínuo até que um pedido de parada seja 
// enviado pelo usuário. 
//
//      Complete a função com a chamada das funções já criadas

int dirige(int *v,int maxv){ // Função responsável pela direção do robô
	int tamanhoMaximoVetor = maxv;
	int *vetorDeMovimentos = v;
	int posAtualVetor = 0;
	int dirigindo = 1;		

	while(dirigindo){ // Enquanto a função estiver em execução (ou seja, enquanto o usuário expressa que deseja continuar o mapeamento), executa os comandos abaixo
		for (int i = 0; i<4; i++) { // Percorre as quatro direções, uma a uma, lendo os valores de distância
			int medida = leituraDasDistancias(i); // .. Chame a função de de leitura da medida para a "Direita"
			//medida = ajusteDeValores(medida,0,830);
			posAtualVetor = armazenaValorVetor(medida, vetorDeMovimentos, tamanhoMaximoVetor, posAtualVetor); // Chame a função para armazenar a medida no vetor
        ///////////////////////////////////////////////////////////////////////////
		// Repita as chamadas acima para a "Esquerda", "Frente", "Tras"
		// ................
		///////////////////////////////////////////////////////////////////////////
		};

		dirigindo = continuaMapeamento(); // A variável "dirigindo" recebe a função "continuaMapeamento", à medida que o usuário termina de digitar os valores para o último mapeamento realizado
	}
	return posAtualVetor; // Retorna a última posição armazenada no vetor de movimentos
}


// O trecho abaixo irá utilizar as funções acima para ler os sensores e o movimento
// do robô e no final percorrer o vetor e mostrar o movimento a cada direção baseado 
// na maior distância a cada movimento

char *direcaoMaiorCaminho(int *vetor, int *maiorDirecao){ // Função que determina a direção a ser seguida pelo robô, com base na maior medida inserida
	int maiorDistancia = vetor[0]; // A maior distância será identificada no vetor em que os valores foram armazenados
	int indice;
	for (int i = 0; i<4; i++){ // Percorre as quatro possíveis direções a serem seguidas pelo robô
		if (vetor[i] > maiorDistancia){ // Enquanto o índice do vator for maior do que o valor inserido em "maiorDistancia", executa os comandos abaixo
			maiorDistancia = vetor[i]; // A maior distância será relacionada à sua respectiva posição no vetor que armazena os valores da distância
			indice = i;
		}
	}

	*maiorDirecao = maiorDistancia;
	return direcoes[indice]; // A função irá retornar o valor contido no índice, o qual recebe a maior distância identificada
}

void percorre(int *v,int tamPercorrido){ // Função responsável por indicar qual será a movimentação feita pelo robô, uma vez identificada a maior distância
	int *vetorDeMovimentos = v;  // Variável referente às movimentações do robô
	int maiorDir = 0;
	
	for(int i = 0; i < tamPercorrido; i+=4){ // Identifica o maior valor inserido em relação a cada possível direção
		char *direcao = direcaoMaiorCaminho(&(vetorDeMovimentos[i]),&maiorDir); // Chama a função "direcaoMaiorCaminho", responsável por identificar qual será o maior caminho a ser percorrido pelo robô
		printf("Movimentar para a %s, a uma distância de %i\n centímetros.",direcao,maiorDir); // Exibe, para o usuário, a direção para a qual a movimentação irá ocorrer, bem como a distância a ser percorrida
	}
}

int main(int argc, char** argv) {
	int tamanhoMaximoVetor = 100;
	int vetorDeMovimentos[tamanhoMaximoVetor*4];
	int posAtualVet = 0;
	
	posAtualVet = dirige(vetorDeMovimentos,tamanhoMaximoVetor);
	percorre(vetorDeMovimentos,posAtualVet);
	
	return 0;
}