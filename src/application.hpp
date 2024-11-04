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
	
private:

	int time;
	tinyxml2::XMLDocument doc;

	//estado atual do jogo
	std::vector<std::vector<std::string>> estado;


private:
	void Inicializa (void);

	//rotacionar uma linha
	void rotateRow (int row, char direcao);
	
};

#endif
