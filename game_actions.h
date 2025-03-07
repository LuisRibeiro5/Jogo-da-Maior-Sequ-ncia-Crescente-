#ifndef GAMEACTIONS_H_INCLUDED
#define GAMEACTIONS_H_INCLUDED

#include "lista.h"
#include <iostream>
using namespace std;

template <typename T>
void inicializaBaralhos(Lista<T> *player, Lista<T> *baralho, int size = 2)
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

int get_rodadas()
{
    int rodadas;
    do
    {
        cout << "/n digite o numero de rodadas a ser jogado (maximo 100):";
        cin >> rodadas;
    } while (rodadas < 1 || rodadas > 100);
    return rodadas;
}

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

    cout << "/nCarta sorteada " << cartaValor << " inserida na posição " << baralhoPos;
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

    } while (!existeElemento(player, vCarta1));

    do
    {
        cout << "/nPosicao a ser escolhida deve ser uma de 1 à " << player.cardinalidade;
        cout << "/nCarta 2:";
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

    cout << "/nCartas " << vCarta1 << " e " << vCarta2 << " foram trocadas de posição";
};

template <typename T>
int retornaSeqCrescente(Lista<T> &player)
{
    Nodo<T> *atual = player.inicio;
    int maiorSeq, seqAtual = 1;

    while (atual)
    {
        if ((atual->valor + 1) == atual->proximo->valor)
        {
            seqAtual++;
        }
        else
        {
            maiorSeq = seqAtual;
            seqAtual = 1;
        }

        atual = atual->proximo;
    }

    return maiorSeq;
};

template <typename T>
void ganhador(Lista<T> &player1, Lista<T> &player2)
{
    int seqPlayer1, seqPlayer2;
    seqPlayer1 = retornaSeqCrescente(player1);
    seqPlayer2 = retornaSeqCrescente(player2);

    if (seqPlayer1 > seqPlayer2)
    {
        cout << "/nVencedor é o jogador 1 sequencia de " << seqPlayer1 << " numeros.";
    }
    else
    {
        cout << "/nVencedor é o jogador 2 sequencia de " << seqPlayer2 << " numeros.";
    }
}

template <typename T>
void mostraBaralho(Lista<T> &lista)
{
    Nodo<T> *aux = lista.inicio;
    std::cout << "[";
    while (aux)
    {
        std::cout << " " << aux->valor;
        (aux->proximo) ? std::cout << "," : std::cout << " ";
        aux = aux->proximo;
    }
    std::cout << "]";
}

#endif