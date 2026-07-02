#ifndef CIDADE_H
#define CIDADE_H

#include <string>

using namespace std;

class Cidade {
private:
    string nome;
    int qttVisita;

public:
    Cidade(string nome);

    string getNome() const;

    int getQttVisitas() const;
    void incrementarVisitas();              
    void setQttVisitas(int v);        
};

#endif