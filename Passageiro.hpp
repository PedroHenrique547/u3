#include <string>
#include <vector>

using namespace std;

class Passageiro {

private:
    int id;
    string nome;

    Cidade* cidadeAtual;
    
    bool emViagem;

public:
    Passageiro(int id, string nome, Cidade* cidadeAtual);

    int getId() const {
        return id; 
    };
    string getNome() const {
        return nome; 
    };
    Cidade* getCidadeAtual() const {
        return cidadeAtual; 
    };
    void setCidadeAtual(Cidade* cidade) {
        cidadeAtual = cidade; 
    };
    bool isEmViagem() const {
        return emViagem; 
    };
};