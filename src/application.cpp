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
Application::Application(int argc, char** argv)
{
	Inicializa();

}

//---------------------------------------------------------------------
Application::~Application()
{
}
//---------------------------------------------------------------------
void Application::Inicializa (void)
{   
    time = 0;
}
//---------------------------------------------------------------------
void Application::draw() {
    std::cout << "Estado Atual do Jogo:" << std::endl;
    for (const auto& linha : estado) {
        for (const auto& col : linha) {
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
int Application::loadXML_example(std::string filename) {
    if (doc.LoadFile(filename.c_str()) != XML_SUCCESS) {
        return doc.ErrorID(); // Retorna o código de erro se houver falha no carregamento
    }

    // Limpa o estado atual antes de carregar novos dados
    estado.clear();

    XMLElement* root = doc.FirstChildElement("EloMaluco");
    if (!root) {
        return -1; // Erro: elemento raiz não encontrado
    }

    XMLElement* estadoAtual = root->FirstChildElement("EstadoAtual");
    if (!estadoAtual) {
        return -1; // Erro: elemento EstadoAtual não encontrado
    }

    // Lê e armazena o estado atual do jogo
    for (XMLElement* row = estadoAtual->FirstChildElement("row"); row != nullptr; row = row->NextSiblingElement("row")) {
        std::vector<std::string> linha;
        for (XMLElement* col = row->FirstChildElement("col"); col != nullptr; col = col->NextSiblingElement("col")) {
            const char* texto = col->GetText();
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
		
	if(errorID)
		std::cout << "Ocorreu um erro na leitura do arquivo..." << std::endl;
	else
		std::cout << "Arquivo XML carregado com sucesso..." << std::endl;
	
	draw();
	rotateRow(0 ,'l');
	draw();
	rotateRow(1,'r');
	draw();
	rotateRow(1,'t');
	draw();
	return 0;
}
 
 //---------------------------------------------------------------------


void Application::rotateRow (int row, char direcao){
	if(direcao == 'r'){
		std::vector<std::string>NovoEstado = {estado[row][3],estado[row][0],estado[row][1],estado[row][2]};
	estado[row] = NovoEstado;
	}else if(direcao == 'l'){
		std::vector<std::string>NovoEstado = {estado[row][1],estado[row][2],estado[row][3],estado[row][0]};
	estado[row] = NovoEstado;
	}else
		std::cout << " Invalido" << endl;
	
}
