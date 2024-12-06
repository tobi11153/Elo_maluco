// Elo Maluco
// main.cpp
// Prof. Giovani Bernardes Vitor
// ECOI2207- 2024
//Alunos: GABRIEL SOUZA SANTOS , ANA VICTÓRIA EVANGELISTA ARAÚJO ,  FABRICIO RICKELMER SOUZA DUARTE


#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <cmath>
#include "tinyxml2.h"
#include <cstdlib> // Para std::srand() e std::rand()
#include <ctime>   // Para std::time()
#include <sstream>
#include <algorithm>
#include <chrono>//para contar o tempo

// Estrutura para representar um estado
struct Estado
{
    std::vector<std::vector<std::string>> estado; // Representação do tabuleiro
    int custo;                                    // g(n): Custo acumulado até aqui
    int heuristica;                               // h(n): Heurística (estimativa até o objetivo)
    std::string caminho;                          // Caminho realizado até este estado

    // Operador para a fila de prioridade
    bool operator<(const Estado &outro) const
    {
        return (custo + heuristica) > (outro.custo + outro.heuristica);
    }
};

class Application
{
public:
    // Construtor da aplicação
    Application(int argc, char **argv);

    // Destrutor da aplicação
    ~Application();

    // Desenha o estado atual do jogo
    void draw();

    // Carrega um exemplo de tabuleiro a partir de um arquivo XML
    int loadXML_example(std::string filename);

    // Salva o estado inicial e o caminho encontrado em um arquivo XML
    void salvarXML( std::vector<std::vector<std::string>> &estadoInicial, const std::string &caminho);

    // Executa a aplicação
    int exec();

private:
    // Variáveis da aplicação
    int count;                                    // Contador genérico
    tinyxml2::XMLDocument doc;                    // Documento XML para leitura e escrita
    std::vector<std::vector<std::string>> estado; // Estado inicial do jogo

    // Inicializa o jogo
    void Inicializa();

     // Rotaciona uma linha do tabuleiro para a esquerda ou direita
    void rodarcoluna(std::vector<std::vector<std::string>> &estadoAtual, int row, char direcao);

    // Move o espaço vazio (vzo) para cima ou para baixo
    void movervzo(std::vector<std::vector<std::string>> &estadoAtual, char direcao);

        // Calcula a heurística (estimativa de custo até o objetivo) de um estado
    int calcularHeuristica( std::vector<std::vector<std::string>> &estadoAtual);

    // Gera os estados vizinhos possíveis a partir de um estado atual
    std::vector<Estado> gerarVizinhos( Estado &atual);

    // Verifica se o estado atual é uma solução
    bool is_solution( std::vector<std::vector<std::string>> &estadoAtual);

   // Serializa o estado atual em uma string para facilitar comparação
    std::string serializarEstado( std::vector<std::vector<std::string>> &estadoAtual);

 
    // Gera um estado inicial aleatório com base no nível de dificuldade
    std::vector<std::vector<std::string>> gerarEntradaAleatoria(int dificuldade);

    //dar output do caminho realiazado
    void mostrarCaminho( std::string &caminho);


       // Resolve o tabuleiro usando o algoritmo de busca A*
    bool resolver();

};

#endif
