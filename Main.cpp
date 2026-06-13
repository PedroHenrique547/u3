class Main{
    private:
        vector<Transporte> transportes;
        vector<Passageiro> passageiros;
        vector<Trajeto> trajetos;

    public:
        void cadastrarTransporte(string nome, string cidadeAtual, TipoTransporte tipo, int capacidade, double velocidade, double distanciaDescanso, double tempoDescanso);
        void cadastrarTrajeto(string origem, string destino, TipoTrajeto tipo, double distancia);
        void cadastrarCidade(string nome);

}