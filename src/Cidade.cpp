#include "Cidade.h"

using namespace std;

Cidade::Cidade(string nome) : nome(nome), qttVisita(0) {}

string Cidade::getNome() const {
     return nome;
}

int Cidade::getQttVisitas() const {
     return qttVisita; 
    }

void Cidade::incrementarVisitas() { 
    qttVisita++; 
}

void Cidade::setQttVisitas(int v) { 
    qttVisita = v; 
}
