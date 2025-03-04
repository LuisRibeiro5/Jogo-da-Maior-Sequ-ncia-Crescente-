#include <iostream>
#include <time.h>
#include "lista.h"

using namespace std;

int main() {
    Lista<int> player[2], baralho[2];
    for (int i = 0; i < 2; i++)
    {
        cria(player[i]);
        cria(baralho[i]);
    }

    for (int i = 1; i < 101; i++)
    {
        insere(baralho[0], i, baralho[0].cardinalidade + 1);
        insere(baralho[1], i, baralho[1].cardinalidade + 1);
    }

    srand(time(NULL));
    for (int i = 0; i < 5; i++)
    {
        int j = rand() % baralho[0].cardinalidade + 1;

        insere(player[0], retornaElemento(baralho[0], j), player[0].cardinalidade + 1);
        retira(baralho[0], j);

        j = rand() % baralho[0].cardinalidade + 1;

        insere(player[1], retornaElemento(baralho[0], j), player[1].cardinalidade + 1);
        retira(baralho[0], j);

    }

    mostra(player[0]);
    mostra(player[1]);
    
    int rodadas;
    cout << "/n digite o numero de rodadas a ser jogado:";
    cin >> rodadas;
    
    for (int i = 0; i < rodadas; i++)
    {
        //vez do player 1
        //vez do player 2
    }

    //verificar ganhador
    
    for (int i = 0; i < 2; i++)
    {
        destroi(player[i]);
        destroi(baralho[i]);
    }
    
    return 0;
}