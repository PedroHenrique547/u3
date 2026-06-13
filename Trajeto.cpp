enum TipoTrajeto {
    T,
    A
};

class Trajeto {

private:
    int id;
    Cidade* origem; 
    Cidade* destino;
    TipoTrajeto tipo;
    double distancia;

public:
    Trajeto(int id, Cidade* origem, Cidade* destino, enum tipo, int distancia);

    int getId() const;
    Cidade* getOrigem() const;
    Cidade* getDestino() const;
    char getTipo() const;
    int getDistancia() const;
};