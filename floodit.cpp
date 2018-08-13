#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define cor 9
#define TAMB 20


typedef struct Tboard
{
	int tiles[TAMB*TAMB];
}Tboard;

typedef struct Tlist
{
	int pos[TAMB*TAMB];
	int pb;
}Tlist;

//Gera numeros aleatorios dentro de um range;
int randomB(int range)
{
	int x = rand()%range;
	return (x);

}

//Preenche o campo do jogo com as cores.
void preencheCampo(Tboard* board)
{
	for (int i = 0; i < TAMB*TAMB; i++)
		board->tiles[i] = randomB(cor) + 1;
}

//Imprime o campo do jogo.
void imprimeCampo(Tboard* board)
{
	for (int i = 0; i < TAMB; i++)
	{
		for(int j = 0; j < TAMB; j++)
			cout << board->tiles[i*TAMB + j] << " ";
		cout << endl;
	}

}

//Imprime o que está em um vetor, até achar o primeiro 0.
void imprimeLista(Tlist* list)
{
	for (int i = 1; i < TAMB*TAMB; i++)
	{
		cout << list->pos[i] << " ";
		if (list->pos[i] == 0) break;
	}
	cout << endl;
}

//Cria uma vetor vazio
void criaLista(Tlist* vec)
{
	for (int i = 0; i < TAMB*TAMB; i++)
		vec->pos[i] = 0;
}

//Verifica repetições
int verifica (Tlist* list, int num)
{
	for (int i = 1; i < TAMB*TAMB; i++)
	{
		if (list->pos[i] == num)
			return 0;
		if (list->pos[i] == 0)
			return 1;
	}
}

//Acha a "mancha" da primeira cor e coloca em um vetor.
void preencheLista(Tboard* board, Tlist* list)
{
	int ps = 0;
	int color = board->tiles[0];
	do
	{	
		if (board->tiles[list->pos[ps] + 1] == color)
			if (verifica(list, (list->pos[ps] + 1)))
			{
				list->pos[list->pb] = list->pos[ps] + 1;
				list->pb++;
			}

		if (board->tiles[list->pos[ps] + TAMB] == color)
			if (verifica(list, (list->pos[ps] + TAMB)))
			{
				list->pos[list->pb] = list->pos[ps] + TAMB;
				list->pb++;
			}

		ps++;
	} while (list->pos[ps] != 0);
}

void novaCor (Tboard* board, Tlist* list, int color)
{
	board->tiles[0] = color;
	for (int i = 1; i < TAMB*TAMB; i++)
	{
		if (list->pos[i] == 0)
			break;
		board->tiles[list->pos[i]] = color;
	}
}

int stop (Tboard* board)
{
	for (int i = 0; i < TAMB*TAMB; i++)
		if(board->tiles[i] != board->tiles[0])
			return (1);
	return (0);
}

int main(int argc, char const *argv[])
{
	int color, steps = 0;
	Tboard* board = new Tboard[sizeof(Tboard)];
	Tlist* list   = new Tlist[sizeof(Tlist)];
	list->pb = 1;
	criaLista(list);
	preencheCampo(board);
	board->tiles[1]  = 4;
	board->tiles[10] = 4;
	board->tiles[11] = 4;
	board->tiles[2]  = 4;
	board->tiles[3]  = 4;
	preencheLista(board, list);
	imprimeCampo(board);
	//imprimeLista(list);
	while (stop(board))
	{
		cin >> color;
		novaCor(board, list, color);
		imprimeCampo(board);
		preencheLista(board, list);
		//imprimeLista(list);
		steps++;
	}	
	cout << endl <<"YOU WIN! in " << steps << endl;
	return 0;
}
