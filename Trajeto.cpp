#include "Trajeto.h"

using namespace std;

Trajeto::Trajeto(Cidade* origem, Cidade* destino, enum Tipo tipo, int distancia)
    : origem(origem),
      destino(destino),
      tipo(tipo),
      distancia(distancia)
{
}

Cidade* Trajeto::getOrigem() const {
    return origem; 
}
Cidade* Trajeto::getDestino() const {
    return destino; 
}
enum Tipo Trajeto::getTipo() const {
    return tipo; 
}
int Trajeto::getDistancia() const {
    return distancia; 
}
