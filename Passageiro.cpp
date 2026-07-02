#include "Passageiro.h"

Passageiro::Passageiro(string nome, Cidade* localAtual)
    : nome(nome),
      localAtual(localAtual),
      emViagem(false)
{
}

string Passageiro::getNome() const {
    return nome;
}

Cidade* Passageiro::getLocalAtual() const {
    return localAtual;
}

void Passageiro::setLocalAtual(Cidade* cidade) {
    localAtual = cidade;
}

bool Passageiro::isEmViagem() const {
    return emViagem;
}