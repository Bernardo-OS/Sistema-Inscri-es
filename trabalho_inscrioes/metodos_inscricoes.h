/*Construir um sistema para realizar inscrições (nome completo, email e matrícula), salvando os dados no arquivo 
inscricoes.csv. O sistema deve possuir um Menu como:
1 - Realizar inscrição 

2 - Listar inscritos 

3 - Registrar frequência (via matrícula) 

4 - Gerar relatório de presença 

5 - Sair Opção:

No item 3, toda vez que uma matrícula é salva/persistida, os dados armazenados são: matricula;data;hora

A interface que captura a frequência permanece em repetição até que a matrícula seja -27.
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef struct{
	int totalCadastros;
	int frequenciasRegistradas;
} Retorno;

typedef struct{
	string nome;
	string email;
    string matricula;
} Inscricao;

typedef struct{
	string matricula;
	string data;
    string hora;
} Frequencia;

void split(string vetor[], string str, string deli = " "){        
    int start = 0;
    int end = str.find(deli);
    int i = 0;
    while (end != -1) {
        vetor[i] = str.substr(start, end - start);
        i++;
        start = end + deli.size();
        end = str.find(deli, start);
    }
    vetor[i] = str.substr(start, end - start);
}

int conectarComBase(string nomeArquivo, Inscricao lista[], int n){
	ifstream procuradorLeitura;
	int indice = 0;
	//abrir e associar o arquivo com seu procurador - formato leitura
	//string linha;
	procuradorLeitura.open(nomeArquivo);
	if(!procuradorLeitura)return indice;
	string linha;
	
	while(!procuradorLeitura.eof() && indice < n){
		//para cada linha percorrida do procurador, splitar por ";"
		getline(procuradorLeitura,linha);
		if(linha != ""){
			string vetorLinha[3];
			split(vetorLinha, linha, ";");
			
            lista[indice].nome = vetorLinha[2];
            lista[indice].email = vetorLinha[1];
			lista[indice].matricula = vetorLinha[0];
			indice++;
		}
	}
	procuradorLeitura.close();
	//cout << "total registros.... " << indice << endl;
	return indice;
}

int conectarComBaseFrequencias(string nomeArquivo, Frequencia lista[], int n){
	ifstream procuradorLeitura;
	int indice = 0;
	//abrir e associar o arquivo com seu procurador - formato leitura
	//string linha;
	procuradorLeitura.open(nomeArquivo);
	if(!procuradorLeitura)return indice;
	string linha;
	
	while(!procuradorLeitura.eof() && indice < n){
		//para cada linha percorrida do procurador, splitar por ";"
		getline(procuradorLeitura,linha);
		if(linha != ""){
			string vetorLinha[3];
			split(vetorLinha, linha, ";");
			
            lista[indice].matricula = vetorLinha[0];
            lista[indice].data = vetorLinha[1];
			lista[indice].hora = vetorLinha[2];
			indice++;
		}
	}
	procuradorLeitura.close();
	// cout << "total registros.... " << indice << endl;
	return indice;
}
						   
void exibirLista(Inscricao lista[], int n){
	for (int i = 0; i < n; i++){
		cout << "Nome do aluno: " << lista[i].nome << " Email: " << lista[i].email << " | Matrícula: " << lista[i].matricula << endl;
	}
}

void exibirFrequencias(Frequencia lista[], int n){
	for (int i = 0; i < n; i++){
		cout << "Matricula do aluno: " << lista[i].matricula << " Data da aula: " << lista[i].data << " Hora da presença: " << lista[i].hora << endl;
	}
}

void gravarArquivo(const string& filename, const string& nome, const string& email, string matricula) {
    ofstream file(filename, ios::app); // Abre o arquivo em modo append
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        return;
    }
    file << matricula << ";" << email << ";" << nome << endl;
    file.close();
}

void gravarArquivoFrequencia(const string& filename, const string& matricula, const string& data, string hora) {
	ofstream file(filename, ios::app); // Abre o arquivo em modo append
	if (!file.is_open()) {
		cerr << "Erro ao abrir o arquivo " << filename << endl;
		return;
	}
	file << matricula << ";" << data << ";" << hora << endl;
	file.close();
}

Retorno menu(Inscricao lista[], int totalCadastrados, Frequencia listaFrequencia[], int frequenciasRegistradas, int n){
	int opcao;
	do {
		system("clear");
		//system("cls");
		cout << "MENU\n";
		cout << "1 - Realizar inscrição\n";
		cout << "2 - Listar inscrições\n";
        cout << "3 - Registrar frequência\n";
		cout << "4 - Gerar relatório de frequência\n";
		cout << "5 - Sair\n";
		cin >> opcao;
		fflush(stdin);
	
		
		switch(opcao){
			case 1:
				//Controle de duplicidade
				if(totalCadastrados < TAM){
                    bool ja_registrado = false;
					cout << "Realizar inscrição...\n";
					string nome;
                    string email;
                    string matricula;
                    cout << "Matrícula:	";
					cin >> matricula;
					fflush(stdin);

					ifstream procuradorLeitura;
					//ofstream procuradorEscrita;
					procuradorLeitura.open("inscricoes.csv");
					//procuradorEscrita.open("temp.csv");
                    ifstream file("inscricoes.csv");
					string linha;
			
					while (getline(procuradorLeitura, linha)) {
						if (linha != "") {
							string vetorLinha[3];
							split(vetorLinha, linha, ";");
							if (vetorLinha[2] == matricula) {
								ja_registrado = true;
								break;
							}
						}
					}
					procuradorLeitura.close();

					if (!ja_registrado) {
						totalCadastrados++;
						cout << "Nome do aluno: ";
						cin >> nome;
						fflush(stdin);
						cout << "Email do aluno: ";
						cin >> email;
						fflush(stdin);
						lista[totalCadastrados].nome = nome;
						lista[totalCadastrados].email = email;
						lista[totalCadastrados].matricula = matricula;
						gravarArquivo("inscricoes.csv", nome, email, matricula);
						conectarComBase("inscricoes.csv", lista, TAM);
					}else{
						cout << "Matricula ja inscrita\n";
					}
            	}else{
					cout << "Lista lotada\n";
				}
				break;
			case 2:
				cout << totalCadastrados;
				if(totalCadastrados > 0){
					cout << "Listar inscritos...\n";
					exibirLista(lista,totalCadastrados);
				}else{
					cout << "lista vazia\n";
				}
					fflush(stdin);

					//ifstream procuradorLeitura;
				break;		
			case 3:
				if(frequenciasRegistradas < TAM){
					cout << "Registrar frequencia...\n";
					string matricula;
					string data;
                    string hora;
					cout << "Data da aula: ";
            		cin >> data;
					fflush(stdin);
					cout << "Hora do registro: ";
            		cin >> hora;
					fflush(stdin);

					while(matricula!="-27"){
					cout << "Matricula do aluno: ";
					cin >> matricula;
					fflush(stdin);
					bool matriculaEncontrada = false;
					for(int i=0; i < totalCadastrados; i++){
						if(matricula==lista[i].matricula){
							frequenciasRegistradas++;
            				listaFrequencia[frequenciasRegistradas].matricula = matricula;
            				listaFrequencia[frequenciasRegistradas].data = data;
            				listaFrequencia[frequenciasRegistradas].hora = hora;
            				gravarArquivoFrequencia("frequencias.csv", matricula, data, hora);
							conectarComBaseFrequencias("frequencias.csv", listaFrequencia, TAM);
							matriculaEncontrada = true;
							cout << "Presença registrada com sucesso\n";
							break;
						}
					//cout << lista[i].matricula;
					}
					if (!matriculaEncontrada && matricula != "-27") {
						cout << "Matricula não esta inscrita\n";
					}
					}
				}else{
					cout << "Estourou limite de registros de frequencia\n";
					break;
				}
				break;
            case 4:
				if(totalCadastrados > 0){
					cout << "Listar inscritos...\n";
					exibirFrequencias(listaFrequencia,frequenciasRegistradas);
				}else{
					cout << "lista vazia\n";
				}
				break;
			case 5:
				break;
			default:
				cout << "Opcao invalida\n";
		}
		//system("pause");
		cout << "Pressione Enter para continuar...";
        cin.ignore();
        cin.get();
	} while(opcao != 5);
	Retorno retorno;
	retorno.totalCadastros = totalCadastrados;
	retorno.frequenciasRegistradas = frequenciasRegistradas;
	return retorno;
}
