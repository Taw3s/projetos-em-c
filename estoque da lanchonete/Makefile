CC      = gcc
CFLAGS  = -std=c17 -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -g
BUILD   = build
TARGET  = $(BUILD)/lanchonete.exe
SRCS    = main.c

ifeq ($(OS),Windows_NT)
	MKDIR_BUILD = if not exist "$(BUILD)" mkdir "$(BUILD)"
	RUN_CMD     = .\$(BUILD)\lanchonete.exe
	CLEAN_CMD   = if exist "$(BUILD)\*.exe" del /Q "$(BUILD)\*.exe" & if exist "$(BUILD)\*.o" del /Q "$(BUILD)\*.o"
else
	MKDIR_BUILD = mkdir -p $(BUILD)
	RUN_CMD     = ./$(TARGET)
	CLEAN_CMD   = rm -f $(BUILD)/*.exe $(BUILD)/*.o
endif

all: $(TARGET)

dirs:
	$(MKDIR_BUILD)

$(TARGET): $(SRCS) | dirs
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	$(RUN_CMD)

clean:
	$(CLEAN_CMD)

help:
	@echo Comandos disponiveis:
	@echo   mingw32-make       - Compila o projeto (build/lanchonete.exe)
	@echo   mingw32-make run   - Compila e executa o programa
	@echo   mingw32-make clean - Remove os arquivos compilados em build/

.PHONY: all dirs run clean help
