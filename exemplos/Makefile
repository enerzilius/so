CC=gcc -Wall
	
P1=ex_cpu_bound_process
P2=ex_exec
P3=ex_fork_wait
P4=ex_zombie
P5=ex_io_bound_process
P6=process_uninterruptible_state
P7=ex_fork
P8=ex_vfork
P9=ex_nozombie

PROGS=$(P1) $(P2) $(P3) $(P4) $(P5) $(P6) $(P7) $(P8) $(P9)

all: $(PROGS)

$(P1):	$(P1).c
	$(CC) $(P1).c -o $(P1)
	
$(P2):	$(P2).c
	$(CC) $(P2).c -o $(P2)
	
$(P3):	$(P3).c
	$(CC) $(P3).c -o $(P3)
	
$(P4):	$(P4).c
	$(CC) $(P4).c -o $(P4)
	
$(P5):	$(P5).c
	$(CC) $(P5).c -o $(P5)
	
$(P6):	$(P6).c
	$(CC) $(P6).c -o $(P6)
	
$(P7):	$(P7).c
	$(CC) $(P7).c -o $(P7)
	
$(P8):	$(P8).c
	$(CC) $(P8).c -o $(P8)
	
$(P9):	$(P9).c
	$(CC) $(P9).c -o $(P9)
	
clean:
	rm $(PROGS)
