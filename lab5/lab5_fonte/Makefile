CC=gcc -Wall

EX1A=1A
EX1A_PIPE=1A_pipe
EX1A_FIFO=1A_fifo

PROGS=$(EX1A)

all: $(PROGS)

$(EX1A): $(EX1A_FIFO) $(EX1A_PIPE)

$($EX1A_PIPE): $(EX1A_PIPE).c
	$(CC) $(EX1A_PIPE).c -o $(EX1A_PIPE).out

$($EX1A_FIFO): $(EX1A_FIFO).c
	$(CC) $(EX1A_FIFO).c -o $(EX1A_FIFO).out
