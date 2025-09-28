# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Nome do executável:
TARGET = projeto

# Arquivos fonte
SRCS = main.c util.c wug.c

# Arquivos objeto (gerados automaticamente a partir de SRCS)
OBJS = $(SRCS:.c=.o)

# --- Regras de Compilação! ---

# Regra principal (default)
all: $(TARGET)

# Regra pra linkar e criar o executável final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra de padrão para compilar os arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)

# Declara regras que não geram arquivos
.PHONY: all clean

# Testes:
TEST_TARGET = testes
TEST_SRCS   = testes.c util.c wug.c
TEST_OBJS   = $(TEST_SRCS:.c=.o)

$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

clean-tests:
	rm -f $(TEST_OBJS) $(TEST_TARGET)

