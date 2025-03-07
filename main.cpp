#include <iostream>
#include <time.h>
#include "lista.h"
#include "game_actions.h"

using namespace std;

int main()
{
    Lista<int> player[2], baralho[2];

    inicializaBaralhos(player, baralho);

    int rodadas = get_rodadas();

    cout << "/nDistribuicao Inicial: ";
    cout << "/nJogador 1 - ";
    mostraBaralho(player[0]);
    cout << "/nJogador 2 - ";
    mostraBaralho(player[1]);

    int opcao;
    for (int i = 0; i < rodadas; i++)
    {
        cout << "/nRodada " << i + 1;

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

            // Escolhe baralho que nao esta vazio
            int k;
            (!ehVazia(baralho[0])) ? k = 0 : k = 1;

            cout << "/nJogador " << i + 1 << " escolhe ";
            switch (opcao)
            {
            case 1:
                cout << "comprar uma carta.";
                comprarCarta(player[j], baralho[k]);
                break;
            case 2:
                cout << "descartar uma carta.";
                descartarCarta(player[j]);
                break;
            case 3:
                cout << "trocar posicao de duas cartas.";
                trocarPosicao(player[j]);
                break;
            }
        }
    }

    // verificar ganhador
    ganhador(player[0], player[1]);

    for (int i = 0; i < 2; i++)
    {
        destroi(player[i]);
        destroi(baralho[i]);
    }

    return 0;
}
