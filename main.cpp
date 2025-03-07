#include <iostream>
#include <time.h>
#include "lista.h"

using namespace std;

template <typename T>
void inicializaBaralhos(Lista<T> *, Lista<T> *, int size = 2);
void menu();

template <typename T>
void comprarCarta(Lista<T> &, Lista<T> &);

template <typename T>
void descartarCarta(Lista<T> &);

template <typename T>
void trocarPosicao(Lista<T> &);

template<typename T>
int retornaSeqCrescente(Lista<T> &);

int main(){
    srand(time(NULL));

    Lista<int> player[2], baralho[2];

    inicializaBaralhos(player, baralho);

    int rodadas;
    cout << "\ndigite o numero de rodadas a ser jogado:";
    cin >> rodadas;

    cout << "\nJogador 1";
    mostra(player[0]);
    cout << "\nJogador 2";
    mostra(player[1]);

    int opcao;
    for (int i = 0; i < rodadas; i++) {
        for (int j = 0; j < 2; j++) {  
            cout << "\nVez do Jogador " << j + 1;  
    
            menu();
            do
            {
                cout << endl;
                cin >> opcao;
                if (opcao < 1 || opcao > 3)
                    cout << "Opcao invalida";

            } while (opcao < 1 || opcao > 3);

            // Escolha do baralho
            int k;
            (!ehVazia(baralho[0])) ? k = 0 : k = 1;

            switch (opcao)
            {
            case 1:
                comprarCarta(player[j], baralho[k]);
                break;
            case 2:
                descartarCarta(player[j]);
                break;
            case 3:
                trocarPosicao(player[j]);
                break;
            }
        }
    }

    // verificar ganhador
    int seqPlayer1, seqPlayer2;
    seqPlayer1 = retornaSeqCrescente(player[0]);
    seqPlayer2 = retornaSeqCrescente(player[1]);

    if (seqPlayer1 > seqPlayer2) {
        cout << "\nVencedor e o jogador 1 com sequencia de " << seqPlayer1 << " numeros.";
    } else if (seqPlayer2 > seqPlayer1) {
        cout << "\nVencedor e o jogador 2 com sequencia de " << seqPlayer2 << " numeros.";
    } else {
        cout << "\nEmpate! Ambos tem sequencia de " << seqPlayer1 << " numeros.";
    }    
    
    for (int i = 0; i < 2; i++)
    {
        destroi(player[i]);
        destroi(baralho[i]);
    }

    return 0;
}

template <typename T>
void inicializaBaralhos(Lista<T> *player, Lista<T> *baralho, int size) {
    for (int i = 0; i < size; i++) {
        cria(player[i]);
        cria(baralho[i]);
    }

    for (int i = 1; i <= 100; i++) {
        insere(baralho[i % size], i, numeroDeElementos(baralho[i % size]) + 1);
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 5; j++) {
            comprarCarta(player[i], baralho[i]);  // Cada jogador compra 5 cartas
        }
    }
}


void menu()
{
    cout << "\nEscolha sua jogada:";
    cout << "\nOpcao 1 : Comprar nova carta.";
    cout << "\nOpcao 2 : Descartar uma carta.";
    cout << "\nOpcao 3 : Trocar posicao de duas cartas.";
};

template <typename T>
void comprarCarta(Lista<T> &player, Lista<T> &baralho)
{
    if (ehVazia(baralho)) {
        cout << "\nBaralho vazio! Não há cartas para comprar.\n";
        return;
    }

    int cartaPos;
    do {
        cartaPos = rand() % numeroDeElementos(baralho) + 1; // Garantir que não seja 0
    } while (cartaPos < 1 || cartaPos > numeroDeElementos(baralho));

    int cartaValor = retornaElemento(baralho, cartaPos);
    retira(baralho, cartaPos);

    int playerPos;
    do {
        cout << "\nPosicao para inserir a carta (1 a " << numeroDeElementos(player) + 1 << "): ";
        cin >> playerPos;
    } while (playerPos < 1 || playerPos > numeroDeElementos(player) + 1);

    insere(player, cartaValor, playerPos);
    cout << "\nCarta sorteada: " << cartaValor << "\n";

    cout << "\nCartas do jogador apos compra: ";
    mostra(player);
    cout << endl;
}

template <typename T>
void descartarCarta(Lista<T> &player)
{
    int cartaPos;
    do
    {
        cout << "\nPosicao a ser excluida deve ser uma de 1 a " << player.cardinalidade << ": ";
        cin >> cartaPos;

    } while (!existePosicao(player, cartaPos));


    T cartaRemovida = retornaElemento(player, cartaPos);

    retira(player, cartaPos);

    cout << "\nCarta " << cartaRemovida << " removida.";

    cout << "\nCartas do jogador apos a remocao: ";
    mostra(player);
    cout << endl;
};

template <typename T>
void trocarPosicao(Lista<T> &player)
{
    int vCarta1, vCarta2;
    cout << "\nDigite o valor das cartas que deseja trocar de posicao:";
    do
    {
        cout << "\nO valor selecionado deve pertencer ao valor da carta no baralho ";
        cout << "\nCarta 1: ";
        cin >> vCarta1;

    } while (!existeElemento(player, vCarta1));

    do
    {
        cout << "\nO valor selecionado deve pertencer ao valor da carta no baralho ";
        cout << "\nCarta 2: ";
        cin >> vCarta2;

    } while (!existeElemento(player, vCarta2));

    Nodo<T> *carta1 = player.inicio;
    Nodo<T> *carta2 = player.inicio;

    while (carta1->valor != vCarta1)
    {
        carta1 = carta1->proximo;
    }

    while (carta2->valor != vCarta2)
    {
        carta2 = carta2->proximo;
    }

    carta1->valor = vCarta2;
    carta2->valor = vCarta1;

    cout << "\nTroca cartas " << vCarta1 << " e " << vCarta2;

    cout << "\nCartas do jogador apos a troca: ";
    mostra(player);
    cout << endl;
};


template<typename T>
int retornaSeqCrescente(Lista<T> &player){
    if (ehVazia(player)) return 0;

    Nodo<T> *atual = player.inicio;
    int maiorSeq = 1, seqAtual = 1;

    while (atual->proximo) {
        if (atual->valor + 1 == atual->proximo->valor) {
            seqAtual++;
            if (seqAtual > maiorSeq) maiorSeq = seqAtual;
        } else {
            seqAtual = 1;
        }
        atual = atual->proximo;
    }

    return maiorSeq;
}