CC=gcc

EX0 = busca
EX1 = processar_matriz
M = matriz
PROGS = $(EX0) $(EX1)
DEPS = matriz.h

all: $(PROGS)

$(EX0): $(EX0).c
	$(CC) $(EX0).c -o $(EX0).out

$(EX1): $(EX1).o $(M).o
	$(CC) -o $(EX1).out $(M).o $(EX1).o -lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< -I.

clean:
	rm -rf *.out *.o *.in *.txt
