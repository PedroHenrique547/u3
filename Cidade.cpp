class Cidade {

private:
    int id, visitas;
    string nome;
    
public:
    Cidade(int id, string nome);

    int getId() const;
    string getNome() const;
    int getVisitas() const;
    void incrementarVisitas();
};