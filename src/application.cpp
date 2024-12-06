#include "application.hpp"
#include <sstream>
#include <algorithm>

using namespace tinyxml2;

// Construtor da classe Application
// Inicializa o estado inicial do jogo.
Application::Application(int argc, char **argv) { Inicializa(); }

// Destrutor da classe Application
Application::~Application() {}

// Função para inicializar variáveis
void Application::Inicializa() { count = 0; }
/////////////////////////////////////////////////////////////////////////////////////////////

// Exibe o estado atual do tabuleiro no console.
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

// Carrega o estado inicial a partir de um arquivo XML.
// Retorna 0 em caso de sucesso ou um código de erro caso falhe.
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

// Verifica se o estado atual é a solução desejada.
// Compara o estado atual com o estado objetivo.
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

// Rotaciona uma linha do tabuleiro para a esquerda ou direita.
void Application::rotateRow(std::vector<std::vector<std::string>> &estadoAtual, int row, char direcao)
{
    if (direcao == 'r')
        std::rotate(estadoAtual[row].rbegin(), estadoAtual[row].rbegin() + 1, estadoAtual[row].rend());
    else if (direcao == 'l')
        std::rotate(estadoAtual[row].begin(), estadoAtual[row].begin() + 1, estadoAtual[row].end());
}

/////////////////////////////////////////////////////////////////////////////////////////////

// Move o espaço vazio (representado por "vzo") no tabuleiro em uma direção (cima ou baixo).
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

