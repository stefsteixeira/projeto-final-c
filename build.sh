set -e
# monta a lista de fontes que EXISTEM
SRCS="testes.c hello.c util.c"
[ -f util0.c ] && SRCS="$SRCS util0.c"   # só adiciona se existir

# objetos pré-compilados que já vieram no zip
OBJS="data.o"
[ -f util.o ] && OBJS="$OBJS util.o"     # se existir util.o, linka também

echo "[1/2] Compilando..."
gcc -Wall -Wextra -std=c11 $SRCS $OBJS -o projeto.exe -mconsole

echo "[2/2] Rodando..."
./projeto.exe
