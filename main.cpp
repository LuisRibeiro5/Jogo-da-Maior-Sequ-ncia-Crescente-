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

int main()
{
    Lista<int> player[2], baralho[2];

    inicializaBaralhos(player, baralho);

    int rodadas;
    cout << "/n digite o numero de rodadas a ser jogado:";
    cin >> rodadas;

    cout << "/nJogador 1";
    mostra(player[0]);
    cout << "/nJogador 2";
    mostra(player[1]);

    int opcao;
    for (int i = 0; i < rodadas; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << "/nVez do Jogador " << i + 1;

            menu();
            do
            {
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
        cout << "/nVencedor é o jogador 1 sequencia de " << seqPlayer1 << " numeros.";
    }else{
        cout << "/nVencedor é o jogador 2 sequencia de " << seqPlayer2 << " numeros.";
    }
    
    for (int i = 0; i < 2; i++)
    {
        destroi(player[i]);
        destroi(baralho[i]);
    }

    return 0;
}

template <typename T>
void inicializaBaralhos(Lista<T> *, Lista<T> *, int size = 2)
{
    for (int i = 0; i < size; i++)
    {
        cria(player[i]);
        cria(baralho[i]);
    }

    for (int i = 1; i < 101; i++)
    {
        insere(baralho[0], i, numeroDeElementos(baralho[0]) + 1);
        insere(baralho[1], i, numeroDeElementos(baralho[1]) + 1);
    }

    for (int i = 0; i < 5; i++)
    {
        comprarCarta(player[0], baralho[0]);
        comprarCarta(player[1], baralho[0]);
    }
};

void menu()
{
    cout << "Escolha sua jogada:";
    cout << "/nOpcao 1 : Comprar nova carta.";
    cout << "/nOpcao 2 : Descartar uma carta.";
    cout << "/nOpcao 3 : Trocar posicao de duas cartas.";
};

template <typename T>
void comprarCarta(Lista<T> &player, Lista<T> &baralho)
{
    int cartaPos, cartaValor, baralhoPos;
    srand(time(NULL));

    do
    {

        cartaPos = rand() % numeroDeElementos(baralho);
        cartaValor = retornaElemento(baralho, cartaPos);

    } while (existeElemento(player, cartaValor));

    retira(baralho, cartaPos);

    cout << "/nDigite qual a posicao do baralho que deseja inserir a carta comprada:";
    do
    {
        cout << "/nPosicao deve ser de 1 à " << numeroDeElementos(player) + 1;
        cin >> baralhoPos;
    } while (baralhoPos < 1 || baralhoPos > numeroDeElementos(player) + 1);

    insere(player, cartaValor, baralhoPos);

    cout << "/nCarta sorteada " << cartaValor;
};

template <typename T>
void descartarCarta(Lista<T> &player)
{
    int cartaPos;
    do
    {
        cout << "/nPosicao a ser excluida deve ser uma de 1 à " << player.cardinalidade;
        cin >> cartaPos;

    } while (!existePosicao(player, cartaPos));

    retira(player, cartaPos);

    cout << "/nCarta " << retornaElemento(player, cartaPos) << " removida.";
};

template <typename T>
void trocarPosicao(Lista<T> &player)
{
    int vCarta1, vCarta2;
    cout << "/nDigite o valor das cartas que deseja trocar de posição:";
    do
    {
        cout << "/nPosicao a ser escolhida deve ser uma de 1 à " << player.cardinalidade;
        cout << "/nCarta 1:";
        cin >> vCarta1;

    } while (!existeElemento(player));

    do
    {
        cout << "/nPosicao a ser escolhida deve ser uma de 1 à " << player.cardinalidade;
        cout << "/nCarta 2:";
        cin >> vCarta2;

    } while (!existeElemento(player));

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

    cout << "/nTroca cartas " << vCarta1 << " e " << vCarta2;
};


template<typename T>
int retornaSeqCrescente(Lista<T> & player){
    Nodo<T> *atual = player.inicio;
    int maiorSeq, seqAtual = 1;

    while (atual)
    {
        if (atual->valor + 1 == atual->proximo)
        {
            seqAtual++;
        }else{
            maiorSeq = seqAtual;
            seqAtual = 1;
        }
        
        atual = atual->proximo;
    }
    
    return maiorSeq;
};