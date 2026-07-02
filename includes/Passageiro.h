#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

#include <string>
#include "Cidade.h"

using namespace std;

class Passageiro {
private:
    string nome;
    Cidade* localAtual;
    bool emViagem;

public:
    Passageiro(string nome, Cidade* localAtual);

    string getNome() const;
    Cidade* getLocalAtual() const;
    void setLocalAtual(Cidade* local);
    bool isEmViagem() const;
};

#endif