// Calcula a heurística (distância de Manhattan) para o estado atual.
// A heurística mede a "distância" entre o estado atual e o estado objetivo.
int Application::calcularHeuristica(const std::vector<std::vector<std::string>> &estadoAtual)
{
    int h = 0;
    std::vector<std::vector<std::string>> estadoObjetivo = {
        {"vms", "ams", "vds", "brs"},
        {"vmm", "amm", "vdm", "brm"},
        {"vmm", "amm", "vdm", "bri"},
        {"vmi", "ami", "vdi", "vzo"}};
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            for (int x = 0; x < 4; ++x)
            {
                for (int y = 0; y < 4; ++y)
                {
                    if (estadoAtual[i][j] == estadoObjetivo[x][y])
                    {
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

// Serializa o estado do tabuleiro para uma string única.
// Útil para armazenar estados visitados.
std::string Application::serializarEstado(const std::vector<std::vector<std::string>> &estadoAtual)
{
    std::ostringstream oss;
    for (const auto &linha : estadoAtual)
        for (const auto &col : linha)
            oss << col << ",";
    return oss.str();
}

/////////////////////////////////////////////////////////////////////////////////////////////

// Resolve o jogo usando o algoritmo A* (Backtracking com heurística).
// Explora estados vizinhos e usa a distância de Manhattan para priorizar estados promissores.
#include <chrono>

// Dentro da função resolve()
bool Application::resolve()
{
    auto inicio = std::chrono::high_resolution_clock::now(); // Início da medição do tempo

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

    int movimentos = 0; // Contador de movimentos

    while (!fila.empty())
    {
        Estado atual = fila.top();
        fila.pop();

        if (is_solution(atual.estado))
        {
            auto fim = std::chrono::high_resolution_clock::now(); // Fim da medição do tempo
            std::chrono::duration<double> duracao = fim - inicio;

            std::cout << "Solução encontrada em " << duracao.count() << " segundos." << std::endl;
            std::cout << "Número de movimentos realizados: " << movimentos << std::endl;
            std::cout << "Caminho encontrado:  " << atual.caminho << std::endl;


            // Salva o estado final e ações em um arquivo XML
            salvarXML(estado, atual.caminho);

            // Atualize o estado final
            estado = atual.estado;

            // Desenhe o estado final
            draw();
            return true;
        }

        for (const auto &vizinho : gerarVizinhos(atual))
        {
            if (caminhosVisitados.find(serializarEstado(vizinho.estado)) == caminhosVisitados.end())
            {
                caminhosVisitados.insert(serializarEstado(vizinho.estado));
                fila.push(vizinho);
                movimentos++; // Incrementa o contador de movimentos
            }
        }
    }

    std::cout << "Solução não encontrada." << std::endl;
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////

// Executa o programa principal, permitindo escolher entre gerar entrada aleatória ou carregar uma existente.
int Application::exec()
{
    // Menu para escolha do tipo de entrada
    int escolha;
    std::cout << "Escolha uma opção:\n1. Criar entrada aleatória\n2. Usar entrada existente\n";
    std::cin >> escolha;

    std::vector<std::vector<std::string>> estadoInicial;

    if (escolha == 1)
    {
        // Geração de entrada aleatória com nível de dificuldade escolhido pelo usuário
        int dificuldade;
        std::cout << "Escolha a dificuldade (1 = Fácil, 2 = Médio, 3 = Difícil): ";
        std::cin >> dificuldade;

        estadoInicial = gerarEntradaAleatoria(dificuldade);
        std::cout << "Estado inicial gerado aleatoriamente.\n";
        this->estado = estadoInicial; // Atualiza o estado inicial do jogo
    }
    else
    {
        // Carregamento de uma entrada existente a partir de um arquivo XML
        std::cout << "Carregando entrada existente...\n";
        int errorID = loadXML_example("../data/EloMaluco_estadoAtual_teste01.xml");
        if (errorID)
        {
            std::cout << "Erro ao carregar XML." << std::endl;
            return -1;
        }
    }

    std::cout << "Estado inicial carregado.\n";

    // Desenha o estado inicial na tela
    draw();

    // Resolve o jogo e retorna o resultado
    return resolve() ? 0 : 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////

// Gera todos os estados vizinhos possíveis a partir de um estado atual.
// Inclui movimentos de linhas e do espaço vazio.
std::vector<Estado> Application::gerarVizinhos(const Estado &atual)
{
    std::vector<Estado> vizinhos;

    // Rotação de linhas (apenas para topo e fundo)
    for (int row : {0, 3})
    {
        for (char dir : {'l', 'r'})
        {
            Estado novo = atual;
            if (row == 0) // Linha superior
                novo.caminho += (dir == 'r') ? "R" : "L";
            else // Linha inferior
                novo.caminho += (dir == 'r') ? "r" : "l";

            rotateRow(novo.estado, row, dir);
            if (novo.estado != atual.estado)
            {
                novo.custo += 1;
                novo.heuristica = calcularHeuristica(novo.estado);
                vizinhos.push_back(novo);
            }
        }
    }

    // Movimentos do espaço vazio
    for (char dir : {'u', 'd'})
    {
        Estado novo = atual;
        novo.caminho += (dir == 'u') ? "U" : "D";
        movevzo(novo.estado, dir);
        if (novo.estado != atual.estado)
        {
            novo.custo += 1;
            novo.heuristica = calcularHeuristica(novo.estado);
            vizinhos.push_back(novo);
        }
    }

    return vizinhos;
}

void Application::salvarXML(const std::vector<std::vector<std::string>> &estadoInicial, const std::string &caminho)
{
    XMLDocument doc;

    // Criação do root
    XMLElement *root = doc.NewElement("EloMaluco");
    doc.InsertFirstChild(root);

    // Estado inicial
    XMLElement *estadoAtual = doc.NewElement("EstadoAtual");
    root->InsertEndChild(estadoAtual);

    for (const auto &linha : estadoInicial)
    {
        XMLElement *row = doc.NewElement("row");
        estadoAtual->InsertEndChild(row);
        for (const auto &col : linha)
        {
            XMLElement *celula = doc.NewElement("col");
            celula->SetText(col.c_str());
            row->InsertEndChild(celula);
        }
    }

    // Ações realizadas
    XMLElement *acoes = doc.NewElement("Acoes");
    root->InsertEndChild(acoes);

    // Tradução do caminho para ações legíveis
    for (char movimento : caminho)
    {
        XMLElement *acaoElement = doc.NewElement("acao");

        std::string acao;
        switch (movimento)
        {
        case 'R':
            acao = "rsd"; // Rotacionar linha superior para a direita
            break;
        case 'L':
            acao = "rse"; // Rotacionar linha superior para a esquerda
            break;
        case 'r':
            acao = "rid"; // Rotacionar linha inferior para a direita
            break;
        case 'l':
            acao = "rie"; // Rotacionar linha inferior para a esquerda
            break;
        case 'U':
            acao = "mfc"; // Mover face abaixo da vazia para cima
            break;
        case 'D':
            acao = "mfb"; // Mover face acima da vazia para baixo
            break;
        default:
            acao = "desconhecido"; // Caso algo inesperado ocorra
            break;
        }

        acaoElement->SetText(acao.c_str());
        acoes->InsertEndChild(acaoElement);
    }

    // Salva o arquivo XML
    doc.SaveFile("../solution/Solucao.xml");
}

std::vector<std::vector<std::string>> Application::gerarEntradaAleatoria(int dificuldade)
{
    // Define o estado resolvido
    std::vector<std::vector<std::string>> estado = {
        {"vms", "ams", "vds", "brs"},
        {"vmm", "amm", "vdm", "brm"},
        {"vmm", "amm", "vdm", "bri"},
        {"vmi", "ami", "vdi", "vzo"}};

    // Define o número de movimentos com base na dificuldade
    int movimentos = dificuldade == 1 ? 100 : (dificuldade == 2 ? 250 : 500);

    // Inicializa o gerador de números aleatórios
    std::srand(std::time(nullptr));

    for (int i = 0; i < movimentos; ++i)
    {
        // Escolhe um movimento aleatório entre R, r, L, l, u, d
        char movimento = "RrLlud"[std::rand() % 6];
        switch (movimento)
        {
        case 'R': // Rotaciona a linha superior para a direita
            rotateRow(estado, 0, 'r');
            break;
        case 'r': // Rotaciona a linha inferior para a direita
            rotateRow(estado, 3, 'r');
            break;
        case 'L': // Rotaciona a linha superior para a esquerda
            rotateRow(estado, 0, 'l');
            break;
        case 'l': // Rotaciona a linha inferior para a esquerda
            rotateRow(estado, 3, 'l');
            break;
        case 'u': // Move o espaço vazio para cima
            movevzo(estado, 'u');
            break;
        case 'd': // Move o espaço vazio para baixo
            movevzo(estado, 'd');
            break;
        }
    }

    return estado; // Retorna o tabuleiro embaralhado
}
