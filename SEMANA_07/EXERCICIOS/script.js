const jogadorAtual = document.querySelector(".jogadorAtual"); // A constante "jogadorAtual" representa o texto que indica o jogador da vez
let url = "http://10.254.16.227/"; // Endereço de IP resultante da conexão entre ESP32 e servidor
// O endereço de IP é retornado no Serial Monitor quando o código da ESP32 é executado
let campoSelecionado; // Variável para manipular o campo que o jogador selecionou
let jogador = "X"; // Variável que indica o que será inserido no campo selecionado

// A variável abaixo representa o conjunto de possibilidades de que um jogador vença o jogo

let posicoes = [
    [1,2,3],
    [4,5,6],
    [7,8,9],
    [1,4,7],
    [2,5,8],
    [3,6,9],
    [1,5,9],
    [3,5,7],
];

function init() {
    campoSelecionado = []; // A variável "campoSelecionado" recebe um array que armazena as jogadas de um jogador

    jogadorAtual.innerHTML = `O jogador da vez é ${jogador}`; // Texto que, no HTML, indica de qual jogador será a próxima jogada

    document.querySelectorAll(".game button").forEach((item) => { // Seleciona os botões que representam os campos em que podem ser feitas as jogadas
        item.innerHTML = ""; // Espaço para que seja inserido 'X' ou 'O'
        item.addEventListener("click", novaJogada); // Um clique sobre o botão representa uma jogada, concretizada pela inserção do texto 'X' ou 'O'
    });
}

init(); // Aqui, estamos chamando que executa os comandos acima

function novaJogada(e) { // Criando a função novaJogada 
    const index = e.target.getAttribute("data-i"); // A constante "index" manipula os objetos que possuem "data-i" como atributo (botões do jogo)
    console.log(index); // Exibir no console qual foi o campo que o jogador selecionou
    e.target.innerHTML = jogador; // Atribuímos ao campo em questão a jogada realizada, a qual será definida abaixo
    e.target.removeEventListener("click", novaJogada); // Faz com que o clique sobre um campo específico só possa ser realizado uma vez
    campoSelecionado[index] = jogador; // Atribui a variável "jogador" ao índice referente ao campo selecionado

    // A lógica abaixo chama a função "conferir", referente ao vencedor do jogo, a qual será estruturada abaixo

    setTimeout(() => {
        conferir();
    }, [100]);

    jogador = jogador === "X" ? "O" : "X"; // Atribuímos à variável "jogador" as possibilidades de jogada, alternando entre 'X' e 'O'
    
    jogadorAtual.innerHTML = `O jogador da vez é ${jogador}`; // Atualizamos, por meio dessa linha, quem será o próximo jogador

    // A lógica abaixo confere se a jogada a ser inserida em um campo é 'X' ou 'O'
    // Se o jogador de X seleciona um determinado campo, X aparece como um texto vermelho, correspondendo ao seu LED no circuito
    // Se o jogador de O seleciona um determinado campo, O aparece como um texto azul, correspondendo ao seu LED no circuito

    if (jogador == "X") {

        if (index == 1) {
            var player = document.querySelector("#botao1");
            player.style.color = "blue";
        }
        else if (index == 2) {
            var player = document.querySelector("#botao2");
            player.style.color = "blue";
        }
        else if (index == 3) {
            var player = document.querySelector("#botao3");
            player.style.color = "blue";
        }
        else if (index == 4) {
            var player = document.querySelector("#botao4");
            player.style.color = "blue";
        }
        else if (index == 5) {
            var player = document.querySelector("#botao5");
            player.style.color = "blue";
        }
        else if (index == 6) {
            var player = document.querySelector("#botao6");
            player.style.color = "blue";
        }
        else if (index == 7) {
            var player = document.querySelector("#botao7");
            player.style.color = "blue";
        }
        else if (index == 8) {
            var player = document.querySelector("#botao8");
            player.style.color = "blue";
        }
        else if (index == 9) {
            var player = document.querySelector("#botao9");
            player.style.color = "blue";
        }

        jogadorX(); // Chama a função responsável por acender o LED vermelho, quando for a vez de X jogar
    }
    
    if (jogador == "O") {

        if (index == 1) {
            var player = document.querySelector("#botao1");
            player.style.color = "red";
        }
        else if (index == 2) {
            var player = document.querySelector("#botao2");
            player.style.color = "red";
        }
        else if (index == 3) {
            var player = document.querySelector("#botao3");
            player.style.color = "red";
        }
        else if (index == 4) {
            var player = document.querySelector("#botao4");
            player.style.color = "red";
        }
        else if (index == 5) {
            var player = document.querySelector("#botao5");
            player.style.color = "red";
        }
        else if (index == 6) {
            var player = document.querySelector("#botao6");
            player.style.color = "red";
        }
        else if (index == 7) {
            var player = document.querySelector("#botao7");
            player.style.color = "red";
        }
        else if (index == 8) {
            var player = document.querySelector("#botao8");
            player.style.color = "red";
        }
        else if (index == 9) {
            var player = document.querySelector("#botao9");
            player.style.color = "red";
        }

        jogadorO(); // Chama a função responsável por acender o LED azul, quando for a vez de O jogar
    }

}


