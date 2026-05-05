CC=gcc -Wall

EX1A_PIPE=1A_pipe
EX1A_FIFO=1A_fifo
EX1B_PIPE=1B_pipe
EX1B_FIFO=1B_fifo
EX2A=2A
EX2B=2B
EX2C=2C
EX3=3
EX4=4

PROGS=$(EX1A_PIPE) $(EX1A_FIFO) $(EX1B_PIPE) $(EX1B_FIFO) $(EX2A) $(EX2B) $(EX2C) $(EX3) $(EX4)

all: $(PROGS)

$($EX1A_PIPE): $(EX1A_PIPE).c
	$(CC) $(EX1A_PIPE).c -o $(EX1A_PIPE).out

$($EX1A_FIFO): $(EX1A_FIFO).c
	$(CC) $(EX1A_FIFO).c -o $(EX1A_FIFO).out

$($EX1B_PIPE): $(EX1B_PIPE).c
	$(CC) $(EX1B_PIPE).c -o $(EX1B_PIPE).out

$($EX1B_FIFO): $(EX1B_FIFO).c
	$(CC) $(EX1B_FIFO).c -o $(EX1B_FIFO).out

$($EX2A): $(EX2A).c
	$(CC) $(EX2A).c -o $(EX2A).out

$($EX2B): $(EX2B).c
	$(CC) $(EX2B).c -o $(EX2B).out

$($EX2C): $(EX2C).c
	$(CC) $(EX2C).c -o $(EX2C).out

$(EX3): $(EX3).c
	$(CC) $(EX3).c -o $(EX3).out

$(EX4): $(EX4).c
	$(CC) $(EX4).c -o $(EX4).out

clean:
	rm $(PROGS) *.out
