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

void cadastrarCidade(string nome){
    Cidade cidade;
    cidade.nome = nome;
    cidade.visitas = 0;
    cidades.push_back(cidade);
}

void cadastrarTransporte(string nome, string cidadeAtual, TipoTransporte tipo, int capacidade, double velocidade, double distanciaDescanso, double tempoDescanso){
    Transporte transporte;
    transporte.nome = nome;
    transporte.cidadeAtual = cidadeAtual;
    transporte.tipo = tipo;
    transporte.capacidade = capacidade;
    transporte.velocidade = velocidade;
    transporte.distanciaDescanso = distanciaDescanso;
    transporte.tempoDescanso = tempoDescanso;
    transporte.emViagem = false;
    transportes.push_back(transporte);
}

void cadastrarTrajeto(string origem, string destino, TipoTrajeto tipo, double distancia){
    Trajeto trajeto;
    trajeto.origem = origem;
    trajeto.destino = destino;
    trajeto.tipo = tipo;
    trajeto.distancia = distancia;
    trajetos.push_back(trajeto);
}

void cadastrarPassageiro(string nome, string cidadeAtual){
    Passageiro passageiro;
    passageiro.nome = nome;
    passageiro.cidadeAtual = cidadeAtual;
    passageiro.emViagem = false;
    passageiros.push_back(passageiro);
}
    