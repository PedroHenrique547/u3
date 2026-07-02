#include "Viagem.h"

Viagem::Viagem(Transporte* transporte,
               vector<Passageiro*> passageiros,
               Cidade* origem,
               Cidade* destino,
               int distancia)
    : transporte(transporte),
      passageiros(passageiros),
      origem(origem),
      destino(destino),
      distancia(distancia),
      proxima(nullptr),
      emAndamento(false),
      finalizada(false)
{
}

void Viagem::iniciar() {
    emAndamento = true;
}

void Viagem::avançarHoras(int horas) {
    (void)horas;
}

Cidade* Viagem::getOrigem() const {
    return origem;
}

Cidade* Viagem::getDestino() const {
    return destino;
}

Transporte* Viagem::getTransporte() const {
    return transporte;
}

const vector<Passageiro*>& Viagem::getPassageiros() const {
    return passageiros;
}

int Viagem::getDistancia() const {
    return distancia;
}

bool Viagem::isEmAndamento() const {
    return emAndamento;
}

bool Viagem::isFinalizada() const {
    return finalizada;
}

void Viagem::setProxima(Viagem* p) {
    proxima = p;
}

Viagem* Viagem::getProxima() const {
    return proxima;
}