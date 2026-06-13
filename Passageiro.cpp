class Passageiro {

private:
    int id;
    string nome;

    Cidade* cidadeAtual;
    
    bool emViagem;

public:
    Passageiro(int id, string nome, Cidade* cidadeAtual);

    int getId() const;
    string getNome() const;
    Cidade* getCidadeAtual() const;
    void setCidadeAtual(Cidade* cidade);
    bool isEmViagem() const;
};