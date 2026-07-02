#include <vector>
#include <string>
#include <queue>
#include "Cidade.hpp"
#include "Trajeto.hpp"
#include "Transporte.hpp"
#include "Passageiro.hpp"
#include "Viagem.hpp"

using namespace std;

class Controlador {
private:
    vector<Cidade*> cidades;
    vector<Trajeto*> trajetos;
    vector<Transporte*> transportes;
    vector<Passageiro*> passageiros;
    vector<Viagem*> viagens; 

    Cidade* getCidade_Name(const string& nome) const;
    Transporte* getTransporte_Name(const string& nome) const;
    Passageiro* getPassageiro_Name(const string& nome) const;
    
    vector<int> calcularMelhorTrajeto(Cidade* origem, Cidade* destino, enum TipoTrajeto tipo) const;

public:

    void carregarDados();
    bool salvarDados();

    void cadastrarCidade();
    void cadastrarTrajeto();
    void cadastrarTransporte();
    void cadastrarPassageiro();

    void iniciarViagemMenu();
    void iniciarViagem(string nome_transporte, string origem, string destino, const vector<string>& nome_passageiros);
    void avancarHoras(int horas);

    void listarTransportes() const;
    void listarPassageiros() const;
    void listarMaisVisitadas() const;
    void listarCidades() const;

    Cidade* getCidade(string nome) const{
        for (Cidade* c : cidades) {
            if (c->getNome() == nome) return c;
        }
        return nullptr;
    }
    Transporte* getTransporte(string nome) const{
        for (Transporte* t : transportes) {
            if (t->getNome() == nome) return t;
        }
        return nullptr;
    }
    Passageiro* getPassageiro(string nome) const{
        for (Passageiro* p : passageiros) {
            if (p->getNome() == nome) return p;
        }
        return nullptr;
    }

};

void cadastrarCidade() {
    string nome;
    cout << "Nome da cidade: \n";
    cin.ignore();
    getline(cin, nome);

    if (getCidade(nome) != nullptr) {
        cout << "Está cidade já existe!\n";
        return;
    }
    cidades.emplace_back(new Cidade(nome));
    cout << "A cidade " << nome << " foi cadastrada com sucesso!\n";
}

void cadastrarTrajeto() {
    string origem, destino;
    int tipo;
    double dist;

    cout << "Cidade de Origem: \n"; 
    cin.ignore(); 
    getline(cin, origem);
    cout << "Cidade de Destino: \n"; 
    getline(cin, destino);
    cout << "o tipo de trajeto é? (0-Terrestre | 1-Aquático): \n"; 
    cin >> tipo;
    cout << "Distância (km): \n"; cin >> dist;

    Cidade* orig = getCidade(origem);
    Cidade* dest = getCidade(destino);

    if (orig == nullptr || dest == nullptr) {
        cout << "Erro: Cidade não encontrada!\n";
        return;
    }
    if (tipo != 0 && tipo != 1) {
        cout << "Erro: Tipo de trajeto inválido!\n";
        return;
    }
    if (dist <= 0) {
        cout << "Erro: Distância inválida!\n";
        return;
    }

    TipoTrajeto t = (tipo == 1) ? TipoTrajeto::A : TipoTrajeto::T;
    trajetos.emplace_back(new Trajeto(orig, dest, t, dist));
    cout << "Trajeto cadastrado!\n";
}

void cadastrarTransporte() {
    string nome;
    int tipo, cap;
    double vel, distDesc, tempoDesc;

    cout << "Nome do Transporte: \n"; 
    cin.ignore(); 
    getline(cin, nome);
    cout << "O tipo de transporte é? (0-Terrestre | 1-Aquático): \n";
    cin >> tipo;
    cout << "Capacidade do transporte: \n"; 
    cin >> cap;
    cout << "Velocidade (km/h): \n"; 
    cin >> vel;
    cout << "Dist. entre descansos (km): \n"; 
    cin >> distDesc;
    cout << "Tempo de descanso (h): \n"; 
    cin >> tempoDesc;


    if(tipo != 0 && tipo != 1) {
        cout << "Erro: Tipo de transporte inválido!\n";
        return;
    }
    TipoTrajeto t = (tipo == 1) ? TipoTrajeto::A : TipoTrajeto::T;
    transportes.emplace_back(nome, t, cap, vel, distDesc, tempoDesc);

    if (!cidades.empty()){
        transportes.back().setLocalAtual(&cidades[0]);
    }
    cout << "Transporte cadastrado!\n";
}

void cadastrarPassageiro() {
    string nome;
    cout << "Nome do Passageiro: \n"; 
    cin.ignore(); 
    getline(cin, nome);
    passageiros.emplace_back(nome);

    if (!cidades.empty())
        passageiros.back().setCidadeAtual(&cidades[0]);

    cout << "Passageiro cadastrado!\n";
}

void iniciarViagemMenu() {
    string origem, destino, transporte;
    vector<string> passageiros;
    int qtd;

    cout << "\n=== INICIAR VIAGEM ===\n";
    cout << "Origem da viagem: "; 
    cin.ignore(); 
    getline(cin, origem);
    cout << "Destino da viagem: "; 
    getline(cin, destino);
    cout << "Transporte: "; 
    getline(cin, transporte);
    cout << "Quantos passageiros? "; 
    cin >> qtd;
    cin.ignore();

    for (int i = 1; i <= qtd; i++) {
        string nome;
        cout << "Passageiro " << i << ": ";
        getline(cin, nome);
        if (!nome.empty()) passageiros.push_back(nome);
    }

    iniciarViagem(transporte, origem, destino, passageiros);
}

