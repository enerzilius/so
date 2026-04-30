CC=gcc -Wall

EX1A_PIPE=1A_pipe
EX1A_FIFO=1A_fifo
EX1B_PIPE=1B_pipe
EX1B_FIFO=1B_fifo
EX2A=2A

PROGS=$(EX1A_PIPE) $(EX1A_FIFO) $(EX1B_PIPE) $(EX1B_FIFO) $(EX2A)

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

clean:
	rm $(PROGS)
