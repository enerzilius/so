CC=gcc -Wall

EX0 = forkbomb
EX1 = hierarquia
EX2 = exec
EX3 = busca_vetor
EX4 = shell

PROGS = $(EX0) $(EX1) $(EX2) $(EX3) $(EX4)

all: $(PROGS)

$(EX0): $(EX0).c
	$(CC) $(EX0).c -o $(EX0).out

$(EX1): $(EX1).c
	$(CC) $(EX1).c -o $(EX1).out

$(EX2): $(EX2).c
	$(CC) $(EX2).c -o $(EX2).out

$(EX3): $(EX3).c
	$(CC) $(EX3).c -o $(EX3).out

$(EX4): $(EX4).c
	$(CC) $(EX4).c -o $(EX4).out

.PHONY clean:
clean:
	rm -rf *.out
