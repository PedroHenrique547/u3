#include <string>
#include <vector>

using namespace std;

enum TipoTransporte {
    T_TERRESTRE,
    T_AQUATICO
};

class Transporte {

private:

    int capacidade, velocidade, distanciaDescanso, tempoDescanso;
    string nome;

    TipoTransporte tipo;
    Cidade* cidadelocal;

    bool emAndamento;

public:
    Transporte(string nome, enum TipoTransporte tipo, int capacidade, int velocidade,
               int distancia_descanso, int tempo_descanso, Cidade* localAtual);

    string getNome() const {
        return nome; 
    };
    enum TipoTransporte getTipo() const {
        return tipo; 
    };
    int getCapacidade() const {
        return capacidade; 
    };
    int getVelocidade() const {
        return velocidade; 
    };
    
    Cidade* getCidadeAtual() const {
        return cidadelocal; 
    };

    void setLocalAtual(Cidade* local) {
        cidadelocal = local; 
    };
    bool isEmAndamento() const {
        return emAndamento; 
    };
};