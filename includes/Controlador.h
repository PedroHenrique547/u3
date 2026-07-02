#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <string>
#include <vector>
#include "Cidade.h"
#include "Trajeto.h"
#include "Transporte.h"
#include "Passageiro.h"
#include "Viagem.h"


using namespace std;


class Controlador {
private:
    vector<Cidade*> cidades;
    vector<Trajeto*> trajetos;
    vector<Transporte*> transportes;
    vector<Passageiro*> passageiros;
    vector<Viagem*> viagens; 
    
    vector<Cidade*> calcularMelhorTrajeto(Cidade* origem, Cidade* destino, enum Tipo tipo) const;
    int distanciaOtim(Cidade* a, Cidade* b, enum Tipo tipo) const ;

public:
    ~Controlador();

    // Métodos de cadastro interativos com o usuario
    void cadastrarCidade();
    void cadastrarTrajeto();
    void cadastrarTransporte();
    void cadastrarPassageiro();
    // Métodos de cadastro com parâmetros voltados para a leitura e carregamento de arquivos do sistema
    void cadastrarCidade(const string& nome);
    void cadastrarTrajeto(const string& origem, const string& destino, Tipo tipo, double distancia);
    void cadastrarTransporte(const string& nome, Tipo tipo, int capacidade, int velocidade, const string& local);
    void cadastrarPassageiro(const string& nome, const string& local);

    void iniciarViagemMenu();
    void iniciarViagem(string nome_transporte, string origem, string destino, const vector<string>& nome_passageiros);
    void avancar();
    void avançarHoras(int horas);
    void melhorTrajeto();

    void listarTransportes() const;
    void listarPassageiros() const;
    void listarMaisVisitadas() const;
    void listarCidades() const;
    void listarViagens() const;

    void carregarDados();
    void salvarDados();

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

#endif