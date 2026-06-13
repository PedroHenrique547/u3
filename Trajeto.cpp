enum TipoTrajeto {
    TERRESTRE,
    AQUATICO
};

class Trajeto {

public:
    string origem, destino;
    TipoTrajeto tipo;
    double distancia;
};