#include "Transporte.h"

using namespace std;

Transporte::Transporte(string nome, Tipo tipo, int capacidade, int velocidade, Cidade* localAtual)
    : nome(nome),
      tipo(tipo),
      capacidade(capacidade),
      velocidade(velocidade),
      localAtual(localAtual),
      emAndamento(false)
{
}

string Transporte::getNome() const {
    return nome; 
}
enum Tipo Transporte::getTipo() const {
    return tipo; 
}
int Transporte::getCapacidade() const {
    return capacidade; 
}
int Transporte::getVelocidade() const {
    return velocidade; 
}
Cidade* Transporte::getLocalAtual() const {
    return localAtual; 
}
void Transporte::setLocalAtual(Cidade* local) {
    localAtual = local; 
}
bool Transporte::isEmAndamento() const {
    return emAndamento; 
}
