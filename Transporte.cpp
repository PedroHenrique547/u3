enum TipoTransporte {
    T_TERRESTRE,
    T_AQUATICO
};

class Transporte {

public:
    string nome, cidadeAtual;
    TipoTransporte tipo;

    int capacidade;
    double velocidade, distanciaDescanso, tempoDescanso;

    bool emViagem;
};