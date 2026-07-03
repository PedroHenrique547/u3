# Sistema Controlador de Viagens - LIP_UFRN 
 Trabalho final de Linguagem de Programacao I, em C++ com Programacao Orientada a Objetos.
 Aluno: Pedro Henrique Fernandes Silva - 20250043255.
 O sistema utiliza apenas o modo de uso via **Terminal (CLI)**

---

## Requisitos

- Um compilador `g++` com suporte a C++15.2.0 ou superior.
  - **No Windows**, a forma recomendada e instalar o **MSYS2** (https://www.msys2.org)
    e, no terminal do MSYS2, rodar:
    `pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make`
    Depois adicione `C:\msys64\ucrt64\bin` ao PATH do Windows e reinicie o VS Code.
- 

---

## Passo a passo para rodar utilizando o Windows + VS Code

### 1. Abra a pasta do projeto no VS Code (File -> Open Folder)
 aperte as teclas (Ctrl+crase) pra abrir o terminal integrado do VS Code, e ao abrir o terminal da raiz
 digite `dir` para verificar se está na raiz do projeto.

### 2. Compilar
Após estar no terminal integrado, digite o seguinte comando pra compilar os arquivos:

```powershell
g++ *.cpp src\*.cpp -Iincludes -o programa.exe
```

---

### 3. Executar
Após a compilação do projeto e não retornar nenhum erro no terminal, digite o seguinte comando pra iniciar o projeto:

```powershell
.\programa.exe
```
---

Isso vai gerar um terminal `programa.exe`

## Estrutura do projeto

```
u3/
├── include/      # headers
├── data/         # dados
├── src/          # implementacoes
├── main.cpp      # interface via Terminal (CLI)
```

## As classes

- **Controlador** — classe de gerenciamento: realiza cadastros, listagens/relatorio, checagem de melhores rotas,
  avanco do tempo de viagens (inativo).

- **Cidade** — Classe da cidade; onde armazena nome e contador de visitas, juntamente com seus gettes e settes.
- **Passageiro** — Classe de pessoa; onde armazena nome e cidade atual (**localAtual = nullptr** quando em transito).
- **Trajeto** — Classe de direcionamento entre duas cidades A -> B, com tipo do **Trajeto** sendo (T/A) e distância, podendo ser bidirecional.
- **Transporte** — Classe de Veiculo, onde armazena o tipo, a capacidade e a velocidade.
- **Viagem** — Classe de trajeto. onde armazena transporte, a rota (origem e destino X -> Y), distancia entre os pontos e se está em  viagem. 
- **Tipos** - Classe de tipos, onde generaliza e resume o uso de char ao utilizar o enum.

## Decisoes de modelagem

- **Melhor trajeto**: utiliza o algoritmo de Dijkstra pra fazer a checagem da menor distancia (do ponto A -> B) ao      utilizar o mesmo tipo de transporte.

- **Persistencia**: salva e lê os arquivos `.txt`, separados por `-`.