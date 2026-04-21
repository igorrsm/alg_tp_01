# ==========================================
# MAKEFILE AVANÇADO (ESTRUTURA DE PASTAS)
# ==========================================

# Compilador e Flags
CXX = g++
CXXFLAGS = -Wall -Wextra -O3 -std=c++17

# Pastas do Projeto
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Onde o compilador deve procurar os arquivos .hpp (-I significa "Include")
INCLUDES = -I$(INC_DIR)

# Nome do executável final
EXEC = $(BIN_DIR)/fuga

# Lista de arquivos fonte (todos os .cpp dentro de src/)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Lista de arquivos objeto (substitui a pasta 'src/' por 'obj/' e '.cpp' por '.o')
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Regra principal (a que roda quando você digita apenas 'make')
all: $(EXEC)

# Passo 2: Junta todos os arquivos .o e cria o executável na pasta bin/
# O comando @mkdir -p garante que a pasta exista antes de tentar salvar nela
$(EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Passo 1: Compila cada .cpp da pasta src/ em um .o na pasta obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Regra para limpar os arquivos gerados (apaga as pastas obj e bin)
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Declara que 'all' e 'clean' não são nomes de arquivos, mas sim comandos
.PHONY: all clean