function conferir() { // Construindo a função conferir
    let ultimaJogada = jogador === "X" ? "O" : "X"; // Variável que armazena a última jogada

    // A lógica abaixo armazena os campos selecionados pelo jogador, de modo que sua última jogada seja conferida a fim de obter o resultado do jogo

    const items = campoSelecionado
        .map((item, i) => [item, i])
        .filter((item) => item[0] === ultimaJogada)
        .map((item) => item[1]);

    // A lógica abaixo determina o vencedor do jogo ao conferir se uma das possibilidades armazenadas na variável "posicoes" foi concretizada
    // Esse processo é determinado pela última jogada do vencedor, armazenada na variável "ultimaJogada"

    for (pos of posicoes) {
        if (pos.every((item) => items.includes(item))) {
            alert("O JOGADOR '" + ultimaJogada + "' GANHOU!"); // Exibe o vencedor do jogo
            if (ultimaJogada == "X") { // Se o vencedor foi o player X:
                ganhouX(); // A função ganhouX, responsável por piscar o LED vermelho, é chamada
            }
            else if (ultimaJogada == "O") { // Se o vencedor foi o player O:
                ganhouO(); // A função ganhouO, responsável por piscar o LED azul, é chamada
            }
            init(); // A função init é chamada a fim de reiniciar o jogo
            return;
        }
    }

    // Se todos os campos foram selecionados e nenhuma das possibilidades de vencer foi concretizada, significa que o jogo empatou:

    if (campoSelecionado.filter((item) => item).length === 9) { // Confere se os nove campos foram preenchidos
        alert("EMPATE!"); // Exibe mensagem informando que o jogo empatou
        empatou(); // Chama a função empatou, responsável por piscar o LED amarelo
        init(); // A função init é chamada a fim de reiniciar o jogo
        return;
    }
}

// Abaixo, são feitas as requisições por meio do AJAX
// As funções chamadas enviam suas respectivas rotas para o servidor
// Consequentemente, os LEDs são manipulados de acordo com o andamento do jogo, demonstrando que a comunicação entre a placa e o servidor foi devidamente estabelecida

function ganhouX() { // Função que faz piscar o LED vermelho
     $.ajax({
        url: url + "venceX", 
    })
}

function ganhouO() { // Função que faz piscar o LED azul
     $.ajax({
        url: url + "venceO",
    })
}

function empatou() { // Função que faz piscar o LED amarelo
    $.ajax({
        url: url + "empate",
    })
}

function jogadorX() { // Função que deixa aceso o LED vermelho na vez do player X
    $.ajax({
        url: url + "jogaX",
    })
}

function jogadorO() { // Função que deixa aceso o LED azul na vez do player O
    $.ajax({
        url: url + "jogaO",
    })
}