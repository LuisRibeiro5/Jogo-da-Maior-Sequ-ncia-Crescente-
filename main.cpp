#include <iostream>
#include <time.h>
#include "lista.h"

using namespace std;

int main() {
    Lista<int> player1, player2, baralho1, baralho2;
    cria(player1);
    cria(player2);
    cria(baralho1);
    cria(baralho2);

    for (int i = 1; i < 101; i++)
    {
        insere(baralho1, i, baralho1.cardinalidade + 1);
        insere(baralho2, i, baralho2.cardinalidade + 1);
    }

    srand(time(NULL));
    for (int i = 0; i < 5; i++)
    {
        int j = rand() % baralho1.cardinalidade + 1;

        insere(player1, retornaElemento(baralho1, j), player1.cardinalidade + 1);
        retira(baralho1, j);

        j = rand() % baralho1.cardinalidade + 1;

        insere(player2, retornaElemento(baralho1, j), player2.cardinalidade + 1);
        retira(baralho1, j);

    }

    mostra(player1);
    mostra(player2);
    
    int rodadas;
    cout << "/n digite o numero de rodadas a ser jogado:";
    cin >> rodadas;
    
    for (int i = 0; i < rodadas; i++)
    {
        //vez do player 1
        //vez do player 2
    }

    //verificar ganhador
    

    destroi(player1);
    destroi(player2);
    destroi(baralho1);
    destroi(baralho2);

    return 0;
}