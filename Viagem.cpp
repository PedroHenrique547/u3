class Viagem {

private:
    int id, trechoAtual = 0, horasEmTransito;

    Transporte* transporte;
    Cidade* origem;
    Cidade* destino;
    Viagem *proxima;

    vector<Passageiro*> passageiro;
    vector<Cidade*> rota;

    double horasRestantes, distanciaPercorrida, distanciaTotal;

    bool finalizada, emAndamento;

public:
    Viagem(int id, Transporte* transporte, vector<Cidade*> rota, vector<Passageiro*> passageiro);

    int getId() const;
    void iniciarViagem();
    void avancarHoras(int horas);
    void relatarEstado();
    
    bool isEmAndamento() const;
    
    Transporte* getTransporte() const;
    Cidade* getOrigem() const;
    Cidade* getDestino() const;
    Viagem* getProxima() const;
    vector<Passageiro*> getPassageiros() const;
    vector<Cidade*> getRota() const;

};