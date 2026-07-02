#include <string>
#include <vector>

using namespace std;

class Cidade {

private:
    int visitas;
    string nome;
    
public:
    Cidade(string nome);

    string getNome() const {
         return nome; 
    };
    int getVisitas() const {
        return visitas; 
    };
    void incrementarVisitas() {
        visitas++; 
    };
};