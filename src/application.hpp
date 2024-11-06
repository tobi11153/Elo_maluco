// Elo Maluco
// application.hpp
// Prof. Giovani Bernardes Vitor
// ECOI2207 - 2024

#include <iostream>
#include <vector>
#include <list>
#include <string>

#include "tinyxml2.h"


#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

using namespace std;

/////////////////////////////////////////////////////////////
class Application
{
public:
	Application(int argc, char** argv);
	~Application(void);

	void draw();
	int loadXML_example(string filename);
	int  exec();
	
	//mover para espaço branco
	void movevzo(char direcao);

	//resolver
	bool resolve(    std::vector<std::vector<std::vector<std::string>>>& caminhos
);

	//verificar se ja passou por esse caminho
	bool samepath( std::vector<std::vector<std::vector<std::string>>>& caminhos);
private:
	int count;
	int time;
	tinyxml2::XMLDocument doc;

	//estado atual do jogo
	std::vector<std::vector<std::string>> estado;

	//verificar se é solução
	bool is_solution();



private:
	void Inicializa (void);

	//rotacionar uma linha
	void rotateRow (int row, char direcao);
	
};

#endif
