#ifndef FUGADCC_HPP
#define FUGADCC_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

struct Posicao_mapa {
    int linha; 
    int coluna;
};

class FugaDcc {

        private:
            int _linhas_mapa;
            int _colunas_mapa;
            
            std::vector<std::string> _mapa;
            std::vector<std::vector<int>> _distancia_calouros;
            std::vector<std::vector<int>> _distancia_veterano;
            std::vector<std::vector<char>> _movimentos_fuga;
            std::queue<Posicao_mapa> _fila_calouros;
            std::queue<Posicao_mapa> _fila_veterano;

            Posicao_mapa _posicao_inicial_veterano;
            std::vector<Posicao_mapa> _posicao_inicial_calouros;

            int _direcao_linhas[4] = {-1, 1, 0, 0};
            int _direcao_colunas[4] = {0, 0, -1, 1};
            Posicao_mapa _posicao_saida;

            char _direcao_letras[4] = {'U', 'D', 'L', 'R'};

            void bfs_distancia_calouros();
            bool bfs_avaliar_fuga();

        public:

            void ler_entradas();
            void encontrar_caminho_fuga();

};

#endif