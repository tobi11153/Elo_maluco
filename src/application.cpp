#include "application.hpp"
#include <sstream>
#include <algorithm>

using namespace tinyxml2;

Application::Application(int argc, char **argv) { Inicializa(); }
Application::~Application() {}

void Application::Inicializa() { count = 0; }
/////////////////////////////////////////////////////////////////////////////////////////////

// Desenhar o estado atual
void Application::draw()
{
    for (const auto &linha : estado)
    {
        for (const auto &col : linha)
            std::cout << col << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////
// Carrega o estado inicial do XML
int Application::loadXML_example(std::string filename)
{
    if (doc.LoadFile(filename.c_str()) != XML_SUCCESS)
        return doc.ErrorID();

    estado.clear();
    XMLElement *root = doc.FirstChildElement("EloMaluco");
    if (!root)
        return -1;

    XMLElement *estadoAtual = root->FirstChildElement("EstadoAtual");
    if (!estadoAtual)
        return -1;

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
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////

// Verifica se o estado atual é solução
bool Application::is_solution(const std::vector<std::vector<std::string>> &estadoAtual)
{
    std::vector<std::vector<std::string>> estadoObjetivo = {
        {"vms", "ams", "vds", "brs"},
        {"vmm", "amm", "vdm", "brm"},
        {"vmm", "amm", "vdm", "bri"},
        {"vmi", "ami", "vdi", "vzo"}};
    return estadoAtual == estadoObjetivo;
}

/////////////////////////////////////////////////////////////////////////////////////////////

// Rotaciona uma linha
void Application::rotateRow(std::vector<std::vector<std::string>> &estadoAtual, int row, char direcao)
{
    if (direcao == 'r')
        std::rotate(estadoAtual[row].rbegin(), estadoAtual[row].rbegin() + 1, estadoAtual[row].rend());
    else if (direcao == 'l')
        std::rotate(estadoAtual[row].begin(), estadoAtual[row].begin() + 1, estadoAtual[row].end());
}

/////////////////////////////////////////////////////////////////////////////////////////////

// Move o espaço vazio
void Application::movevzo(std::vector<std::vector<std::string>> &estadoAtual, char direcao)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (estadoAtual[i][j] == "vzo")
            {
                if (direcao == 'u' && i > 0)
                    std::swap(estadoAtual[i][j], estadoAtual[i - 1][j]);
                if (direcao == 'd' && i < 3)
                    std::swap(estadoAtual[i][j], estadoAtual[i + 1][j]);
                return;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////

// Heurística (distância de Manhattan)
int Application::calcularHeuristica(const std::vector<std::vector<std::string>> &estadoAtual) {
    int h = 0;
    std::vector<std::vector<std::string>> estadoObjetivo = {
        {"vms", "ams", "vds", "brs"},
        {"vmm", "amm", "vdm", "brm"},
        {"vmm", "amm", "vdm", "bri"},
        {"vmi", "ami", "vdi", "vzo"}
    };
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int x = 0; x < 4; ++x) {
                for (int y = 0; y < 4; ++y) {
                    if (estadoAtual[i][j] == estadoObjetivo[x][y]) {
                        h += abs(i - x) + abs(j - y);
                        break;
                    }
                }
            }
        }
    }
    return h;
}
/////////////////////////////////////////////////////////////////////////////////////////////

// Serializa o estado para formato único
std::string Application::serializarEstado(const std::vector<std::vector<std::string>> &estadoAtual)
{
    std::ostringstream oss;
    for (const auto &linha : estadoAtual)
        for (const auto &col : linha)
            oss << col << ",";
    return oss.str();
}

/////////////////////////////////////////////////////////////////////////////////////////////

// Algoritmo backtraking (usando distancia de manhatham A*)
bool Application::resolve() {
    std::priority_queue<Estado> fila;
    std::unordered_set<std::string> caminhosVisitados;

    // Estado inicial
    Estado inicial;
    inicial.estado = estado;
    inicial.custo = 0;
    inicial.heuristica = calcularHeuristica(estado);
    inicial.caminho = "";

    fila.push(inicial);
    caminhosVisitados.insert(serializarEstado(inicial.estado));

    std::cout << inicial.heuristica << std::endl;
    
    while (!fila.empty()) {
        Estado atual = fila.top();
        fila.pop();

        if (is_solution(atual.estado)) {
            std::cout << "Solução encontrada: " << atual.caminho << std::endl;
            return true;
        }

        for (const auto &vizinho : gerarVizinhos(atual)) {
            if (caminhosVisitados.find(serializarEstado(vizinho.estado)) == caminhosVisitados.end()) {
                caminhosVisitados.insert(serializarEstado(vizinho.estado));
                fila.push(vizinho);
            }
        }
    }

    std::cout << "Solução não encontrada." << std::endl;
    return false;
}


/////////////////////////////////////////////////////////////////////////////////////////////

// Execução
int Application::exec()
{
    int errorID = loadXML_example("../data/EloMaluco_estadoAtual_teste01.xml");
    if (errorID)
    {
        std::cout << "Erro ao carregar XML." << std::endl;
        return -1;
    }
    std::cout << "Estado inicial carregado." << std::endl;
    draw();
    return resolve() ? 0 : 1;
    draw();
}

/////////////////////////////////////////////////////////////////////////////////////////////


std::vector<Estado> Application::gerarVizinhos(const Estado &atual) {
    std::vector<Estado> vizinhos;

    // Movimentos do espaço vazio
    for (char dir : {'u', 'd'}) {
        Estado novo = atual;
        novo.caminho += dir;
        movevzo(novo.estado, dir);
        if (novo.estado != atual.estado) { // Só adiciona se o estado for diferente
            novo.custo += 1;
            novo.heuristica = calcularHeuristica(novo.estado);
            vizinhos.push_back(novo);
        }
    }

    // Rotação de linhas (apenas para topo e fundo)
    for (int row : {0, 3}) { // Apenas linhas 0 e 3
        for (char dir : {'l', 'r'}) {
            Estado novo = atual;
            novo.caminho += std::to_string(row) + dir;
            rotateRow(novo.estado, row, dir);
            if (novo.estado != atual.estado) { // Só adiciona se o estado for diferente
                novo.custo += 1;
                novo.heuristica = calcularHeuristica(novo.estado);
                vizinhos.push_back(novo);
            }
        }
    }

    return vizinhos;
}


