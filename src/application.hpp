#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <cmath>
#include "tinyxml2.h"

// Estrutura para representar um estado
struct Estado
{
    std::vector<std::vector<std::string>> estado; // Representação do tabuleiro
    int custo;                                   // g(n): Custo acumulado até aqui
    int heuristica;                              // h(n): Heurística (estimativa até o objetivo)
    std::string caminho;                         // Caminho realizado até este estado

    // Operador para a fila de prioridade
    bool operator<(const Estado &outro) const
    {
        return (custo + heuristica) > (outro.custo + outro.heuristica);
    }
};

class Application
{
public:
    Application(int argc, char **argv);
    ~Application();

    void draw();
    int loadXML_example(std::string filename);
    int exec();

private:
    int count;
    tinyxml2::XMLDocument doc;

    // Estado inicial do jogo
    std::vector<std::vector<std::string>> estado;

    // Verificar se é a solução
    bool is_solution(const std::vector<std::vector<std::string>> &estadoAtual);

    // Função para inicializar o jogo
    void Inicializa();

    // Rotacionar uma linha
    void rotateRow(std::vector<std::vector<std::string>> &estadoAtual, int row, char direcao);

    // Mover o espaço vazio
    void movevzo(std::vector<std::vector<std::string>> &estadoAtual, char direcao);

    // Funções auxiliares para A*
    int calcularHeuristica(const std::vector<std::vector<std::string>> &estadoAtual);
    std::string serializarEstado(const std::vector<std::vector<std::string>> &estadoAtual);
    std::vector<Estado> gerarVizinhos(const Estado &atual);
    // Algoritmo de busca A*
    bool resolve();
};

#endif
