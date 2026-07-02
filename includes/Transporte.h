#ifndef TRANSPORTE_H
#define TRANSPORTE_H

#include <string>
#include "Cidade.h"
#include "Tipos.h"

using namespace std;

class Transporte {
private:
    string nome;
    Tipo tipo;  
    int capacidade;                
    int velocidade;                         
    Cidade* localAtual;  
    bool emAndamento;          

public:
    Transporte(string nome, Tipo tipo, int capacidade, int velocidade, Cidade* localAtual);
    string getNome() const;
    Tipo getTipo() const;
    int getCapacidade() const;
    int getVelocidade() const;
    Cidade* getLocalAtual() const;
    void setLocalAtual(Cidade* local);
    bool isEmAndamento() const;
};

#endif