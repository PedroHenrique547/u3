#include "Controlador.h"
#include <vector>
#include <string>

#include <algorithm>
#include <limits>
#include <queue>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Construtor e Destrutor pra limpar a memória alocada dinamicamente
Controlador::~Controlador() {
    for (Cidade* c : cidades) {
        delete c;
    }
    for (Trajeto* t : trajetos) {
        delete t;
    }
    for (Transporte* t : transportes) {
        delete t;
    } 
       for (Passageiro* p : passageiros) {
        delete p;
    }
    for (Viagem* v : viagens) {
        Viagem* atual = v;
        while (atual != nullptr) {
            Viagem* prox = atual->getProxima();
            delete atual;
            atual = prox;
        }
    }
}


void Controlador::cadastrarCidade() {
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

void Controlador::cadastrarTrajeto() {
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

    Tipo t = (tipo == 1) ? Tipo::A : Tipo::T;
    trajetos.emplace_back(new Trajeto(orig, dest, t, dist));
    cout << "Trajeto cadastrado!\n";
}

void Controlador::cadastrarTransporte() {
    string nome, local;
    int tipo, cap;
    double vel;

    cout << "Nome do Transporte: \n"; 
    cin.ignore(); 
    getline(cin, nome);
    cout << "O tipo de transporte é? (0-Terrestre | 1-Aquático): \n";
    cin >> tipo;
    cout << "Capacidade do transporte: \n"; 
    cin >> cap;
    cout << "Velocidade (km/h): \n"; 
    cin >> vel;
    cout << "Cidade de origem do transporte: \n"; 
    cin.ignore();   
    getline(cin, local);

    Cidade* localAtual = getCidade(local);
    if (!localAtual) {
        cout << "Erro: Cidade de origem não encontrada!\n";
        return;
    }

    if(tipo != 0 && tipo != 1) {
        cout << "Erro: Tipo de transporte inválido!\n";
        return;
    }
    Tipo t = (tipo == 1) ? Tipo::A : Tipo::T;
    transportes.emplace_back(new Transporte(nome, t, cap, vel, localAtual));

    cout << "Transporte cadastrado!\n";
}

void Controlador::cadastrarPassageiro() {
    string nome, local;
    cout << "Nome do Passageiro: \n"; 
    cin.ignore(); 
    getline(cin, nome);
    cout << "Cidade de origem do passageiro: \n"; 
    getline(cin, local);

    Cidade* localAtual = getCidade(local);
    if (!localAtual) {
        cout << "Erro: Cidade de origem não encontrada!\n";
        return;
    }

    passageiros.emplace_back(new Passageiro(nome, localAtual));

    cout << "Passageiro cadastrado!\n";
}

void Controlador::iniciarViagemMenu() {
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

void Controlador::iniciarViagem(string nome_transp, string origem, string destino, const vector<string>& nomesPassageiros) {
    Transporte* transp = getTransporte(nome_transp);
    Cidade* o = getCidade(origem);
    Cidade* d = getCidade(destino);

    // Checagem inicial de validação dos parâmetros, como destino, transporte e cidade departida--
    if (!transp) { 
        cout << "Erro: Transporte não existe, nome incorreto ou encontrado.\n"; 
        return; 
    }
    if (!o || !d) { 
        cout << "Erro: Cidade não existe, nome incorreto ou não encontrada.\n"; 
        return; 
    }
    if (transp->getLocalAtual() != o) {
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
        if (p->getLocalAtual() != o) {
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

void Controlador::avancar(){
    int horas;
    cout << "Quantas horas deseja avançar? ";
    cin >> horas;
    avançarHoras(horas);
}
// Função pra avançar 1 hora em todas viagens em andamento
void Controlador::avançarHoras(int horas) {
    if (horas <= 0) {
        return;
    }

    for (int i = 0; i < horas; i++) {
        for (Viagem* viagem : viagens) {
            Viagem* atual = viagem;
            while (atual) {
                if (!atual->isFinalizada() && atual->isEmAndamento()) {
                    atual->avançarHoras(horas);
                }
                atual = atual->getProxima();
            }
        }
    }
    cout << horas << " horas avançadas.\n";
}

// ====================== RELATÓRIOS ======================
void Controlador::listarCidades() const{
    cout << "\n=== CIDADES ===\n";
    if(cidades.empty()) {
        cout << "Nenhuma cidade cadastrada.\n";
        return;
    }
    for (int i = 0; i < cidades.size(); i++)
        cout << i << "º " << cidades[i]->getNome() << endl;
}

void Controlador::listarTransportes() const{
    cout << "\n=== TRANSPORTES ===\n";
    if(transportes.empty()) {
        cout << "Nenhum transporte cadastrado.\n";
        return;
    }
    for (Transporte* t : transportes) {
        if(t->getLocalAtual() == nullptr) {
            cout << t->getNome() << " | Em trânsito" << endl;
        } else {
            cout << t->getNome() << " está em " << t->getLocalAtual()->getNome() << endl;
        }
    }
}

void Controlador::listarPassageiros() const{
    cout << "\n=== PASSAGEIROS ===\n";
    if(passageiros.empty()) {
        cout << "Nenhum passageiro cadastrado.\n";
        return;
    }
    for (Passageiro* p : passageiros) {
        if(p->isEmViagem()) {
            cout << p->getNome() << " | Em trânsito" << endl;
        }else{
            cout << p->getNome() << " está em " << p->getLocalAtual()->getNome() << endl;
            for(Viagem* v : viagens) {
                Viagem* atual = v;
                while (atual) {
                    const vector<Passageiro*>& ps = atual->getPassageiros();
                    if (find(ps.begin(), ps.end(), p) != ps.end()) {
                        cout << "  Origem: " << atual->getOrigem()->getNome() 
                             << " | Destino: " << atual->getDestino()->getNome() 
                             << " | Transporte: " << atual->getTransporte()->getNome() << endl;
                        break;
                    }
                    atual = atual->getProxima();
                }
            }
        }
        cout << endl;
    }
}

void Controlador::listarViagens() const{
    int x = 1;
    bool possui = false;

    cout << "\n=== VIAGENS EM ANDAMENTO ===\n";
    if(viagens.empty()) {
        cout << "Nenhuma viagem cadastrada.\n";
        return;
    }
    for (Viagem* v : viagens) {
        Viagem* atual = v;
        while (atual) {
            if (!atual->isFinalizada() && atual->isEmAndamento()) {
                cout << "Viagem " << x << ": " 
                     << "\nOrigem: " << atual->getOrigem()->getNome() << " → " 
                     << "Destino: " << atual->getDestino()->getNome() << endl;
                possui = true;
                x++;
            }
            atual = atual->getProxima();
        }
    }
    if (!possui){
        cout << "Nenhuma viagem em andamento.\n";
    } 
}

void Controlador::listarMaisVisitadas() const{
    cout << "\n CIDADES MAIS VISITADAS \n";

    if(cidades.empty()) {
        cout << "Nenhuma cidade cadastrada.\n";
        return;
    }
    vector<Cidade*> copia = cidades;
    sort(copia.begin(), copia.end(), [](Cidade* a, Cidade* b) {
        return a->getQttVisitas() > b->getQttVisitas();
    });

    for (Cidade* c : copia) {
        cout << c->getNome() << " | Visitas: " << c->getQttVisitas() << endl;
    }
}

void Controlador::melhorTrajeto(){
    string o, d;
    int op;

    cout << "Cidade de origem: ";
    cin >> o;
    cout << "Cidade de destino: ";
    cin >> d;

    cout << "Tipo de transporte:\n 1 - Terrestre\n 2 - Aquático\nEscolha: ";
    cin >> op;

    Tipo tipo;

    tipo = (op == 1) ? T : A;

    Cidade* origem = getCidade(o);
    Cidade* destino = getCidade(d);

    if (!origem || !destino) {
        cout << "Cidade não encontrada.\n";
        return;
    }

    vector<Cidade*> rota = calcularMelhorTrajeto(origem, destino, tipo);

    if (rota.empty()) {
        cout << "Não existe rota possível entre as cidades para esse tipo de transporte.\n";
        return;
    }

    cout << "Melhor rota: ";

    for (size_t i = 0; i < rota.size(); i++) {
        cout << rota[i]->getNome();

        if (i + 1 < rota.size())
            cout << " -> ";
    }

    cout << endl;
}

vector<Cidade*> Controlador::calcularMelhorTrajeto(Cidade* origem, Cidade* destino, Tipo tipo) const {
    const int MAX = numeric_limits<int>::max();
    int tam = cidades.size();

    auto index = [&](Cidade* c) -> int {
        for (int i = 0; i < tam; i++) {
            if (cidades[i] == c)
                return i;
        }
        return -1;
    };

    int ini = index(origem);
    int fin = index(destino);

    if (ini == -1 || fin == -1){
        return {};
    }
    vector<int> dist(tam, MAX);
    vector<int> anterior(tam, -1);

    dist[ini] = 0;

    using Par = pair<int, int>;
    priority_queue<Par, vector<Par>, greater<Par>> fila;
    fila.push({0, ini});

    while (!fila.empty()) {
        auto [d, u] = fila.top();
        fila.pop();

        if (d > dist[u]){
            continue;
        }
        for (int v = 0; v < tam; v++) {
            if (v == u){
                continue;
            }
            int retorno;
            retorno = distanciaOtim(cidades[u], cidades[v], tipo, retorno);

            if (retorno < 0){
                continue;
            }
            if (dist[u] != MAX && dist[u] + retorno < dist[v]) {
                dist[v] = dist[u] + retorno;
                anterior[v] = u;
                fila.push({dist[v], v});
            }
        }
    }
    if (dist[fin] == MAX){
        return {};
    }
    vector<Cidade*> result;

    for (int i = fin; i != -1; i = anterior[i]) {
        result.push_back(cidades[i]);
    }
    reverse(result.begin(), result.end());
    return result;
}

int Controlador::distanciaOtim(Cidade* a, Cidade* b, Tipo tipo, int& ref) const {
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
    return ref;
}

//----- CARREGAR DADOS ---

void Controlador::carregarDados() {
    // Implementação para carregar dados de arquivos futuramente
}

void Controlador::salvarDados() {
    // Implementação para salvar dados em arquivos futuramente
}