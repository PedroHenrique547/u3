#include <string>
#include <vector>

using namespace std;

enum TipoTrajeto {
    T,
    A
};

class Trajeto {

private:
    Cidade* origem; 
    Cidade* destino;
    TipoTrajeto tipo;
    double distancia;

public:
    Trajeto(Cidade* origem, Cidade* destino, enum TipoTrajeto tipo, int distancia);

    Cidade* getOrigem() const {
        return origem; 
    };
    Cidade* getDestino() const {
        return destino; 
    };
    enum TipoTrajeto getTipo() const {
        return tipo; 
    };
    int getDistancia() const {
        return distancia; 
    };
};