.PHONY=$(EX) $(MON)

CC=gcc -Wall

EX=jantar
MON=monitor

all: $(EX)

$(EX): $(MON).o
	$(CC) $(EX).c $(MON).o -o $(EX).out

$(MON): $(MON).c $(MON).h
	$(CC) -c $(MON).c -o $(MON).o

clean: 
	rm *.out *.o

