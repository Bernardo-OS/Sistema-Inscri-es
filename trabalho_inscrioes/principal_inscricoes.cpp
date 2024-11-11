#include <iostream>
#include <fstream>
#include <string>

#define TAM 100
using namespace std;
#include "metodos_inscricoes.h"

int main(){
	//conectar com a base
	Inscricao lista[TAM];
	Frequencia listaFrequencia[TAM];
	int totalCadastrados = 0;
	int frequenciasRegistradas = 0;
	totalCadastrados = conectarComBase("inscricoes.csv", lista, TAM);
	frequenciasRegistradas = conectarComBaseFrequencias("frequencias.csv", listaFrequencia, TAM);
	//cout << totalCadastrados;
	Retorno retorno = menu(lista, totalCadastrados, listaFrequencia, frequenciasRegistradas,TAM);
	totalCadastrados = retorno.totalCadastros;
	frequenciasRegistradas = retorno.frequenciasRegistradas;
	//totalCadastrados = menu(lista, totalCadastrados, listaFrequencia, frequenciasRegistradas,TAM);
	return 1;
}