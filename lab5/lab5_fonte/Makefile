CC=gcc -Wall

EX1A=1A
EX1A_PIPE=1A_pipe
EX1A_FIFO=1A_fifo
EX1B=1B
EX1B_PIPE=1B_pipe
EX1B_FIFO=1B_fifo

PROGS=$(EX1A)

all: $(PROGS)

$(EX1A): $(EX1A_FIFO) $(EX1A_PIPE)

$($EX1A_PIPE): $(EX1A_PIPE).c
	$(CC) $(EX1A_PIPE).c -o $(EX1A_PIPE).out

$($EX1A_FIFO): $(EX1A_FIFO).c
	$(CC) $(EX1A_FIFO).c -o $(EX1A_FIFO).out

$(EX1B): $(EX1B_FIFO) $(EX1B_PIPE)

$($EX1B_PIPE): $(EX1B_PIPE).c
	$(CC) $(EX1B_PIPE).c -o $(EX1B_PIPE).out

$($EX1B_FIFO): $(EX1B_FIFO).c
	$(CC) $(EX1B_FIFO).c -o $(EX1B_FIFO).out
