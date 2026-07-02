#ifndef TRAJETO_H
#define TRAJETO_H

#include "Cidade.h"
#include "Tipos.h"

using namespace std;

class Trajeto {
private:
    Cidade* origem;
    Cidade* destino;
    enum Tipo tipo; 
    int distancia; 

public:
    Trajeto(Cidade* origem, Cidade* destino, enum Tipo tipo, int distancia);

    Cidade* getOrigem() const;
    Cidade* getDestino() const;
    enum Tipo getTipo() const;
    int getDistancia() const;
};

#endif