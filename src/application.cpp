// Elo Maluco
// application.cpp
// Prof. Giovani Bernardes Vitor
// ECOI2207 - 2024

#include <stdlib.h>
#include <stdio.h>

#include "application.hpp"

using namespace tinyxml2;

///////////////////////////////////////////////////////////////////////
// Application Class
Application::Application(int argc, char **argv)
{
	Inicializa();
}

//---------------------------------------------------------------------
Application::~Application()
{
}
//---------------------------------------------------------------------
void Application::Inicializa(void)
{
	time = 0;
	count = -2;
}
//---------------------------------------------------------------------
void Application::draw()
{
	std::cout << "Estado Atual do Jogo:" << std::endl;
	for (const auto &linha : estado)
	{
		for (const auto &col : linha)
		{
			std::cout << col << " ";
		}
		std::cout << std::endl;
	}
}

//---------------------------------------------------------------------
/** @page Example_1 Load an XML File
 *  @dontinclude ./xmltest.cpp
 *  Basic XML file loading.
 *  The basic syntax to load an XML file from
 *  disk and check for an error. (ErrorID()
 *  will return 0 for no error.)
 *  @skip example_1()
 *  @until }
 *  https://github.com/leethomason/tinyxml2
 */
int Application::loadXML_example(std::string filename)
{
	if (doc.LoadFile(filename.c_str()) != XML_SUCCESS)
	{
		return doc.ErrorID(); // Retorna o código de erro se houver falha no carregamento
	}

	// Limpa o estado atual antes de carregar novos dados
	estado.clear();

	XMLElement *root = doc.FirstChildElement("EloMaluco");
	if (!root)
	{
		return -1; // Erro: elemento raiz não encontrado
	}

	XMLElement *estadoAtual = root->FirstChildElement("EstadoAtual");
	if (!estadoAtual)
	{
		return -1; // Erro: elemento EstadoAtual não encontrado
	}

	// Lê e armazena o estado atual do jogo
	for (XMLElement *row = estadoAtual->FirstChildElement("row"); row != nullptr; row = row->NextSiblingElement("row"))
	{
		std::vector<std::string> linha;
		for (XMLElement *col = row->FirstChildElement("col"); col != nullptr; col = col->NextSiblingElement("col"))
		{
			const char *texto = col->GetText();
			linha.push_back(texto ? texto : "");
		}
		estado.push_back(linha);
	}

	std::cout << "Estado carregado com sucesso." << std::endl;
	return 0; // Sucesso
}

//---------------------------------------------------------------------

int Application::exec()
{

	// Executa o algoritmo para buscar a solução!!!

	// Carrega arquivo XML de entrada... exemplo...
	int errorID = loadXML_example(std::string("../data/EloMaluco_estadoInicialAcoes_teste01.xml"));

	if (errorID)
		std::cout << "Ocorreu um erro na leitura do arquivo..." << std::endl;
	else
		std::cout << "Arquivo XML carregado com sucesso..." << std::endl;
	std::vector<std::vector<std::vector<std::string>>> caminhos;
	draw();
	resolve(caminhos);
	draw();

	std::cout << count;
	return 0;
}

//---------------------------------------------------------------------
// rotaciona a linha para a direita 'r' (right) ou para a esquerda 'l' (left)

void Application::rotateRow(int row, char direcao)
{
	if (direcao == 'r')
	{
		std::vector<std::string> NovoEstado = {estado[row][3], estado[row][0], estado[row][1], estado[row][2]};
		estado[row] = NovoEstado;
	}
	else if (direcao == 'l')
	{
		std::vector<std::string> NovoEstado = {estado[row][1], estado[row][2], estado[row][3], estado[row][0]};
		estado[row] = NovoEstado;
	}
	else
		std::cout << " Invalido" << endl;
}

//---------------------------------------------------------------------

void Application::movevzo(char direcao)
{

	for (int i = 0; i < estado.size(); i++)
	{
		for (int j = 0; j < estado[i].size(); j++)
		{
			if (estado[i][j] == "vzo")
			{
				if (direcao == 'u' && i != 0)
				{
					std::swap(estado[i][j], estado[i - 1][j]);
				}
				else if (direcao == 'd' && i != 3)
				{
					std::swap(estado[i][j], estado[i + 1][j]);
				}
			}
		}
	}
}

//---------------------------------------------------------------------

bool Application::resolve(std::vector<std::vector<std::vector<std::string>>> &caminhos)
{
    // Checa se o estado atual é a solução
    if (is_solution()) {
        std::cout << "Solução encontrada!" << std::endl;
        return true;
    }

    count++;

    // Verifica se o estado atual já foi visitado para evitar loops
    if (samepath(caminhos)) {
        return false; // Se o estado já existe em caminhos, retorna para evitar recursão infinita
    }

    // Adiciona o estado atual aos caminhos visitados
    caminhos.push_back(estado);


    // Tentativa de resolver rotacionando a primeira linha para a direita
    rotateRow(0, 'r');
    if (resolve(caminhos)) return true; // Se a solução for encontrada, retorna
    rotateRow(0, 'l'); // Desfaz a rotação

    // Tentativa de resolver rotacionando a última linha para a direita
    rotateRow(3, 'r');
    if (resolve(caminhos)) return true; // Se a solução for encontrada, retorna
    rotateRow(3, 'l'); // Desfaz a rotação

    // Tentativa de mover 'vzo' para cima
    movevzo('u');
    if (resolve(caminhos)) return true; // Se a solução for encontrada, retorna
    movevzo('d'); // Desfaz o movimento

    // Tentativa de mover 'vzo' para baixo
    movevzo('d');
    if (resolve(caminhos)) return true; // Se a solução for encontrada, retorna
    movevzo('u'); // Desfaz o movimento

    // Remove o estado atual dos caminhos (backtracking)
    caminhos.pop_back();
    return false;
}


//---------------------------------------------------------------------

bool Application::samepath(std::vector<std::vector<std::vector<std::string>>> &caminhos)
{
	for (const auto &caminho : caminhos)
	{
		if (caminho == estado)
		{
			return true; // A matriz foi encontrada em caminhos
		}
	}
	return false; // A matriz não foi encontrada em caminhos
}


//---------------------------------------------------------------------

bool Application::is_solution() {
    // Defina o estado de solução alvo; cada linha representa o objetivo desejado
    std::vector<std::vector<std::string>> estadoObjetivo = {
        {"vms", "ams", "vds", "brs"},
        {"vmm", "amm", "vdm", "brm"},
        {"vmm", "amm", "vdm", "vzo"},
        {"vmi", "ami", "vdi", "bri"}
    };

    // Verifica se o estado atual é igual ao estado objetivo
    return estado == estadoObjetivo;
}