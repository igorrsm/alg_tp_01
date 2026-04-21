#include "fuga_dcc.hpp"

using namespace std;

void FugaDcc::ler_entradas() {

    cin >> _linhas_mapa >> _colunas_mapa;

    if(_linhas_mapa <= 0 or _colunas_mapa <= 0) {
        cout << "NO" << endl;
        exit(0);
    }

    _mapa.resize(_linhas_mapa);


    //inicialização das "matrizes" que serão utilizadas no algoritmo de busca.
    //-1 para aqueles locais que ainda não foram visitados.
    //X para o local que não foi visitado e não é proveniente de alguma ação - U D R L
    _distancia_calouros.assign(_linhas_mapa, vector<int>(_colunas_mapa, -1));
    _distancia_veterano.assign(_linhas_mapa, vector<int>(_colunas_mapa, -1));
    _movimentos_fuga.assign(_linhas_mapa, vector<char>(_colunas_mapa, 'X'));

    for(int linha = 0; linha < _linhas_mapa; linha++) {
        
        cin >> _mapa[linha];

        for(int coluna = 0; coluna < _colunas_mapa; coluna++) {
            
            if(_mapa[linha][coluna] == 'A') {
                _posicao_inicial_veterano = {linha, coluna};
                _distancia_veterano[linha][coluna] = 0;
                _fila_veterano.push({linha, coluna});
            }
                
            else if(_mapa[linha][coluna] == 'M') {
                _posicao_inicial_calouros.push_back({linha, coluna});
                _distancia_calouros[linha][coluna] = 0;
                _fila_calouros.push({linha, coluna});
            }        
        }
    }
};

//Propósito do código: 
//funcionar como uma busca em largura para os calouros. Identificar as menores distâncias dos caminhos a percorrer, a partir dos calouros.
//Esses valores são armazenados em uma matriz de adjacência distancia_calouros.
void FugaDcc::bfs_distancia_calouros() {

    while(!_fila_calouros.empty()) {
        Posicao_mapa posicao_atual = _fila_calouros.front();
        _fila_calouros.pop();

        for(int posicao = 0; posicao < 4; posicao++) {
            int vizinho_linha = posicao_atual.linha + _direcao_linhas[posicao];
            int vizinho_coluna = posicao_atual.coluna + _direcao_colunas[posicao];

            bool coordenadas_validas = (vizinho_linha < _linhas_mapa && vizinho_linha >= 0 && vizinho_coluna < _colunas_mapa && vizinho_coluna >= 0);
            
            if(coordenadas_validas) {
                bool nao_e_parede = _mapa[vizinho_linha][vizinho_coluna] != '#';
                bool coordenada_nao_visitada = _distancia_calouros[vizinho_linha][vizinho_coluna] == -1;

                if(nao_e_parede && coordenada_nao_visitada) {
                    _distancia_calouros[vizinho_linha][vizinho_coluna] = _distancia_calouros[posicao_atual.linha][posicao_atual.coluna] + 1;
                    _fila_calouros.push({vizinho_linha, vizinho_coluna});
                }
            }
        }
    }
};

bool FugaDcc::bfs_avaliar_fuga() {

    while(!_fila_veterano.empty()) {
        Posicao_mapa posicao_atual = _fila_veterano.front();
        _fila_veterano.pop();

        if(posicao_atual.linha == 0 || posicao_atual.linha == _linhas_mapa - 1 ||
           posicao_atual.coluna == 0 || posicao_atual.coluna == _colunas_mapa - 1) {
            
            _posicao_saida = posicao_atual;
            return true;
           }

        for(int posicao = 0; posicao < 4; posicao++) {
            int vizinho_linha = posicao_atual.linha + _direcao_linhas[posicao];
            int vizinho_coluna = posicao_atual.coluna + _direcao_colunas[posicao];

            bool coordenadas_validas = (vizinho_linha < _linhas_mapa && vizinho_linha >= 0 && vizinho_coluna < _colunas_mapa && vizinho_coluna >= 0);

            if(coordenadas_validas) {
                bool nao_e_parede = _mapa[vizinho_linha][vizinho_coluna] != '#';
                bool coordenada_nao_visitada_veterano = _distancia_veterano[vizinho_linha][vizinho_coluna] == -1;

                if(nao_e_parede && coordenada_nao_visitada_veterano) {
                    int distancia_deslocada_veterano = _distancia_veterano[posicao_atual.linha][posicao_atual.coluna] + 1;
                    int distancia_deslocada_calouros = _distancia_calouros[vizinho_linha][vizinho_coluna];

                    bool posicao_segura = (distancia_deslocada_calouros == -1 || distancia_deslocada_veterano < distancia_deslocada_calouros);

                    if(posicao_segura) {
                        _distancia_veterano[vizinho_linha][vizinho_coluna] = distancia_deslocada_veterano;
                        _movimentos_fuga[vizinho_linha][vizinho_coluna] = _direcao_letras[posicao];
                        _fila_veterano.push({vizinho_linha, vizinho_coluna});
                    }
                }
            }
        }
    }

    return false;
};

void FugaDcc::encontrar_caminho_fuga() {

    bfs_distancia_calouros();

    bool fuga_bem_sucedida = bfs_avaliar_fuga();

    if(!fuga_bem_sucedida) {
        cout << "NO" << endl;
        exit(0);
    }

    cout << "YES" << endl;
    string caminho = "";
    Posicao_mapa posicao_atual = _posicao_saida;

    while(_movimentos_fuga[posicao_atual.linha][posicao_atual.coluna] != 'X') {
        char direcao = _movimentos_fuga[posicao_atual.linha][posicao_atual.coluna];
        caminho += direcao;

        if(direcao == 'U')
            posicao_atual.linha = posicao_atual.linha + _direcao_linhas[1];
        else if (direcao == 'D')
            posicao_atual.linha = posicao_atual.linha + _direcao_linhas[0];
        else if (direcao == 'L')
            posicao_atual.coluna = posicao_atual.coluna + _direcao_colunas[3];
        else if (direcao == 'R')
            posicao_atual.coluna = posicao_atual.coluna + _direcao_colunas[2];
    }

    reverse(caminho.begin(), caminho.end());

        cout << caminho.length() << endl;
        cout << caminho << endl;
};