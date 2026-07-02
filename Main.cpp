#include <iostream>
#include <string>
#include <vector>
#include "Controlador.h" 

using namespace std;

class Main {
private:
    Controlador controlador;
public:
    void executar();
    void menuPrincipal();
    void menuListagens();
    void menuGestaoViagens();
};

void Main::executar() {
    controlador.carregarDados();
    
    cout << "=== Sistema Controlador de Viagens ===\n";
    menuPrincipal();
    
    controlador.salvarDados();
}

void Main::menuPrincipal() {
    int opcao;
    
    while (true) {
        cout << "\n=== MENU PRINCIPAL ===\n";
        cout << "1. Cadastrar Cidades\n";
        cout << "2. Cadastrar Trajetos\n";
        cout << "3. Cadastrar Transportes\n";
        cout << "4. Cadastrar Passageiros\n";
        cout << "5. Gestão de Viagens\n";
        cout << "6. Consultas e Relatorios\n";
        cout << "7. Salvar Dados\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                controlador.cadastrarCidade();
                break;
            case 2:
                controlador.cadastrarTrajeto();
                break;
            case 3:
                controlador.cadastrarTransporte();
                break;
            case 4:
                controlador.cadastrarPassageiro();
                break;
            case 5:
                menuGestaoViagens();
                break;
            case 6:
                menuListagens();
                break;
            case 7:
                controlador.salvarDados();
                break;
            case 0:
                cout << "Encerrando o sistema...\n";
                controlador.salvarDados();
                return;
            default:
                cout << "Opcao invalida! Tente novamente.\n";
        }
    }
}

void Main::menuGestaoViagens() {
    int opcao;
    while (true) {
        cout << "\n=== GESTÃO DE VIAGENS ===\n";
        cout << "1. Iniciar Nova Viagem\n";
        cout << "2. Escolher o transporte e passageiros\n";
        cout << "3. Registrar a partida de transporte\n";
        cout << "4. Avançar X horas e atualizar estado do sistema\n";
        cout << "5. Calcular o melhor trajeto entre cidades\n";
        cout << "0. Voltar ao Menu Principal\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                controlador.iniciarViagemMenu();
                break;
            case 2:
               controlador.listarViagens();
                break;
            case 3:
                //controlador.finalizarViagem();
                break;
            case 4:
                controlador.avancar();
                break;
            case 5:
                controlador.melhorTrajeto();
                break;
            case 0:
                return;
            default:
                cout << "Opcao invalida!\n";
        }
    }
}


void Main::menuListagens() {
    int opcao;
    while (true) {
        cout << "\n=== MENU DE CONSULTAS E RELATÓRIOS ===\n";
        cout << "1. Relatório de onde estão cada passageiros\n"; //(cidade ou em trânsito, informando origem-destino-transporte)
        cout << "2. Relatório de onde está cada transporte\n";
        cout << "3. Relatório de todas as viagens em andamento\n";
        cout << "4. Relatório das cidades mais visitadas\n";
        cout << "0. Voltar ao Menu Principal\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                controlador.listarPassageiros();
                break;
            case 2:
                controlador.listarTransportes();
                break;
            case 3:
                controlador.listarViagens();
                break;
            case 4:
                controlador.listarMaisVisitadas();
                break;
            case 0:
                return;
            default:
                cout << "Opcao invalida!\n";
        }
    }
}

// ====================== FUNÇÃO MAIN ======================
int main() {
    Main programa;
    programa.executar();
    return 0;
}