CC       = gcc
CXX      = g++
INCLUDES = -Iinclude
CFLAGS   = -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference -g $(INCLUDES)
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -g $(INCLUDES)

OBJ_DIR  = build/obj
BIN_DIR  = build/bin

TARGET   = $(BIN_DIR)/programa.exe
BENCH    = $(BIN_DIR)/bench.exe
LEITOR   = $(BIN_DIR)/leitor.exe

C_OBJS   = $(OBJ_DIR)/main.o $(OBJ_DIR)/vetor.o
EXTRAS   = $(BENCH) $(LEITOR)

ifeq ($(OS),Windows_NT)
	MKDIR_DIRS = if not exist "build\obj" mkdir "build\obj" && if not exist "build\bin" mkdir "build\bin"
	RUN_PREFIX = .\$(subst /,\,$1)
	RM_CLEAN   = del /Q "build\obj\*.o" "build\bin\*.exe" 2>nul || exit 0
else
	MKDIR_DIRS = mkdir -p $(OBJ_DIR) $(BIN_DIR)
	RUN_PREFIX = ./$1
	RM_CLEAN   = rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*.exe
endif

all: $(TARGET)

extras: $(EXTRAS)

dirs:
	$(MKDIR_DIRS)

$(TARGET): $(C_OBJS) | dirs
	$(CC) $(CFLAGS) -o $@ $(C_OBJS)

$(BENCH): $(OBJ_DIR)/bench.o $(OBJ_DIR)/vetor.o | dirs
	$(CXX) $(CXXFLAGS) -o $@ $^

$(LEITOR): $(OBJ_DIR)/leitor.o $(OBJ_DIR)/vetor.o | dirs
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: src/%.c include/vetor.h | dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: extras/%.cpp include/vetor.h | dirs
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	$(call RUN_PREFIX,$(TARGET))

run-bench: $(BENCH)
	$(call RUN_PREFIX,$(BENCH))

run-leitor: $(LEITOR)
	$(call RUN_PREFIX,$(LEITOR)) data/notas.txt

clean:
	$(RM_CLEAN)

help:
	@echo Comandos disponiveis:
	@echo   mingw32-make            - Compila o programa principal (build/bin/programa.exe)
	@echo   mingw32-make extras     - Compila os auxiliares C++ (bench.exe e leitor.exe)
	@echo   mingw32-make run        - Compila e executa programa.exe
	@echo   mingw32-make run-bench  - Executa o benchmark (C vs std::vector)
	@echo   mingw32-make run-leitor - Executa o leitor lendo data/notas.txt
	@echo   mingw32-make clean      - Remove arquivos gerados em build/obj e build/bin

.PHONY: all extras dirs run run-bench run-leitor clean help
