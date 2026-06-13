enum TipoTransporte {
    T_TERRESTRE,
    T_AQUATICO
};

class Transporte {

private:

    int id, capacidade, velocidade, distanciaDescanso, tempoDescanso, tempoDescansoAtual;
    string nome;

    TipoTransporte tipo;
    Cidade* cidadelocal;

    bool emViagem;

private:
    public:
    Transporte(int id, string nome, enum tipo, int capacidade, int velocidade,
               int distancia_descanso, int tempo_descanso, Cidade* localAtual);

    int getId() const;
    string getNome() const;
    char getTipo() const;
    int getCapacidade() const;
    int getVelocidade() const;
    int getDistanciaEntreDescansos() const;
    int getTempoDescanso() const;
    int getTempoDescansoAtual() const;
    Cidade* getLocalAtual() const;

    void setLocalAtual(Cidade* local);
    void resetarDescanso();
};