void iniciarViagem(string nome_transp, string origem, string destino, const vector<string>& nomesPassageiros) {
    Transporte* transp = getTransporte(nome_transp);
    Cidade* o= getCidade(origem);
    Cidade* d= getCidade(destino);

    // Checagem inicial de validação dos parâmetros, como destino, transporte e cidade departida--
    if (!transp) { 
        cout << "Erro: Transporte não existe, nome incorreto ou encontrado.\n"; 
        return; 
    }
    if (!o || !d) { 
        cout << "Erro: Cidade não existe, nome incorreto ou não encontrada.\n"; 
        return; 
    }
    if (transp->getCidadeAtual() != o) {
        cout << "Erro: O transporte não está na cidade de partida/origem.\n";
        return;
    }

    // Faz a validação dos passageiros
    vector<Passageiro*> l;
    for (const string& nome : nomesPassageiros) {
        Passageiro* p = getPassageiro(nome);
        if (!p) { 
            cout << "Erro: O passageiro " << nome << " não foi encontrado ou não é cadastrado.\n";
             return;
        }
        if (p->getCidadeAtual() != o) {
            cout << "Erro: O passageiro " <<nome<< " não está na cidade de partida/origem.\n";
            return;
        }
        l.push_back(p);
    }

    // Faz a validação da capacidade atual do transporte em relação ao número de passageiros
    int tam = l.size();
    if (tam > transp->getCapacidade()) {
        cout << "Erro: O número de passageiros excede a capacidade atual do transporte.\n";
        return;
    }

    // Gera a rota utilizando o algoritmo de Dijkstra, com restrito ao tipo do transporte
    vector<Cidade*> rota = calcularMelhorTrajeto(o, d, transp->getTipo());

    // Verifica se há rota válida (válida = houve retorno e não está vazia)
    if (!rota.empty()) {
        // Inicia o encadeamento das viagens
        Viagem* inicial = nullptr;
        Viagem* ant = nullptr;
        int otimizado;
        for (int i = 0; i + 1 < rota.size(); i++) {
            Cidade* a = rota[i];
            Cidade* b = rota[i + 1];
            int dist = distanciaOtim(a, b, transp->getTipo(), otimizado);
            Viagem* v = new Viagem(transp, l, a, b, dist);
            if (!inicial) {
                inicial = v;
            }
            if (ant) {
                ant->setProxima(v);
            }
            ant = v;
        }

        inicial->iniciar(); 
        viagens.push_back(inicial);

        cout << "A viagem foi iniciada!\nRota inicial: ";
        for (int i = 0; i < rota.size(); i++) {
            cout << rota[i]->getNome();
            if (i + 1 < rota.size()){
                cout << " - ";
            }
        }
        cout << "\n";
        return;
    }
    
    cout << "Erro: não existe rota possível entre as cidades para esse tipo de transporte.\n";
    return;
}

// Função pra avançar 1 hora em todas as viagens em andamento
void avancarHoras(int horas) {
    if (horas <= 0) {
        return;
    }

    for (int i = 0; i < horas; i++) {
        for (Viagem* viagem : viagens) {
            Viagem* atual = viagem;
            while (atual) {
                if (!atual->isFinalizada() && atual->isEmAndamento()) {
                   // bool finalizada = atual->avancarHoras(1);
                }
                atual = atual->getProxima();
            }
        }
    }
    cout << horas << " horas avançadas.\n";
}

// ====================== RELATÓRIOS ======================
void listarCidades() {
    cout << "\n=== CIDADES ===\n";
    for (size_t i = 0; i < cidades.size(); i++)
        cout << i << " - " << cidades[i].getNome() << endl;
}

void listarTransportes() {
    cout << "\n=== TRANSPORTES ===\n";
    for (const auto& t : transportes) {
        string local = t.getLocalAtual() ? t.getLocalAtual()->getNome() : "Em trânsito";
        cout << t.getNome() << " | " << local << endl;
    }
}

void listarPassageiros() {
    cout << "\n=== PASSAGEIROS ===\n";
    for (const auto& p : passageiros) {
        string local = p.getCidadeAtual() ? p.getCidadeAtual()->getNome() : "Em trânsito";
        cout << p.getNome() << " | " << local << endl;
    }
}

void listarViagens() {
    cout << "\n=== VIAGENS EM ANDAMENTO ===\n";
    bool tem = false;
    for (const auto& v : viagens) {
        if (!v->isFinalizada() && v->isEmAndamento()) {
            cout << "Viagem " << v->getId() << ": " 
                 << v->getOrigem()->getNome() << " → " 
                 << v->getDestino()->getNome() << endl;
            tem = true;
        }
    }
    if (!tem) cout << "Nenhuma viagem em andamento.\n";
}

void distanciaOtim(Cidade* a, Cidade* b, enum TipoTransporte tipo, int& ref) const {
    for (Trajeto* t : trajetos) {
        if (t->getTipo() != tipo) {
            continue;
        }
        bool check = (t->getOrigem() == a && t->getDestino() == b) || (t->getOrigem() == b && t->getDestino() == a);
        if (check) {
            if (ref == -1 || t->getDistancia() < ref)
                ref = t->getDistancia();
        }
    }
}