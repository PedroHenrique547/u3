#ifndef VIAGEM_H
#define VIAGEM_H

#include <vector>
#include "Transporte.h"
#include "Passageiro.h"
#include "Cidade.h"

using namespace std;

class Viagem {
private:
    Transporte* transporte;
    vector<Passageiro*> passageiros;
    Cidade* origem;
    Cidade* destino;
    int distancia;   
    Viagem* proxima; 

    bool emAndamento;  
    bool finalizada;  
    
public:
    Viagem(Transporte* transporte, vector<Passageiro*> passageiros,
           Cidade* origem, Cidade* destino, int distancia);

    void iniciar();        
    void avançarHoras(int horas);  

    Cidade* getOrigem() const;
    Cidade* getDestino() const;
    Transporte* getTransporte() const;
    const vector<Passageiro*>& getPassageiros() const;
    int getDistancia() const;

    bool isEmAndamento() const;
    bool isFinalizada() const;

    void setProxima(Viagem* p);
    Viagem* getProxima() const;
};

#endif