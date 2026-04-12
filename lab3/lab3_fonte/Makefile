.PHONY:  matriz

CC=gcc -Wall

EX0 = busca
EX1 = processar_matriz
M = matriz
PROGS = $(EX0) $(EX1)

all: $(PROGS)

$(EX0): $(EX0).c
	$(CC) $(EX0).c -o $(EX0).out

$(EX1): $(EX1).c $(M).c
	$(CC) $(EX1).c $(M).c -o $(EX1).out

clean:
	rm -rf *.out *.o
